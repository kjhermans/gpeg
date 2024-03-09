#include "gpegc_private.h"
#include "grammar.slotmap.h"

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

IGNOREHANDLER(ABCLOSE)
IGNOREHANDLER(ABOPEN)

int handle_AND
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

  gpegc->currentmatcher->modifier = GPEGC_MODI_AND;

  return 0;
}

int handle_post_AND
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

int handle_ANY
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
  gpegc->currentmatcher->type = GPEGC_MATCH_ANY;

  return 0;
}

int handle_post_ANY
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

IGNOREHANDLER(BCLOSE)

int handle_BITMASK
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

int handle_post_BITMASK
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

IGNOREHANDLER(BOPEN)

int handle_CAPTURE
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

  gpegc->currentmatcher->type = GPEGC_MATCH_CAPTURE;
  gpegc->currentmatcher->value.capture = (gpegc->cslot)++;
  capture->attachment.value_ptr = gpegc->currentmatcherlist;
  gpegc->currentmatcherlist = &(gpegc->currentmatcher->group);

  return 0;
}

int handle_post_CAPTURE
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

  gpegc->currentmatcherlist = capture->attachment.value_ptr;

  return 0;
}

int handle_CAPTUREEND
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

int handle_post_CAPTUREEND
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

int handle_CAPTURETYPE
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

int handle_post_CAPTURETYPE
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

int handle_DEFINITION
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

int handle_post_DEFINITION
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

int handle_END
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

int handle_post_END
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

int handle_ENDFORCE
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

  gpegc->currentmatcher->type = GPEGC_MATCH_ENDFORCE;
  gpegc->currentmatcher->value.number = atoi(
    (char*)(capture->children.list[ 0 ].data.data)
  );

  return 0;
}

int handle_post_ENDFORCE
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

int handle_EXPRESSION
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

  if (capture->children.count > 1) {
    capture->attachment.value_ptr = gpegc->currentmatcherlist;
  }

  return 0;
}

int handle_post_EXPRESSION
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

  if (capture->children.count > 1) {
    gpegc->currentmatcherlist = capture->attachment.value_ptr;
  }

  return 0;
}

int handle_EXPRESSION_0
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

  m.type = GPEGC_MATCH_CHOICE;
  for (unsigned i=0; i < gpegc->currentmatcherlist->count; i++) {
    gpegc_matcherlist_push(&(m.group), gpegc->currentmatcherlist->list[ i ]);
  }
  gpegc->currentmatcherlist->count = 0;
  gpegc_matcherlist_push(gpegc->currentmatcherlist, m);
  _m = gpegc_matcherlist_peekptr(gpegc->currentmatcherlist);
//  capture->attachment.value_ptr = gpegc->currentmatcherlist;
  gpegc->currentmatcherlist = &(_m->altgroup);

  return 0;
}

int handle_post_EXPRESSION_0
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

//  gpegc_t* gpegc = arg;

//  gpegc->currentmatcherlist = capture->attachment.value_ptr;

  return 0;
}

int handle_FATARROW
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

int handle_post_FATARROW
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

int handle_GRAMMAR
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

int handle_post_GRAMMAR
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

int handle_GROUP
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

  gpegc->currentmatcher->type = GPEGC_MATCH_GROUP;
  capture->attachment.value_ptr = gpegc->currentmatcherlist;
  gpegc->currentmatcherlist = &(gpegc->currentmatcher->group);

  return 0;
}

int handle_post_GROUP
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

int handle_HEXLITERAL
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

  gpegc->currentmatcher->type = GPEGC_MATCH_CHAR;
  gpegc->currentmatcher->value.chr =
    (hexchar(capture->data.data[ 2 ]) << 4) |
     hexchar(capture->data.data[ 3 ]);

  return 0;
}

int handle_post_HEXLITERAL
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

int handle_IDENT
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

int handle_post_IDENT
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

int handle_IMPORTDECL
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

int handle_post_IMPORTDECL
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

int handle_KW_AS
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

int handle_post_KW_AS
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

int handle_KW_IMPORT
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

