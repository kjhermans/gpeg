#define _GNU_SOURCE
#include <sys/socket.h>
#include <poll.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <util/xtransport.h>

MAKE_MAP_CODE(uint32_t, struct xt_stream, xt_streammap_)

static
void __xt_header_compose
  (
    unsigned char header[ XT_HEADERSIZE ],
    uint32_t streamid,
    uint32_t blockindex,
    uint32_t flags
  )
{
  header[  0 ] = (streamid >> 24);
  header[  1 ] = (streamid >> 16);
  header[  2 ] = (streamid >>  8);
  header[  3 ] = streamid;
  header[  4 ] = (blockindex >> 24);
  header[  5 ] = (blockindex >> 16);
  header[  6 ] = (blockindex >>  8);
  header[  7 ] = blockindex;
  header[  8 ] = (flags >> 24);
  header[  9 ] = (flags >> 16);
  header[ 10 ] = (flags >>  8);
  header[ 11 ] = flags;
}

static
void __xt_header_decompose
  (
    unsigned char header[ XT_HEADERSIZE ],
    uint32_t* streamid,
    uint32_t* blockindex,
    uint32_t* flags
  )
{
  *streamid = (
    (header[  0 ] << 24) |
    (header[  1 ] << 16) |
    (header[  2 ] <<  8) |
     header[  3 ]
  );
  *blockindex = (
    (header[  4 ] << 24) |
    (header[  5 ] << 16) |
    (header[  6 ] <<  8) |
     header[  7 ]
  );
  *flags = (
    (header[  8 ] << 24) |
    (header[  9 ] << 16) |
    (header[ 10 ] <<  8) |
     header[ 11 ]
  );
}

int xtransport_client
  (
    xt_t* xt,
    int fd,
    char* filename,
    vec_t* msg,
    struct timespec* waitforstatus
  )
{
  char firstpayload[ XT_PAYLOADSIZE ] = { 0 };
  unsigned char header[ XT_GROUPSIZE ][ XT_HEADERSIZE ] = { 0 };
  struct iovec iovec[ XT_GROUPSIZE ][ 2 ] = { 0 };
  struct mmsghdr msgvec[ XT_GROUPSIZE ] = { 0 };
  int vlen = 0;
  uint32_t streamid = ++(xt->id);
  unsigned rollback_off;
  unsigned off = 0;
  int r;
  int first = 1;
  unsigned blockno = 1;

  if (msg->size >= XT_MAXMSGSIZE) {
    return ~0;
  }

  while (off < msg->size) {
    rollback_off = off;
    for (unsigned i=0; off < msg->size && i < XT_GROUPSIZE; i++) {
      if (first) {
        unsigned flags = XT_FLG_INIT;
        if (msg->size == 0) {
          flags |= XT_FLG_CLOSE;
        }
        __xt_header_compose(header[ i ], streamid, 0, flags);
        snprintf(firstpayload, sizeof(firstpayload), "%u:%s", msg->size, filename);
        iovec[ i ][ 0 ].iov_base = header[ i ];
        iovec[ i ][ 0 ].iov_len = XT_HEADERSIZE;
        iovec[ i ][ 1 ].iov_base = firstpayload;
        iovec[ i ][ 1 ].iov_len = strlen(firstpayload) + 1;
        msgvec[ i ].msg_hdr.msg_iov = iovec[ i ];
        msgvec[ i ].msg_hdr.msg_iovlen = 2;
        first = 0;
      } else {
        unsigned len = XT_BLOCKSIZE;
        unsigned flags = XT_FLG_DATA;
        if (off + len >= msg->size) {
          len = msg->size - off;
          flags |= XT_FLG_CLOSE;
        }
        __xt_header_compose(header[ i ], streamid, blockno, flags);
        iovec[ i ][ 0 ].iov_base = header[ i ];
        iovec[ i ][ 0 ].iov_len = XT_HEADERSIZE;
        iovec[ i ][ 1 ].iov_base = msg->data + off;
        iovec[ i ][ 1 ].iov_len = len;
        msgvec[ i ].msg_hdr.msg_iov = iovec[ i ];
        msgvec[ i ].msg_hdr.msg_iovlen = 2;
        ++blockno;
        off += len;
      }
      ++vlen;
    }
    r = sendmmsg(fd, msgvec, vlen, 0);
    if (r != vlen) {
      if (r == -1 || r == 0) {
        return ~0;
      } else if (r < vlen) { /* Rollback */
        int diff = vlen - r;
        off = rollback_off + (r * XT_GROUPSIZE);
        blockno -= diff;
      }
    }
    vlen = 0;
  }

  if (waitforstatus) {
    struct pollfd pfds[ 1 ] = {
      { .fd = fd, .events = POLLIN, .revents = 0 }
    };
    switch (ppoll(pfds, 1, waitforstatus, 0)) {
    case -1:
      return ~0;
    case 0:
      return 0;
    case 1:
      {
        unsigned char reply[ XT_HEADERSIZE ];
        int r = recv(fd, reply, sizeof(reply), 0);
        uint32_t re_streamid, re_status, re_flags;
        if (r >= XT_HEADERSIZE) {
          __xt_header_decompose(reply, &re_streamid, &re_status, &re_flags);
          if (streamid == re_streamid && re_flags & XT_FLG_STATUS) {
            return (int)re_status;
          }
        }
      }
      break;
    }
  }

  return 0;
}

