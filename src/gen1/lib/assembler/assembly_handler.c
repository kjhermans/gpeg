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
        //.. return error
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
        //.. return error
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
        //.. return error
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

int handle_post_CLOSECAPTUREINSTR
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
        //.. return error
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
  uint32_t param2 = htonl(atoi((char*)(capture->children.list[ 1 ].data.data)));

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &opcode, sizeof(opcode));
    vec_append(gpega->output, &param1, sizeof(param1));
    vec_append(gpega->output, &param2, sizeof(param2));
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

int handle_post_ENDISOLATEINSTR
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

int handle_post_ENDREPLACEINSTR
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

int handle_post_FAILINSTR
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

int handle_post_FAILTWICEINSTR
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

int handle_post_INTRPCAPTUREINSTR
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

int handle_INTRPCAPTURETYPES
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

int handle_post_INTRPCAPTURETYPES
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

int handle_INTRPCAPTURETYPES_0
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

int handle_post_INTRPCAPTURETYPES_0
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

int handle_post_ISOLATEINSTR
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
        //.. return error
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

int handle_post_JUMPINSTR
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

int handle_LABEL
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
  char* label = (char*)(capture->data.data);

  if (gpega->round == 0) {
    str2int_map_put(&(gpega->labelmap), label, gpega->offset);
  }

  return 0;
}

int handle_post_LABEL
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
  return 0;
}

int handle_post_LABELDEF
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

int handle_MASKEDCHARINSTR
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

int handle_post_MASKEDCHARINSTR
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

int handle_post_NOOPINSTR
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

int handle_post_OPENCAPTUREINSTR
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
        //.. return error
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

int handle_post_PARTIALCOMMITINSTR
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
  return 0;
}

int handle_post_QUADINSTR
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
  return 0;
}

int handle_post_RANGEINSTR
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

int handle_post_REPLACEINSTR
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

int handle_post_RETINSTR
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

int handle_RULEINSTR
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

int handle_post_RULEINSTR
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
  return 0;
}

int handle_post_SETINSTR
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
  return 0;
}

int handle_post_SKIPINSTR
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
  return 0;
}

int handle_post_SPANINSTR
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
  return 0;
}

int handle_post_TESTANYINSTR
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
  return 0;
}

int handle_post_TESTCHARINSTR
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
  return 0;
}

int handle_post_TESTQUADINSTR
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
  return 0;
}

int handle_post_TESTSETINSTR
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

int handle_post_TRAPINSTR
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
  return 0;
}

int handle_post_VARINSTR
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