int handle_post_KW_IMPORT
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

int handle_LCMODES
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

int handle_post_LCMODES
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

int handle_LCPARAM
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

int handle_post_LCPARAM
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

int handle_LEFTARROW
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

int handle_post_LEFTARROW
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

int handle_LIMITEDCALL
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

int handle_post_LIMITEDCALL
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

int handle_MACRO
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
    set_bits(gpegc->currentmatcher->value.set.bitmask, 32, 127);
  }

  return 0;
}

int handle_post_MACRO
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

int handle_MATCHER
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

int handle_post_MATCHER
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

int handle_NOT
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

  gpegc->currentmatcher->modifier = GPEGC_MODI_NOT;

  return 0;
}

int handle_post_NOT
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

int handle_NUMBER
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

int handle_post_NUMBER
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

int handle_OPTNAMESPACE
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

int handle_post_OPTNAMESPACE
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

int handle_OR
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

int handle_post_OR
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

int handle_QUANTIFIEDMATCHER
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

int handle_post_QUANTIFIEDMATCHER
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

int handle_QUANTIFIER
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

int handle_post_QUANTIFIER
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

int handle_Q_FROM
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

  gpegc->currentmatcher->quantifier[ 0 ] =
    atoi((char*)(capture->children.list[ 0 ].data.data));
  gpegc->currentmatcher->quantifier[ 1 ] = -1;

  return 0;
}

int handle_post_Q_FROM
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

int handle_Q_FROMTO
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

  gpegc->currentmatcher->quantifier[ 0 ] =
    atoi((char*)(capture->children.list[ 0 ].data.data));
  gpegc->currentmatcher->quantifier[ 1 ] =
    atoi((char*)(capture->children.list[ 1 ].data.data));

  return 0;
}

int handle_post_Q_FROMTO
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

int handle_Q_FROMTO_0
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

int handle_post_Q_FROMTO_0
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

int handle_Q_FROMTO_1
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

int handle_post_Q_FROMTO_1
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

int handle_Q_FROM_0
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

int handle_post_Q_FROM_0
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

int handle_Q_ONEORMORE
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

  gpegc->currentmatcher->quantifier[ 0 ] = 1;
  gpegc->currentmatcher->quantifier[ 1 ] = -1;

  return 0;
}

int handle_post_Q_ONEORMORE
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

int handle_Q_SPECIFIC
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

  gpegc->currentmatcher->quantifier[ 0 ] =
    atoi((char*)(capture->children.list[0].data.data));
  gpegc->currentmatcher->quantifier[ 1 ] =
    gpegc->currentmatcher->quantifier[ 0 ];

  return 0;
}

int handle_post_Q_SPECIFIC
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

int handle_Q_SPECIFIC_0
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

int handle_post_Q_SPECIFIC_0
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

int handle_Q_UNTIL
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

  gpegc->currentmatcher->quantifier[ 0 ] = 0;
  gpegc->currentmatcher->quantifier[ 1 ] =
    atoi((char*)(capture->children.list[ 0 ].data.data));

  return 0;
}

int handle_post_Q_UNTIL
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

int handle_Q_UNTIL_0
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

int handle_post_Q_UNTIL_0
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

int handle_Q_VAR
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

int handle_post_Q_VAR
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

int handle_Q_ZEROORMORE
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

  gpegc->currentmatcher->quantifier[ 0 ] = 0;
  gpegc->currentmatcher->quantifier[ 1 ] = -1;

  return 0;
}

int handle_post_Q_ZEROORMORE
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

int handle_Q_ZEROORONE
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

  gpegc->currentmatcher->quantifier[ 0 ] = 0;
  gpegc->currentmatcher->quantifier[ 1 ] = 1;

  return 0;
}

int handle_post_Q_ZEROORONE
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

int handle_RECYCLE
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

int handle_post_RECYCLE
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

int handle_REFERENCE
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

  gpegc->currentmatcher->type = GPEGC_MATCH_REFERENCE;
  gpegc->currentmatcher->value.string = (char*)(capture->data.data);

  return 0;
}

