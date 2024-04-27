#include "gpega_private.h"
#include "gpega_instructions.h"
#include "assembly.slotmap.h"

#define COMBINE(a, b) a##b
#define IGNOREHANDLER(ident)     \
int COMBINE(handle_,ident)       \
  (                              \
    gpeg_capture_t* parent,      \
    unsigned index,              \
    gpeg_capture_t* capture,     \
    void* arg                    \
  )                              \
{                                \
  (void)parent;                  \
  (void)index;                   \
  (void)capture;                 \
  (void)arg;                     \
  return 0;                      \
}                                \
int COMBINE(handle_post_,ident)  \
  (                              \
    gpeg_capture_t* parent,      \
    unsigned index,              \
    gpeg_capture_t* capture,     \
    void* arg                    \
  )                              \
{                                \
  (void)parent;                  \
  (void)index;                   \
  (void)capture;                 \
  (void)arg;                     \
  return 0;                      \
}

#define IGNOREPOSTHANDLER(ident) \
int COMBINE(handle_post_,ident)  \
  (                              \
    gpeg_capture_t* parent,      \
    unsigned index,              \
    gpeg_capture_t* capture,     \
    void* arg                    \
  )                              \
{                                \
  (void)parent;                  \
  (void)index;                   \
  (void)capture;                 \
  (void)arg;                     \
  return 0;                      \
}

IGNOREHANDLER(AMPERSAND)

int handle_ANYINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_ANY);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_ANY;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(ANYINSTR)

int handle_BACKCOMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_BACKCOMMIT);
      char* label = (char*)(capture->children.list[ 0 ].data.data);
      unsigned offset = 0;
      uint32_t o;

      if (0 == strcmp(label, "__NEXT__")) {
        offset = gpega->offset + INSTR_LENGTH_BACKCOMMIT;
      } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
        return GPEG_ERR_LABEL.code;
      }
      o = htonl(offset);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &o, sizeof(o));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_BACKCOMMIT;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(BACKCOMMITINSTR)

int handle_CALLINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_CALL);
      char* label = (char*)(capture->children.list[ 0 ].data.data);
      unsigned offset = 0;
      uint32_t o;

      if (0 == strcmp(label, "__NEXT__")) {
        offset = gpega->offset + INSTR_LENGTH_CALL;
      } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
        return GPEG_ERR_LABEL.code;
      }
      o = htonl(offset);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &o, sizeof(o));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_CALL;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(CALLINSTR)

int handle_CATCHINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_CATCH);
      char* label = (char*)(capture->children.list[ 0 ].data.data);
      unsigned offset = 0;
      uint32_t o;

      if (0 == strcmp(label, "__NEXT__")) {
        offset = gpega->offset + INSTR_LENGTH_CATCH;
      } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
        return GPEG_ERR_LABEL.code;
      }
      o = htonl(offset);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &o, sizeof(o));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_CATCH;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(CATCHINSTR)

int handle_CHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_CHAR);
  unsigned char* hex = capture->children.list[ 0 ].data.data;
  uint32_t value = htonl(hexcodon(hex[ 0 ], hex[ 1 ]));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &value, sizeof(value));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_CHAR;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(CHARINSTR)

int handle_CLOSECAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_CLOSECAPTURE);
  uint32_t slot = htonl(atoi((char*)(capture->children.list[ 0 ].data.data)));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &slot, sizeof(slot));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_CLOSECAPTURE;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(CLOSECAPTUREINSTR)

IGNOREHANDLER(CODE)
IGNOREHANDLER(COLON)
IGNOREHANDLER(COMMENT)

int handle_COMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_COMMIT);
      char* label = (char*)(capture->children.list[ 0 ].data.data);
      unsigned offset = 0;
      uint32_t o;

      if (0 == strcmp(label, "__NEXT__")) {
        offset = gpega->offset + INSTR_LENGTH_COMMIT;
      } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
        return GPEG_ERR_LABEL.code;
      }
      o = htonl(offset);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &o, sizeof(o));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_COMMIT;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(COMMITINSTR)

int handle_CONDJUMPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_CONDJUMP);
  uint32_t param1 = htonl(atoi((char*)(capture->children.list[ 0 ].data.data)));
  char* label = (char*)(capture->children.list[ 1 ].data.data);
  unsigned offset = 0;
  uint32_t o;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + INSTR_LENGTH_COMMIT;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }
  o = htonl(offset);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &param1, sizeof(param1));
    vec_append(gpega->output, &o, sizeof(o));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_CONDJUMP;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(CONDJUMPINSTR)

