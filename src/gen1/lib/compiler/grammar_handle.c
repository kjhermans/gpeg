#include "gpegc_private.h"
#include "grammar.slotmap.h"

#define COMBINE(a, b) a##b
#define IGNOREHANDLER(ident)     \
int COMBINE(gpegc_handle_,ident) \
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
int COMBINE(gpegc_handle_post_,ident) \
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
int COMBINE(gpegc_handle_post_,ident) \
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

IGNOREHANDLER(ABCLOSE)
IGNOREHANDLER(ABOPEN)

int gpegc_handle_AND
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }
  gpegc->currentmatcher->modifier = GPEGC_MODI_AND;

  return 0;
}

IGNOREPOSTHANDLER(AND)

int gpegc_handle_ANY
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

  gpegc_t* gpegc = arg;
  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_ANY;

  return 0;
}

IGNOREPOSTHANDLER(ANY)

IGNOREHANDLER(BCLOSE)

int gpegc_handle_BITMASK
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

  ASSERT(capture->data.size >= 2
         && capture->data.data[ 0 ] == '|'
         && capture->data.data[ capture->data.size-1 ] == '|')

  gpegc_t* gpegc = arg;
  unsigned char* mask = &(capture->data.data[ 1 ]);
  uint32_t nbits = capture->data.size-2;
  uint32_t bits = 0;
  uint32_t andmask = 0;
  uint32_t ormask = 0;

  if (gpegc->round == 0) { return 0; }

  for (unsigned i=0; i < nbits; i++) {
    uint32_t bit = (1<<(nbits-(i+1)));
    switch (mask[ i ]) {
    case '0': // must match zero
      andmask |= bit;
      break;
    case '1': // must match one
      bits |= bit;
      andmask |= bit;
      break;
    case '_': // don't care
      ormask |= bit;
      break;
    }
  }

  gpegc->currentmatcher->type = GPEGC_MATCH_BITMASK; 
  gpegc->currentmatcher->value.bitmask.nbits = nbits;
  gpegc->currentmatcher->value.bitmask.bits = bits;
  gpegc->currentmatcher->value.bitmask.andmask = andmask;
  gpegc->currentmatcher->value.bitmask.ormask = ormask;

  return 0;
}

IGNOREPOSTHANDLER(BITMASK)

IGNOREHANDLER(BOPEN)

int gpegc_handle_CAPTURE
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

  gpegc_t* gpegc = arg;
  char slotname[ 128 ];

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_CAPTURE;
  gpegc->currentmatcher->value.capture.slot = (gpegc->cslot)++;
  if (str2int_map_has(&(gpegc->slotmap), gpegc->currentrule.name)) {
    snprintf(slotname, sizeof(slotname),
      "%s_%u"
      , gpegc->currentrule.name,
      (gpegc->currentrule.slotcount)++
    );
  } else {
    snprintf(slotname, sizeof(slotname),
      "%s"
      , gpegc->currentrule.name
    );
  }
  str2int_map_put(
    &(gpegc->slotmap),
    strdup(slotname),
    gpegc->currentmatcher->value.capture.slot
  );
  capture->attachment.value_ptr = gpegc->currentmatcherlist;
  gpegc->currentmatcherlist = &(gpegc->currentmatcher->group);

  return 0;
}

int gpegc_handle_post_CAPTURE
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcherlist = capture->attachment.value_ptr;

  return 0;
}

int gpegc_handle_CAPTURETYPE
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

int gpegc_handle_post_CAPTURETYPE
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

IGNOREHANDLER(CBCLOSE)
IGNOREHANDLER(CBOPEN)
IGNOREHANDLER(COLON)
IGNOREHANDLER(COMMENT)

int gpegc_handle_DEFINITION
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

int gpegc_handle_post_DEFINITION
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

int gpegc_handle_END
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

int gpegc_handle_post_END
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

int gpegc_handle_ENDFORCE
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_ENDFORCE;
  gpegc->currentmatcher->value.number = atoi(
    (char*)(capture->children.list[ 0 ].data.data)
  );

  return 0;
}

int gpegc_handle_post_ENDFORCE
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

int gpegc_handle_EXPRESSION
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  capture->attachment.value_ptr = gpegc->currentmatcherlist;

  return 0;
}

int gpegc_handle_post_EXPRESSION
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcherlist = capture->attachment.value_ptr;

  return 0;
}

