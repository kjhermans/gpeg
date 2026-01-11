#ifndef _XTRANSPORT_H_
#define _XTRANSPORT_H_

#include <stdint.h>

#include <util/vec_t.h>
#include <util/map.h>

#define XT_GROUPSIZE    128
#define XT_HEADERSIZE   12
#define XT_BLOCKSIZE    1024
#define XT_PAYLOADSIZE  (XT_HEADERSIZE + XT_BLOCKSIZE)

#define XT_MAXMSGSIZE   (8 * 1024 * 1024)

#define XT_FLG_INIT     (1<<0)
#define XT_FLG_DATA     (1<<1)
#define XT_FLG_STATUS   (1<<2)
#define XT_FLG_CLOSE    (1<<3)

struct xt_stream {
  vec_t                 msg;
  unsigned              msg_allocated;
  unsigned char*        blocks;
  unsigned              blocks_allocated;
  char*                 filename;
};

MAKE_MAP_HEADER(uint32_t, struct xt_stream, xt_streammap_)

typedef struct
{
  uint32_t              id;
  xt_streammap_t        streammap;
}
xt_t;

extern
int xtransport_client
  (
    xt_t* xt,
    int fd, 
    char* filename,
    vec_t* msg, 
    struct timespec* waitforstatus
  );

extern
int xtransport_server
  (
    xt_t* xt,
    int fd,
    int(*fnc)(char* filename, vec_t* msg, void* arg),
    void* arg
  );

#endif