int handle_COUNTERINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_COUNTER);
  uint32_t param1 = htonl(atoi((char*)(capture->children.list[ 0 ].data.data)));
  uint32_t param2 = htonl(atoi((char*)(capture->children.list[ 1 ].data.data)));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &param1, sizeof(param1));
    vec_append(gpega->output, &param2, sizeof(param2));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_COUNTER;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(COUNTERINSTR)

IGNOREHANDLER(END)

int handle_ENDINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_END);
  uint32_t exitcode = htonl(atoi((char*)(capture->children.list[ 0 ].data.data)));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &exitcode, sizeof(exitcode));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_END;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(ENDINSTR)

int handle_ENDISOLATEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(ENDISOLATEINSTR)

int handle_ENDREPLACEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(ENDREPLACEINSTR)

int handle_FAILINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_FAIL);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_FAIL;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(FAILINSTR)

int handle_FAILTWICEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_FAILTWICE);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_FAILTWICE;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(FAILTWICEINSTR)

IGNOREHANDLER(HEXBYTE)
IGNOREHANDLER(INSTRUCTION)
IGNOREHANDLER(INSTRUCTIONS)

int handle_INTRPCAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(INTRPCAPTUREINSTR)

IGNOREHANDLER(INTRPCAPTURETYPES)
IGNOREHANDLER(INTRPCAPTURETYPES_0)

int handle_ISOLATEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(ISOLATEINSTR)

int handle_JUMPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_JUMP);
      char* label = (char*)(capture->children.list[ 0 ].data.data);
      unsigned offset = 0;
      uint32_t o;

      if (0 == strcmp(label, "__NEXT__")) {
        offset = gpega->offset + INSTR_LENGTH_JUMP;
      } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
        return GPEG_ERR_LABEL.code;
      }
      o = htonl(offset);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &o, sizeof(o));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_JUMP;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(JUMPINSTR)

IGNOREHANDLER(LABEL)

int handle_LABELDEF
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  char* label = (char*)(capture->children.list[ 0 ].data.data);

  if (gpega->round == 0) {
    str2int_map_put(&(gpega->labelmap), label, gpega->offset);
  }

  return 0;
}

IGNOREPOSTHANDLER(LABELDEF)

int handle_BITMASKINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_BITMASK);
      uint32_t nbits = atoi((char*)(capture->children.list[ 1 ].data.data));
      uint32_t bits = strtol((char*)(capture->children.list[ 2 ].data.data), 0, 16);
      uint32_t andmask = strtol((char*)(capture->children.list[ 3 ].data.data), 0, 16);
      uint32_t ormask = strtol((char*)(capture->children.list[ 4 ].data.data), 0, 16);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &nbits, sizeof(nbits));
      vec_append(gpega->output, &bits, sizeof(bits));
      vec_append(gpega->output, &andmask, sizeof(andmask));
      vec_append(gpega->output, &ormask, sizeof(ormask));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_BITMASK;
    break;
  }


  return 0;
}

IGNOREPOSTHANDLER(BITMASKINSTR)

IGNOREHANDLER(HEXQUAD)
IGNOREHANDLER(MULTILINECOMMENT)

int handle_NOOPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_NOOP);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_NOOP;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(NOOPINSTR)

IGNOREHANDLER(NUMBER)

int handle_OPENCAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_OPENCAPTURE);
  uint32_t slot = htonl(atoi((char*)(capture->children.list[ 0 ].data.data)));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &slot, sizeof(slot));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_OPENCAPTURE;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(OPENCAPTUREINSTR)

int handle_PARTIALCOMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_PARTIALCOMMIT);
      char* label = (char*)(capture->children.list[ 0 ].data.data);
      unsigned offset = 0;
      uint32_t o;

      if (0 == strcmp(label, "__NEXT__")) {
        offset = gpega->offset + INSTR_LENGTH_PARTIALCOMMIT;
      } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
        return GPEG_ERR_LABEL.code;
      }
      o = htonl(offset);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &o, sizeof(o));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_PARTIALCOMMIT;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(PARTIALCOMMITINSTR)

IGNOREHANDLER(QUAD)