int handle_post_REFERENCE
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

int handle_REPLACE
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

int handle_post_REPLACE
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

int handle_REPLACETERM
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

int handle_post_REPLACETERM
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

int handle_REPLACETERMS
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

int handle_post_REPLACETERMS
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

int handle_RIGHTARROW
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

int handle_post_RIGHTARROW
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

int handle_RULE
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

  gpegc->currentrule.name = (char*)(capture->children.list[ 0 ].data.data);
  gpegc->currentmatcherlist = &(gpegc->currentrule.matchers);
  if (NULL == gpegc->startrule) {
    gpegc->startrule = (char*)(capture->children.list[ 0 ].data.data);
  }

  return 0;
}

int handle_post_RULE
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
  unsigned slot = 0;

  vec_printf(gpegc->output, "%s:\n", gpegc->currentrule.name);
  if (gpegc->prefixgiven) {
    vec_printf(gpegc->output, "  call __prefix\n");
  }
  if (gpegc->rulecapture) {
    slot = (gpegc->cslot)++;
    vec_printf(gpegc->output, "  opencapture %u\n", slot);
  }
  e = gpegc_matcherlist(gpegc, &(gpegc->currentrule.matchers));
  if (gpegc->rulecapture) {
    vec_printf(gpegc->output, "  closecapture %u\n", slot);
  }
  vec_printf(gpegc->output, "  ret\n\n");
  if (0 == strcmp(gpegc->currentrule.name, "__prefix")) {
    gpegc->prefixgiven = 1;
  }
  if (e.code) {
    return e.code;
  }
  gpegc->currentrule.name = NULL;
// the following function will not free 'child' matcherlists
  gpegc_matcherlist_free(&(gpegc->currentrule.matchers));
  gpegc->currentmatcher = NULL;
  gpegc->currentmatcherlist = NULL;

  return 0;
}

IGNOREHANDLER(S)

int handle_SCANMATCHER
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

int handle_post_SCANMATCHER
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

int handle_SET
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

int handle_post_SET
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

  gpegc->currentmatcher->type = GPEGC_MATCH_SET;

  return 0;
}

int handle_SET_0
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

  if (capture->data.data[ 0 ] == '^') {
    gpegc->currentmatcher->value.set.inverted = 1;
  }

  return 0;
}

int handle_post_SET_0
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

int handle_SET_3
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

  set_bit(gpegc->currentmatcher->value.set.bitmask, bit);

  return 0;
}

int handle_post_SET_1
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

int handle_SET_1
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

  gpegc->currentmatcher->value.set.from = bit;

  return 0;
}

int handle_post_SET_2
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

int handle_SET_2
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

  for (unsigned i=gpegc->currentmatcher->value.set.from; i <= bit; i++) {
    set_bit(gpegc->currentmatcher->value.set.bitmask, i);
  }

  return 0;
}

int handle_post_SET_3
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

int handle_STRING
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

  if (capture->data.data[ capture->data.size-1 ] == 'i') {
    gpegc->currentmatcher->caseinsensitive = 1;
  }

  return 0;
}

int handle_post_STRING
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

int handle_STRINGLITERAL
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

int handle_post_STRINGLITERAL
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

int handle_STRINGLITERAL_0
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

  gpegc->currentmatcher->type = GPEGC_MATCH_STRING;
  gpegc->currentmatcher->value.string = (char*)(capture->data.data);

  return 0;
}

int handle_post_STRINGLITERAL_0
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

int handle_TERM
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

  gpegc_matcherlist_push(gpegc->currentmatcherlist, matcher);
  gpegc->currentmatcher = gpegc_matcherlist_peekptr(gpegc->currentmatcherlist);

  return 0;
}

int handle_post_TERM
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

int handle_TERMS
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

int handle_post_TERMS
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

int handle_TYPE
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

int handle_post_TYPE
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

int handle_VARCAPTURE
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

int handle_post_VARCAPTURE
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

int handle_VARREFERENCE
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

int handle_post_VARREFERENCE
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