int gpegc_handle_EXPRESSION_0
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

  gpegc_t* gpegc = arg;
  gpegc_matcher_t m = { 0 }, *_m;

  if (gpegc->round == 0) { return 0; }

  m.type = GPEGC_MATCH_CHOICE;
  for (unsigned i=0; i < gpegc->currentmatcherlist->count; i++) {
    gpegc_matcherlist_push(&(m.group), gpegc->currentmatcherlist->list[ i ]);
  }
  gpegc->currentmatcherlist->count = 0;
  gpegc_matcherlist_push(gpegc->currentmatcherlist, m);
  _m = gpegc_matcherlist_peekptr(gpegc->currentmatcherlist);
  capture->attachment.value_ptr = gpegc->currentmatcherlist;
  gpegc->currentmatcherlist = &(_m->altgroup);

  return 0;
}

int gpegc_handle_post_EXPRESSION_0
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcherlist = capture->attachment.value_ptr;

  return 0;
}

int gpegc_handle_GRAMMAR
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

int gpegc_handle_post_GRAMMAR
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

int gpegc_handle_GROUP
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_GROUP;
  capture->attachment.value_ptr = gpegc->currentmatcherlist;
  gpegc->currentmatcherlist = &(gpegc->currentmatcher->group);

  return 0;
}

int gpegc_handle_post_GROUP
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcherlist = capture->attachment.value_ptr;

  return 0;
}

static
unsigned hexchar
  (char c)
{
  if (c >= 'a' && c <= 'f') {
    return (10 + c - 'a');
  } else if (c >= 'A' && c <= 'F') {
    return (10 + c - 'A');
  } else if (c >= '0' && c <= '9') {
    return (c - '0');
  } else {
    return 0;
  }
}

static
unsigned unescape
  (char code)
{
  switch (code) {
  case 'a': return 0x07;
  case 'b': return 0x08;
  case 't': return 0x09;
  case 'n': return 0x0a;
  case 'v': return 0x0b;
  case 'f': return 0x0c;
  case 'r': return 0x0d;
  default: return code;
  }
}

int gpegc_handle_HEXLITERAL
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_CHAR;
  gpegc->currentmatcher->value.chr =
    (hexchar(capture->data.data[ 2 ]) << 4) |
     hexchar(capture->data.data[ 3 ]);

  return 0;
}

IGNOREPOSTHANDLER(HEXLITERAL)

int gpegc_handle_IDENT
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

int gpegc_handle_post_IDENT
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

int gpegc_handle_IMPORTDECL
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->importdecl = 1;

  return 0;
}

int gpegc_handle_post_IMPORTDECL
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->importdecl = 0;

  return 0;
}

int gpegc_handle_KW_AS
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

int gpegc_handle_post_KW_AS
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

int gpegc_handle_KW_IMPORT
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

int gpegc_handle_post_KW_IMPORT
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

int gpegc_handle_LCMODES
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

int gpegc_handle_post_LCMODES
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

int gpegc_handle_LCPARAM
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

int gpegc_handle_post_LCPARAM
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

int gpegc_handle_LEFTARROW
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

int gpegc_handle_post_LEFTARROW
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

int gpegc_handle_LIMITEDCALL
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

  gpegc_t* gpegc = arg;
  char* type = (char*)(capture->children.list[ 0 ].data.data);
  char* slot = (char*)(capture->children.list[ 2 ].data.data);
  char* rule = (char*)(capture->children.list[ 4 ].data.data);

  if (gpegc->round == 0) { return 0; }
  if (!(stringlist_has(&(gpegc->namespace), rule))) {
    vec_printf(&(gpegc->compiler->error), "Rule '%s' not found.\n", rule);
    return GPEG_ERR_NOTFOUND.code;
  }

  gpegc->currentmatcher->type = GPEGC_MATCH_LIMITEDCALL;
  gpegc->currentmatcher->value.limitedcall.type = type;
  gpegc->currentmatcher->value.limitedcall.slot = slot;
  gpegc->currentmatcher->value.limitedcall.rule = rule;

  return 0;
}

int gpegc_handle_post_LIMITEDCALL
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

static
void set_bit
  (unsigned char* bitmask, unsigned bit)
{
  bitmask[ bit / 8 ] |= (1 << (bit % 8));
}

static
void set_bits
  (unsigned char* bitmask, unsigned from, unsigned to)
{
  for (unsigned i=from; i <= to; i++) {
    set_bit(bitmask, i);
  }
}

