#include <gpeg/lib/gpeg/gpeg_capturelist.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

extern int gpegc_grammar_process_node(gpeg_capture_t*,void*);
static int do_node(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);

extern int gpegc_handle_GRAMMAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_GRAMMAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_DEFINITION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_DEFINITION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_RULE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_RULE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_EXPRESSION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_EXPRESSION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_EXPRESSION_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_EXPRESSION_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_TERMS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_TERMS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_TERM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_TERM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SCANMATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SCANMATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_QUANTIFIEDMATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_QUANTIFIEDMATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_QUANTIFIER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_QUANTIFIER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_ZEROORONE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_ZEROORONE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_ONEORMORE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_ONEORMORE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_ZEROORMORE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_ZEROORMORE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROMTO(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROMTO(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROMTO_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROMTO_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROMTO_1(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROMTO_1(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_UNTIL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_UNTIL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_UNTIL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_UNTIL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROM_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROM_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_SPECIFIC(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_SPECIFIC(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_SPECIFIC_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_SPECIFIC_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_VAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_VAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_MATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_MATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_BITMASK(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_BITMASK(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_VARCAPTURE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_VARCAPTURE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_CAPTURETYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_CAPTURETYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_TYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_TYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_CAPTURE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_CAPTURE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_GROUP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_GROUP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET_1(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET_1(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET_2(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET_2(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET_3(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET_3(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_VARREFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_VARREFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_REFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_REFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_LIMITEDCALL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_LIMITEDCALL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_LCMODES(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_LCMODES(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_LCPARAM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_LCPARAM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_LEFTARROW(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_LEFTARROW(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_NOT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_NOT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_AND(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_AND(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_MACRO(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_MACRO(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_ENDFORCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_ENDFORCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_HEXLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_HEXLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_NUMBER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_NUMBER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_STRING(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_STRING(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_OR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_OR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_ANY(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_ANY(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_IMPORTDECL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_IMPORTDECL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_KW_IMPORT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_KW_IMPORT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_OPTNAMESPACE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_OPTNAMESPACE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_KW_AS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_KW_AS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_STRINGLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_STRINGLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_STRINGLITERAL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_STRINGLITERAL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_IDENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_IDENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_BOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_BOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_BCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_BCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_CBOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_CBOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_CBCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_CBCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_ABOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_ABOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_ABCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_ABCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_COLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_COLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SEMICOLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SEMICOLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);

int gpegc_grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
{
  return do_node(0, 0, capture, ptr);
}

static
int do_node
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* ptr
  )
{
  int e;
  unsigned indices[ 69 ] = { 0 };

  switch (capture->type) {
  case 0:
    {
      ++indices[ 0 ];
      if ((e = gpegc_handle_GRAMMAR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 0 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_GRAMMAR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 1:
    {
      ++indices[ 1 ];
      if ((e = gpegc_handle_S(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 1 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_S(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 2:
    {
      ++indices[ 2 ];
      if ((e = gpegc_handle_MULTILINECOMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 2 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_MULTILINECOMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 3:
    {
      ++indices[ 3 ];
      if ((e = gpegc_handle_COMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 3 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_COMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 4:
    {
      ++indices[ 4 ];
      if ((e = gpegc_handle_END(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 4 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_END(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 5:
    {
      ++indices[ 5 ];
      if ((e = gpegc_handle_DEFINITION(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 5 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_DEFINITION(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 6:
    {
      ++indices[ 6 ];
      if ((e = gpegc_handle_RULE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 6 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_RULE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 7:
    {
      ++indices[ 7 ];
      if ((e = gpegc_handle_EXPRESSION(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 7 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_EXPRESSION(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 8:
    {
      ++indices[ 8 ];
      if ((e = gpegc_handle_EXPRESSION_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 8 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_EXPRESSION_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 9:
    {
      ++indices[ 9 ];
      if ((e = gpegc_handle_TERMS(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 9 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_TERMS(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 10:
    {
      ++indices[ 10 ];
      if ((e = gpegc_handle_TERM(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 10 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_TERM(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 11:
    {
      ++indices[ 11 ];
      if ((e = gpegc_handle_SCANMATCHER(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 11 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_SCANMATCHER(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 12:
    {
      ++indices[ 12 ];
      if ((e = gpegc_handle_QUANTIFIEDMATCHER(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 12 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_QUANTIFIEDMATCHER(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 13:
    {
      ++indices[ 13 ];
      if ((e = gpegc_handle_QUANTIFIER(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 13 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_QUANTIFIER(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 14:
    {
      ++indices[ 14 ];
      if ((e = gpegc_handle_Q_ZEROORONE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 14 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_ZEROORONE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 15:
    {
      ++indices[ 15 ];
      if ((e = gpegc_handle_Q_ONEORMORE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 15 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_ONEORMORE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 16:
    {
      ++indices[ 16 ];
      if ((e = gpegc_handle_Q_ZEROORMORE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 16 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_ZEROORMORE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 17:
    {
      ++indices[ 17 ];
      if ((e = gpegc_handle_Q_FROMTO(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 17 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_FROMTO(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 18:
    {
      ++indices[ 18 ];
      if ((e = gpegc_handle_Q_FROMTO_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 18 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_FROMTO_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 19:
    {
      ++indices[ 19 ];
      if ((e = gpegc_handle_Q_FROMTO_1(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 19 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_FROMTO_1(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 20:
    {
      ++indices[ 20 ];
      if ((e = gpegc_handle_Q_UNTIL(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 20 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_UNTIL(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 21:
    {
      ++indices[ 21 ];
      if ((e = gpegc_handle_Q_UNTIL_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 21 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_UNTIL_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 22:
    {
      ++indices[ 22 ];
      if ((e = gpegc_handle_Q_FROM(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 22 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_FROM(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 23:
    {
      ++indices[ 23 ];
      if ((e = gpegc_handle_Q_FROM_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 23 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_FROM_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 24:
    {
      ++indices[ 24 ];
      if ((e = gpegc_handle_Q_SPECIFIC(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 24 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_SPECIFIC(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 25:
    {
      ++indices[ 25 ];
      if ((e = gpegc_handle_Q_SPECIFIC_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 25 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_SPECIFIC_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 26:
    {
      ++indices[ 26 ];
      if ((e = gpegc_handle_Q_VAR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 26 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_Q_VAR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 27:
    {
      ++indices[ 27 ];
      if ((e = gpegc_handle_MATCHER(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 27 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_MATCHER(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 28:
    {
      ++indices[ 28 ];
      if ((e = gpegc_handle_BITMASK(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 28 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_BITMASK(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 29:
    {
      ++indices[ 29 ];
      if ((e = gpegc_handle_VARCAPTURE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 29 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_VARCAPTURE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 30:
    {
      ++indices[ 30 ];
      if ((e = gpegc_handle_CAPTURETYPE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 30 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_CAPTURETYPE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 31:
    {
      ++indices[ 31 ];
      if ((e = gpegc_handle_TYPE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 31 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_TYPE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 32:
    {
      ++indices[ 32 ];
      if ((e = gpegc_handle_CAPTURE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 32 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_CAPTURE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 33:
    {
      ++indices[ 33 ];
      if ((e = gpegc_handle_GROUP(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 33 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_GROUP(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 34:
    {
      ++indices[ 34 ];
      if ((e = gpegc_handle_SET(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 34 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_SET(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 35:
    {
      ++indices[ 35 ];
      if ((e = gpegc_handle_SET_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 35 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_SET_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 36:
    {
      ++indices[ 36 ];
      if ((e = gpegc_handle_SET_1(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 36 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_SET_1(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 37:
    {
      ++indices[ 37 ];
      if ((e = gpegc_handle_SET_2(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 37 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_SET_2(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 38:
    {
      ++indices[ 38 ];
      if ((e = gpegc_handle_SET_3(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 38 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_SET_3(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 39:
    {
      ++indices[ 39 ];
      if ((e = gpegc_handle_VARREFERENCE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 39 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_VARREFERENCE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 40:
    {
      ++indices[ 40 ];
      if ((e = gpegc_handle_REFERENCE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 40 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_REFERENCE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 41:
    {
      ++indices[ 41 ];
      if ((e = gpegc_handle_LIMITEDCALL(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 41 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_LIMITEDCALL(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 42:
    {
      ++indices[ 42 ];
      if ((e = gpegc_handle_LCMODES(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 42 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_LCMODES(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 43:
    {
      ++indices[ 43 ];
      if ((e = gpegc_handle_LCPARAM(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 43 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_LCPARAM(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 44:
    {
      ++indices[ 44 ];
      if ((e = gpegc_handle_LEFTARROW(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 44 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_LEFTARROW(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 45:
    {
      ++indices[ 45 ];
      if ((e = gpegc_handle_NOT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 45 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_NOT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 46:
    {
      ++indices[ 46 ];
      if ((e = gpegc_handle_AND(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 46 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_AND(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 47:
    {
      ++indices[ 47 ];
      if ((e = gpegc_handle_MACRO(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 47 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_MACRO(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 48:
    {
      ++indices[ 48 ];
      if ((e = gpegc_handle_ENDFORCE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 48 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_ENDFORCE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 49:
    {
      ++indices[ 49 ];
      if ((e = gpegc_handle_HEXLITERAL(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 49 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_HEXLITERAL(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 50:
    {
      ++indices[ 50 ];
      if ((e = gpegc_handle_NUMBER(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 50 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_NUMBER(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 51:
    {
      ++indices[ 51 ];
      if ((e = gpegc_handle_STRING(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 51 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_STRING(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 52:
    {
      ++indices[ 52 ];
      if ((e = gpegc_handle_OR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 52 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_OR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 53:
    {
      ++indices[ 53 ];
      if ((e = gpegc_handle_ANY(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 53 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_ANY(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 54:
    {
      ++indices[ 54 ];
      if ((e = gpegc_handle_IMPORTDECL(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 54 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_IMPORTDECL(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 55:
    {
      ++indices[ 55 ];
      if ((e = gpegc_handle_KW_IMPORT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 55 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_KW_IMPORT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 56:
    {
      ++indices[ 56 ];
      if ((e = gpegc_handle_OPTNAMESPACE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 56 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_OPTNAMESPACE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 57:
    {
      ++indices[ 57 ];
      if ((e = gpegc_handle_KW_AS(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 57 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_KW_AS(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 58:
    {
      ++indices[ 58 ];
      if ((e = gpegc_handle_STRINGLITERAL(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 58 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_STRINGLITERAL(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 59:
    {
      ++indices[ 59 ];
      if ((e = gpegc_handle_STRINGLITERAL_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 59 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_STRINGLITERAL_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 60:
    {
      ++indices[ 60 ];
      if ((e = gpegc_handle_IDENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 60 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_IDENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 61:
    {
      ++indices[ 61 ];
      if ((e = gpegc_handle_BOPEN(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 61 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_BOPEN(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 62:
    {
      ++indices[ 62 ];
      if ((e = gpegc_handle_BCLOSE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 62 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_BCLOSE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 63:
    {
      ++indices[ 63 ];
      if ((e = gpegc_handle_CBOPEN(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 63 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_CBOPEN(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 64:
    {
      ++indices[ 64 ];
      if ((e = gpegc_handle_CBCLOSE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 64 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_CBCLOSE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 65:
    {
      ++indices[ 65 ];
      if ((e = gpegc_handle_ABOPEN(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 65 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_ABOPEN(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 66:
    {
      ++indices[ 66 ];
      if ((e = gpegc_handle_ABCLOSE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 66 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_ABCLOSE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 67:
    {
      ++indices[ 67 ];
      if ((e = gpegc_handle_COLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 67 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_COLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 68:
    {
      ++indices[ 68 ];
      if ((e = gpegc_handle_SEMICOLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 68 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegc_handle_post_SEMICOLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  }
  return 0;
}