int handle_QUADINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_QUAD);
  char* quad = (char*)(capture->children.list[ 0 ].data.data);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_appendchr(gpega->output, hexcodon(quad[ 0 ], quad[ 1 ]));
    vec_appendchr(gpega->output, hexcodon(quad[ 2 ], quad[ 3 ]));
    vec_appendchr(gpega->output, hexcodon(quad[ 4 ], quad[ 5 ]));
    vec_appendchr(gpega->output, hexcodon(quad[ 6 ], quad[ 7 ]));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_QUAD;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(QUADINSTR)

int handle_RANGEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_RANGE);
  unsigned char* hex = capture->children.list[ 0 ].data.data;
  uint32_t from = htonl(hexcodon(hex[ 0 ], hex[ 1 ]));
  hex = capture->children.list[ 1 ].data.data;
  uint32_t until = htonl(hexcodon(hex[ 0 ], hex[ 1 ]));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &from, sizeof(from));
    vec_append(gpega->output, &until, sizeof(until));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_RANGE;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(RANGEINSTR)

IGNOREHANDLER(REGISTER)

int handle_REPLACEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(REPLACEINSTR)

int handle_RETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_RET);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_RET;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(RETINSTR)

IGNOREHANDLER(RULEINSTR)
IGNOREHANDLER(S)
IGNOREHANDLER(SET)

int handle_SETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_SET);
  char* set = (char*)(capture->children.list[ 0 ].data.data);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    for (unsigned i=0; i<64; i+=2) {
      unsigned chr = hexcodon(set[ i ], set[ i+1 ]);
      vec_appendchr(gpega->output, chr);
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_SET;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(SETINSTR)

int handle_SKIPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_SKIP);
  uint32_t nsteps = htonl(atoi((char*)(capture->children.list[ 0 ].data.data)));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &nsteps, sizeof(nsteps));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_SKIP;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(SKIPINSTR)

IGNOREHANDLER(SLOT)

int handle_SPANINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  fprintf(stderr, "Warning: span instruction not implemented.\n");

  return 0;
}

IGNOREPOSTHANDLER(SPANINSTR)

IGNOREHANDLER(STRINGLITERAL)
IGNOREHANDLER(STRINGLITERAL_0)

int handle_TESTANYINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_TESTANY);
      char* label = (char*)(capture->children.list[ 0 ].data.data);
      unsigned offset = 0;
      uint32_t o;

      if (0 == strcmp(label, "__NEXT__")) {
        offset = gpega->offset + INSTR_LENGTH_TESTANY;
      } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
        return GPEG_ERR_LABEL.code;
      }
      o = htonl(offset);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &o, sizeof(o));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_TESTANY;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(TESTANYINSTR)

int handle_TESTCHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;

  switch (gpega->round) {
  case 1:
    {
      uint32_t opcode = htonl(INSTR_OPCODE_TESTCHAR);
      char* label = (char*)(capture->children.list[ 1 ].data.data);
      unsigned offset = 0;
      uint32_t o;
      unsigned char* hex = capture->children.list[ 0 ].data.data;
      uint32_t value = htonl(hexcodon(hex[ 0 ], hex[ 1 ]));

      if (0 == strcmp(label, "__NEXT__")) {
        offset = gpega->offset + INSTR_LENGTH_TESTCHAR;
      } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
        return GPEG_ERR_LABEL.code;
      }
      o = htonl(offset);
      vec_append(gpega->output, &opcode, sizeof(opcode));
      vec_append(gpega->output, &o, sizeof(o));
      vec_append(gpega->output, &value, sizeof(value));
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_TESTCHAR;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(TESTCHARINSTR)

int handle_TESTQUADINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  fprintf(stderr, "Warning: testquad instruction not implemented.\n");

  return 0;
}

IGNOREPOSTHANDLER(TESTQUADINSTR)

int handle_TESTSETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  fprintf(stderr, "Warning: testset instruction not implemented.\n");

  return 0;
}

IGNOREPOSTHANDLER(TESTSETINSTR)

IGNOREHANDLER(TOP)

int handle_TRAPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_TRAP);

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_TRAP;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(TRAPINSTR)

IGNOREHANDLER(TYPE)
IGNOREHANDLER(UNSIGNED)

int handle_VARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpega_t* gpega = arg;
  uint32_t opcode = htonl(INSTR_OPCODE_VAR);
  uint32_t slot = htonl(atoi((char*)(capture->children.list[ 0 ].data.data)));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &slot, sizeof(slot));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += INSTR_LENGTH_VAR;
    break;
  }

  return 0;
}

IGNOREPOSTHANDLER(VARINSTR)