int gpegc_handle_MACRO
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_SET;
  if (0 == strcmp((char*)(capture->data.data), "%s")) {
    set_bit(gpegc->currentmatcher->value.set.bitmask, '\n');
    set_bit(gpegc->currentmatcher->value.set.bitmask, '\r');
    set_bit(gpegc->currentmatcher->value.set.bitmask, '\t');
    set_bit(gpegc->currentmatcher->value.set.bitmask, '\v');
    set_bit(gpegc->currentmatcher->value.set.bitmask, ' ');
  } else if (0 == strcmp((char*)(capture->data.data), "%w")) {
    set_bits(gpegc->currentmatcher->value.set.bitmask, 'a', 'z');
    set_bits(gpegc->currentmatcher->value.set.bitmask, 'A', 'Z');
  } else if (0 == strcmp((char*)(capture->data.data), "%a")) {
    set_bits(gpegc->currentmatcher->value.set.bitmask, 'a', 'z');
    set_bits(gpegc->currentmatcher->value.set.bitmask, 'A', 'Z');
    set_bits(gpegc->currentmatcher->value.set.bitmask, '0', '9');
  } else if (0 == strcmp((char*)(capture->data.data), "%n")) {
    set_bits(gpegc->currentmatcher->value.set.bitmask, '0', '9');
  } else if (0 == strcmp((char*)(capture->data.data), "%p")) {
    gpegc->currentmatcher->type = GPEGC_MATCH_RANGE;
    gpegc->currentmatcher->value.range.from = 32;
    gpegc->currentmatcher->value.range.until = 127;
  }

  return 0;
}

int gpegc_handle_post_MACRO
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

int gpegc_handle_MATCHER
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

int gpegc_handle_post_MATCHER
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

int gpegc_handle_NOT
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->modifier = GPEGC_MODI_NOT;

  return 0;
}

int gpegc_handle_post_NOT
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

int gpegc_handle_NUMBER
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

int gpegc_handle_post_NUMBER
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

int gpegc_handle_OPTNAMESPACE
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

int gpegc_handle_post_OPTNAMESPACE
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

int gpegc_handle_OR
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

int gpegc_handle_post_OR
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

int gpegc_handle_QUANTIFIEDMATCHER
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  if (capture->children.count == 2) { // ie there *is* a quantifier
    capture->attachment.value_ptr = gpegc->currentmatcher;
  }

  return 0;
}

int gpegc_handle_post_QUANTIFIEDMATCHER
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  if (capture->children.count == 2) { // ie there *is* a quantifier
    gpegc_matcher_t* matcher = capture->attachment.value_ptr;
    if (gpegc->currentquantifier[ 0 ] || gpegc->currentquantifier[ 1 ]) {
      matcher->quantifier[ 0 ] = gpegc->currentquantifier[ 0 ];
      matcher->quantifier[ 1 ] = gpegc->currentquantifier[ 1 ];
      gpegc->currentquantifier[ 0 ] = 0;
      gpegc->currentquantifier[ 1 ] = 0;
    }
  }

  return 0;
}

int gpegc_handle_QUANTIFIER
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

int gpegc_handle_post_QUANTIFIER
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

int gpegc_handle_Q_FROM
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentquantifier[ 0 ] =
    atoi((char*)(capture->children.list[ 0 ].data.data));
  gpegc->currentquantifier[ 1 ] = -1;

  return 0;
}

int gpegc_handle_post_Q_FROM
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

int gpegc_handle_Q_FROMTO
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentquantifier[ 0 ] =
    atoi((char*)(capture->children.list[ 0 ].data.data));
  gpegc->currentquantifier[ 1 ] =
    atoi((char*)(capture->children.list[ 1 ].data.data));

  return 0;
}

int gpegc_handle_post_Q_FROMTO
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

int gpegc_handle_Q_FROMTO_0
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

int gpegc_handle_post_Q_FROMTO_0
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

int gpegc_handle_Q_FROMTO_1
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

int gpegc_handle_post_Q_FROMTO_1
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

int gpegc_handle_Q_FROM_0
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

int gpegc_handle_post_Q_FROM_0
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

int gpegc_handle_Q_ONEORMORE
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentquantifier[ 0 ] = 1;
  gpegc->currentquantifier[ 1 ] = -1;

  return 0;
}

int gpegc_handle_post_Q_ONEORMORE
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

int gpegc_handle_Q_SPECIFIC
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentquantifier[ 0 ] =
    atoi((char*)(capture->children.list[0].data.data));
  gpegc->currentquantifier[ 1 ] =
    gpegc->currentquantifier[ 0 ];

  return 0;
}

int gpegc_handle_post_Q_SPECIFIC
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

int gpegc_handle_Q_SPECIFIC_0
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

int gpegc_handle_post_Q_SPECIFIC_0
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

