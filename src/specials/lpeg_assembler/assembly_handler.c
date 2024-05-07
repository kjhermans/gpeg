//#include "gpega_private.h"
//#include "gpega_instructions.h"
//#include "assembly.slotmap.h"

#include <gpeg/private/assembler/lib.h>

#include "lpeg.h"

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
  lpeg_instr_t instr = {
    .instr.code = IAny,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_ANY;
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
  char* label = (char*)(capture->children.list[ 0 ].data.data);
  unsigned offset = 0;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + LPEG_INSTR_LENGTH_BACKCOMMIT;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }

  lpeg_instr_t instr[ 2 ] = {
    {
      .instr.code = IBackCommit,
      .instr.aux = 0,
      .instr.key = 0
    },
    {
      .offset = offset
    }
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_BACKCOMMIT;
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
  char* label = (char*)(capture->children.list[ 0 ].data.data);
  unsigned offset = 0;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + LPEG_INSTR_LENGTH_CALL;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }

  lpeg_instr_t instr[ 2 ] = {
    {
      .instr.code = ICall,
      .instr.aux = 0,
      .instr.key = 0
    },
    {
      .offset = offset
    }
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_CALL;
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
  char* label = (char*)(capture->children.list[ 0 ].data.data);
  unsigned offset = 0;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + LPEG_INSTR_LENGTH_CHOICE;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }

  lpeg_instr_t instr[ 2 ] = {
    {
      .instr.code = IChoice,
      .instr.aux = 0,
      .instr.key = 0
    },
    {
      .offset = offset
    }
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_CHOICE;
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
  unsigned char* hex = capture->children.list[ 0 ].data.data;
  uint32_t value = htonl(hexcodon(hex[ 0 ], hex[ 1 ]));
  lpeg_instr_t instr = {
    .instr.code = IChar,
    .instr.aux = value,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_CHAR;
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
  lpeg_instr_t instr = {
    .instr.code = ICloseCapture,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_CLOSECAPTURE;
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
  char* label = (char*)(capture->children.list[ 0 ].data.data);
  unsigned offset = 0;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + LPEG_INSTR_LENGTH_COMMIT;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }

  lpeg_instr_t instr[ 2 ] = {
    {
      .instr.code = ICommit,
      .instr.aux = 0,
      .instr.key = 0
    },
    {
      .offset = offset
    }
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_COMMIT;
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

  fprintf(stderr, "Warning: condjump instruction not emitted.\n");

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

  fprintf(stderr, "Warning: counter instruction not emitted.\n");

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
  lpeg_instr_t instr = {
    .instr.code = IEnd,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_END;
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

  fprintf(stderr, "Warning: endisolate instruction not emitted.\n");

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

  fprintf(stderr, "Warning: endreplace instruction not emitted.\n");

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
  lpeg_instr_t instr = {
    .instr.code = IFail,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_FAIL;
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
  lpeg_instr_t instr = {
    .instr.code = IFailTwice,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_FAILTWICE;
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

  fprintf(stderr, "Warning: intrpcapture instruction not emitted.\n");

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

  fprintf(stderr, "Warning: isolate instruction not emitted.\n");

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
  char* label = (char*)(capture->children.list[ 0 ].data.data);
  unsigned offset = 0;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + LPEG_INSTR_LENGTH_JUMP;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }

  lpeg_instr_t instr[ 2 ] = {
    {
      .instr.code = IJmp,
      .instr.aux = 0,
      .instr.key = 0
    },
    {
      .offset = offset
    }
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_JUMP;
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

  fprintf(stderr, "Warning: maskedchar instruction not emitted.\n");

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

  fprintf(stderr, "Warning: noop instruction not emitted.\n");

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
  lpeg_instr_t instr = {
    .instr.code = IOpenCapture,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_OPENCAPTURE;
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
  char* label = (char*)(capture->children.list[ 0 ].data.data);
  unsigned offset = 0;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + LPEG_INSTR_LENGTH_PARTIALCOMMIT;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }

  lpeg_instr_t instr[ 2 ] = {
    {
      .instr.code = IPartialCommit,
      .instr.aux = 0,
      .instr.key = 0
    },
    {
      .offset = offset
    }
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_PARTIALCOMMIT;
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

  switch (gpega->round) {
  case 1:
    __attribute__ ((fallthrough));
  case 0:
    //gpega->offset += INSTR_LENGTH_QUAD;
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

  fprintf(stderr, "Warning: replace instruction not emitted.\n");

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
  lpeg_instr_t instr = {
    .instr.code = IRet,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_RET;
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
  unsigned char* hex = capture->children.list[ 0 ].data.data;
  lpeg_instr_t instr = {
    .instr.code = ISet,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    for (unsigned i=0; i < 64; i += 2) {
      uint8_t c = hexcodon(hex[ i ], hex[ i+1 ]);
      vec_appendchr(gpega->output, c);
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_SET;
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

  char* nstring = (char*)(capture->children.list[ 0 ].data.data);
  unsigned n = strtoul(nstring, 0, 10);

  for (unsigned i=0; i < n; i++) {
    handle_ANYINSTR(parent, index, capture, arg);
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

  gpega_t* gpega = arg;
  unsigned char* hex = capture->children.list[ 0 ].data.data;
  lpeg_instr_t instr = {
    .instr.code = ISpan,
    .instr.aux = 0,
    .instr.key = 0
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, &instr, sizeof(instr));
    for (unsigned i=0; i < 64; i += 2) {
      uint8_t c = hexcodon(hex[ i ], hex[ i+1 ]);
      vec_appendchr(gpega->output, c);
    }
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_SPAN;
    break;
  }

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

  gpega_t* gpega = arg;
  char* label = (char*)(capture->children.list[ 0 ].data.data);
  unsigned offset = 0;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + LPEG_INSTR_LENGTH_TESTANY;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }

  lpeg_instr_t instr[ 2 ] = {
    {
      .instr.code = ITestAny,
      .instr.aux = 0,
      .instr.key = 0
    },
    {
      .offset = offset
    }
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_TESTANY;
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
  unsigned char* hex = capture->children.list[ 0 ].data.data;
  uint32_t value = htonl(hexcodon(hex[ 0 ], hex[ 1 ]));
  char* label = (char*)(capture->children.list[ 1 ].data.data);
  unsigned offset = 0;

  if (0 == strcmp(label, "__NEXT__")) {
    offset = gpega->offset + LPEG_INSTR_LENGTH_TESTANY;
  } else if (str2int_map_get(&(gpega->labelmap), label, &offset)) {
    return GPEG_ERR_LABEL.code;
  }

  lpeg_instr_t instr[ 2 ] = {
    {
      .instr.code = ITestChar,
      .instr.aux = value,
      .instr.key = 0
    },
    {
      .offset = offset
    }
  };

  switch (gpega->round) {
  case 1:
    vec_append(gpega->output, instr, sizeof(instr));
    __attribute__ ((fallthrough));
  case 0:
    gpega->offset += LPEG_INSTR_LENGTH_TESTCHAR;
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

  fprintf(stderr, "Warning: trap instruction not emitted.\n");

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

  fprintf(stderr, "Warning: var instruction not emitted.\n");

  return 0;
}

IGNOREPOSTHANDLER(VARINSTR)