static
void __xt_stream_set_filename
  (
    xt_t* xt,
    uint32_t streamid,
    char* filename
  )
{
  struct xt_stream* stream;
  char* colon;
  unsigned msgsize;

  if (NULL == (colon = strchr(filename, ':'))) {
    return;
  }

  if (NULL == (stream = xt_streammap_getptr(&(xt->streammap), streamid))) {
    struct xt_stream newstream = { 0 };
    xt_streammap_put(&(xt->streammap), streamid, newstream);
    if ((stream = xt_streammap_getptr(&(xt->streammap), streamid)) == NULL) {
      abort();
    }
  }

  *colon = 0;
  msgsize = strtoull(filename, 0, 10);
  ++colon;
  stream->filename = strdup(colon);

  if (msgsize > stream->msg_allocated) {
    stream->msg_allocated = msgsize;
    stream->msg.data = realloc(stream->msg.data, stream->msg_allocated + 1);
    stream->msg.size = stream->msg_allocated;
  }
  if ((msgsize / (8 * XT_BLOCKSIZE)) + 1 > stream->blocks_allocated) {
    unsigned orig = stream->blocks_allocated;
    stream->blocks_allocated = (msgsize / (8 * XT_BLOCKSIZE)) + 1;
    stream->blocks = realloc(stream->blocks, stream->blocks_allocated);
    memset(stream->blocks + orig, 0, stream->blocks_allocated - orig);
  }
}

static
void __xt_stream_push_block
  (
    xt_t* xt,
    uint32_t streamid,
    uint32_t blockindex,
    unsigned char* block,
    unsigned size
  )
{
  struct xt_stream* stream;
  off_t blockoffset = blockindex * XT_BLOCKSIZE;

  if (blockoffset + size > XT_MAXMSGSIZE) {
    return;
  }

  if (NULL == (stream = xt_streammap_getptr(&(xt->streammap), streamid))) {
    struct xt_stream newstream = { 0 };
    xt_streammap_put(&(xt->streammap), streamid, newstream);
    if ((stream = xt_streammap_getptr(&(xt->streammap), streamid)) == NULL) {
      abort();
    }
  }

  if (blockoffset + size > stream->msg_allocated) {
    stream->msg_allocated = blockoffset + size;
    stream->msg.data = realloc(stream->msg.data, stream->msg_allocated);
  }
  memcpy(stream->msg.data + blockoffset, block, size);

  if ((blockindex / 8) + 1 > stream->blocks_allocated) {
    unsigned orig = stream->blocks_allocated;
    stream->blocks_allocated = (blockindex / 8) + 1;
    stream->blocks = realloc(stream->blocks, stream->blocks_allocated);
    memset(stream->blocks + orig, 0, stream->blocks_allocated - orig);
  }
  stream->blocks[ blockindex / 8 ] |= (1 << (blockindex % 8));
}

/**
 * This function can be called when the filedescriptor
 * in the service implementation has become ready for
 * reading.
 */
int xtransport_server
  (
    xt_t* xt,
    int fd,
    int(*fnc)(char* filename, vec_t* msg, void* arg),
    void* arg
  )
{
  struct iovec iovec[ XT_GROUPSIZE ] = { 0 };
  struct mmsghdr msgvec[ XT_GROUPSIZE ] = { 0 };
  unsigned char* msgbuf = 0;
  int r;

  msgbuf = calloc(1, XT_GROUPSIZE * XT_PAYLOADSIZE);
  for (unsigned i=0; i < XT_GROUPSIZE; i++) {
    iovec[ i ].iov_base = msgbuf + (i * XT_PAYLOADSIZE);
    iovec[ i ].iov_len = XT_PAYLOADSIZE;
    msgvec[ i ].msg_hdr.msg_iov = &(iovec[ i ]);
    msgvec[ i ].msg_hdr.msg_iovlen = 1;
  }
  r = recvmmsg(fd, msgvec, XT_GROUPSIZE, MSG_WAITFORONE, 0);
  if (r == -1) {
    free(msgbuf);
    return ~0;
  } else if (r == 0) {
    free(msgbuf);
    return 0;
  }
  for (unsigned i=0; i < (unsigned)r; i++) {
    uint32_t streamid, blockindex, flags;
    if (iovec[ i ].iov_len < XT_HEADERSIZE) {
      continue; /* disregard */
    }
    __xt_header_decompose(iovec[ i ].iov_base, &streamid, &blockindex, &flags);
    if (flags & XT_FLG_INIT) {
      char* str = iovec[ i ].iov_base + XT_HEADERSIZE;
      unsigned str_len = iovec[ i ].iov_len - XT_HEADERSIZE;
      if (str_len == XT_BLOCKSIZE) { --str_len; }
      str[ str_len ] = 0;
      __xt_stream_set_filename(xt, streamid, str);
    } else if (flags & XT_FLG_DATA && blockindex) {
      --blockindex;
      __xt_stream_push_block(
        xt,
        streamid,
        blockindex,
        iovec[ i ].iov_base + XT_HEADERSIZE,
        iovec[ i ].iov_len - XT_HEADERSIZE
      );
    }
    if (flags & XT_FLG_CLOSE) {
      struct xt_stream* stream;
      int r;
      unsigned char reply[ XT_HEADERSIZE ] = { 0 };
      if (NULL == (stream = xt_streammap_getptr(&(xt->streammap), streamid))) {
        abort();
      }
      r = fnc(stream->filename, &(stream->msg), arg);
      free(stream->filename);
      free(stream->msg.data);
      free(stream->blocks);
      xt_streammap_del(&(xt->streammap), streamid, 0);
      __xt_header_compose(reply, streamid, (uint32_t)r, XT_FLG_STATUS);
      if (send(fd, reply, sizeof(reply), 0)) {
      }
    }
  }

  free(msgbuf);
  return 0;
}