int gpegc_handle_Q_UNTIL
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentquantifier[ 0 ] = 0;
  gpegc->currentquantifier[ 1 ] =
    atoi((char*)(capture->children.list[ 0 ].data.data));

  return 0;
}

int gpegc_handle_post_Q_UNTIL
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

int gpegc_handle_Q_UNTIL_0
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

int gpegc_handle_post_Q_UNTIL_0
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

int gpegc_handle_Q_VAR
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

int gpegc_handle_post_Q_VAR
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

int gpegc_handle_Q_ZEROORMORE
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentquantifier[ 0 ] = 0;
  gpegc->currentquantifier[ 1 ] = -1;

  return 0;
}

int gpegc_handle_post_Q_ZEROORMORE
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

int gpegc_handle_Q_ZEROORONE
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentquantifier[ 0 ] = 0;
  gpegc->currentquantifier[ 1 ] = 1;

  return 0;
}

int gpegc_handle_post_Q_ZEROORONE
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

int gpegc_handle_REFERENCE
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;

  gpegc_t* gpegc = arg;
  char* name = (char*)(capture->data.data);

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_REFERENCE;
  gpegc->currentmatcher->value.string.value = name;
  if (!(stringlist_has(&(gpegc->namespace), name))) {
    vec_printf(&(gpegc->compiler->error), "Rule '%s' not found.\n", name);
    return GPEG_ERR_NOTFOUND.code;
  }

  return 0;
}

int gpegc_handle_post_REFERENCE
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

int gpegc_handle_RULE
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) {
    char* name = (char*)(capture->children.list[ 0 ].data.data);
    stringlist_push(&(gpegc->namespace), name);
    return 0;
  }

  gpegc->currentrule.name = (char*)(capture->children.list[ 0 ].data.data);
  gpegc->currentrule.slotcount = 0;
  gpegc->currentmatcherlist = &(gpegc->currentrule.matchers);
  if (NULL == gpegc->startrule) {
    gpegc->startrule = (char*)(capture->children.list[ 0 ].data.data);
  }

  if (gpegc->compiler->flags & GPEGC_FLAG_GENTRAPS) {
    vec_printf(&(gpegc->compiler->output), "  trap\n");
  }
  vec_printf(&(gpegc->compiler->output), "%s:\n", gpegc->currentrule.name);
  if (gpegc->prefixgiven) {
    vec_printf(&(gpegc->compiler->output), "  call __prefix\n");
  }
  if ((gpegc->compiler->flags & GPEGC_FLAG_GENCAPTURES)
      && strcmp(gpegc->currentrule.name, "__prefix"))
  {
    gpegc->currentrule.slot = (gpegc->cslot)++;
    vec_printf(&(gpegc->compiler->output), "  opencapture %u\n"
                                           , gpegc->currentrule.slot);

    char slotname[ 128 ];
    snprintf(slotname, sizeof(slotname), "%s" , gpegc->currentrule.name);
    str2int_map_put(&(gpegc->slotmap), strdup(slotname), gpegc->currentrule.slot);
  }

  return 0;
}

int gpegc_handle_post_RULE
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

  gpegc_t* gpegc = arg;
  GPEG_ERR_T e;

  if (gpegc->round == 0) { return 0; }

  e = gpegc_matcherlist(gpegc, &(gpegc->currentrule.matchers));
  if ((gpegc->compiler->flags & GPEGC_FLAG_GENCAPTURES)
      && strcmp(gpegc->currentrule.name, "__prefix"))
  {
    vec_printf(&(gpegc->compiler->output), "  closecapture %u\n"
                                           , gpegc->currentrule.slot);
  }
  vec_printf(&(gpegc->compiler->output), "  ret\n\n");
  if (gpegc->compiler->flags & GPEGC_FLAG_GENTRAPS) {
    vec_printf(&(gpegc->compiler->output), "  trap\n");
  }
  if (0 == strcmp(gpegc->currentrule.name, "__prefix")) {
    gpegc->prefixgiven = 1;
  }
  if (e.code) {
    return e.code;
  }
  if (0 == strcmp(gpegc->currentrule.name, "__main")) {
    gpegc->startrule = gpegc->currentrule.name;
  }
  gpegc->currentrule.name = NULL;
  gpegc_matcherlist_free(&(gpegc->currentrule.matchers));
  gpegc->currentmatcher = NULL;
  gpegc->currentmatcherlist = NULL;

  return 0;
}

IGNOREHANDLER(S)

int gpegc_handle_SCANMATCHER
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

int gpegc_handle_post_SCANMATCHER
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

IGNOREHANDLER(SEMICOLON)

int gpegc_handle_SET
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

int gpegc_handle_post_SET
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_SET;

  return 0;
}

int gpegc_handle_SET_0
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  if (capture->data.data[ 0 ] == '^') {
    gpegc->currentmatcher->value.set.inverted = 1;
  }

  return 0;
}

int gpegc_handle_post_SET_0
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

static
unsigned get_bit
  (char* str)
{
  if (*str == '\\') {
    return unescape(str[ 1 ]);
  } else if (str[ 0 ] == '0' && str[ 1 ] == 'x') {
    return (hexchar(str[ 2 ]) << 4) | hexchar(str[ 3 ]);
  } else {
    return str[ 0 ];
  }
}

int gpegc_handle_SET_3
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

  gpegc_t* gpegc = arg;
  unsigned bit = get_bit((char*)(capture->data.data));

  if (gpegc->round == 0) { return 0; }

  set_bit(gpegc->currentmatcher->value.set.bitmask, bit);

  return 0;
}

int gpegc_handle_post_SET_1
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

int gpegc_handle_SET_1
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

  gpegc_t* gpegc = arg;
  unsigned bit = get_bit((char*)(capture->data.data));

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->value.set.from = bit;

  return 0;
}

int gpegc_handle_post_SET_2
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

int gpegc_handle_SET_2
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

  gpegc_t* gpegc = arg;
  unsigned bit = get_bit((char*)(capture->data.data));

  if (gpegc->round == 0) { return 0; }

  for (unsigned i=gpegc->currentmatcher->value.set.from; i <= bit; i++) {
    set_bit(gpegc->currentmatcher->value.set.bitmask, i);
  }

  return 0;
}

int gpegc_handle_post_SET_3
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

int gpegc_handle_STRING
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  if (capture->data.data[ capture->data.size-1 ] == 'i') {
    gpegc->currentmatcher->caseinsensitive = 1;
  }

  return 0;
}

int gpegc_handle_post_STRING
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

int gpegc_handle_STRINGLITERAL
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

int gpegc_handle_post_STRINGLITERAL
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

int gpegc_handle_STRINGLITERAL_0
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  if (gpegc->importdecl) {
    DEBUGMSG("Importing %s\n", (char*)(capture->data.data));
    GPEG_ERR_T e = gpegc_import(gpegc, (char*)(capture->data.data));
    if (e.code) {
      return e.code;
    }
  } else {
    gpegc->currentmatcher->type = GPEGC_MATCH_STRING;
    gpegc->currentmatcher->value.string.value = (char*)(capture->data.data);
  }

  return 0;
}

int gpegc_handle_post_STRINGLITERAL_0
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

int gpegc_handle_TERM
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

  gpegc_t* gpegc = arg;
  gpegc_matcher_t matcher = { 0 };

  if (gpegc->round == 0) { return 0; }

  gpegc_matcherlist_push(gpegc->currentmatcherlist, matcher);
  gpegc->currentmatcher = gpegc_matcherlist_peekptr(gpegc->currentmatcherlist);

  return 0;
}

int gpegc_handle_post_TERM
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

int gpegc_handle_TERMS
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

int gpegc_handle_post_TERMS
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

int gpegc_handle_TYPE
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

int gpegc_handle_post_TYPE
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

int gpegc_handle_VARCAPTURE
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

  gpegc_t* gpegc = arg;
  char slotname[ 128 ];

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_CAPTURE;
  gpegc->currentmatcher->value.capture.slot = (gpegc->cslot)++;
  snprintf(slotname, sizeof(slotname),
    "%s"
    , capture->children.list[ 2 ].data.data
  );
  str2int_map_put(
    &(gpegc->slotmap),
    strdup(slotname),
    gpegc->currentmatcher->value.capture.slot
  );
  capture->attachment.value_ptr = gpegc->currentmatcherlist;
  gpegc->currentmatcherlist = &(gpegc->currentmatcher->group);

  return 0;
}

int gpegc_handle_post_VARCAPTURE
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcherlist = capture->attachment.value_ptr;

  return 0;
}

int gpegc_handle_VARREFERENCE
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

  gpegc_t* gpegc = arg;

  if (gpegc->round == 0) { return 0; }

  gpegc->currentmatcher->type = GPEGC_MATCH_VARIABLE;
  gpegc->currentmatcher->value.string.value = (char*)(capture->data.data);

  return 0;
}

IGNOREPOSTHANDLER(VARREFERENCE)
