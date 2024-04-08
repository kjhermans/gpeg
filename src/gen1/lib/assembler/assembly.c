
#include <gpeg/lib/gpeg/gpeg_capturelist.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

extern int grammar_process_node(gpeg_capture_t*, void*);
static int do_node(gpeg_capture_t*, unsigned, gpeg_capture_t*, void*);

extern int handle_AMPERSAND(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_AMPERSAND(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_ANYINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_ANYINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_BACKCOMMITINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_BACKCOMMITINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_BITMASKINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_BITMASKINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_CALLINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_CALLINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_CATCHINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_CATCHINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_CHARINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_CHARINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_CLOSECAPTUREINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_CLOSECAPTUREINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_CODE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_CODE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_COLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_COLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_COMMITINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_COMMITINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_CONDJUMPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_CONDJUMPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_COUNTERINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_COUNTERINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_ENDINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_ENDINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_ENDISOLATEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_ENDISOLATEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_ENDREPLACEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_ENDREPLACEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_FAILINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_FAILINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_FAILTWICEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_FAILTWICEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_HEXBYTE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_HEXBYTE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_HEXQUAD(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_HEXQUAD(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_INSTRUCTION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_INSTRUCTION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_INSTRUCTIONS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_INSTRUCTIONS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_INTRPCAPTUREINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_INTRPCAPTUREINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_INTRPCAPTURETYPES(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_INTRPCAPTURETYPES(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_INTRPCAPTURETYPES_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_INTRPCAPTURETYPES_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_ISOLATEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_ISOLATEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_JUMPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_JUMPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_LABEL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_LABEL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_LABELDEF(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_LABELDEF(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_NOOPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_NOOPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_NUMBER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_NUMBER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_OPENCAPTUREINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_OPENCAPTUREINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_PARTIALCOMMITINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_PARTIALCOMMITINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_QUAD(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_QUAD(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_QUADINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_QUADINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_RANGEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_RANGEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_REGISTER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_REGISTER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_REPLACEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_REPLACEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_RETINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_RETINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_RULEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_RULEINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_SET(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_SET(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_SETINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_SETINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_SKIPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_SKIPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_SLOT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_SLOT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_SPANINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_SPANINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_STRINGLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_STRINGLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_STRINGLITERAL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_STRINGLITERAL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_TESTANYINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_TESTANYINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_TESTCHARINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_TESTCHARINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_TESTQUADINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_TESTQUADINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_TESTSETINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_TESTSETINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_TOP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_TOP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_TRAPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_TRAPINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_TYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_TYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_UNSIGNED(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_UNSIGNED(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_VARINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_VARINSTR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);



int grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
{
  return do_node(0, 0, capture, ptr);
}
 
static
int do_node
  (gpeg_capture_t* parent, unsigned index, gpeg_capture_t* capture, void* ptr)
{
  int e;
  unsigned indices[ 60 ] = { 0 };

  switch (capture->type) {
  case 55:
    {
      ++(indices[ 55 ]);
      if ((e = handle_AMPERSAND(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 55 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_AMPERSAND(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 8:
    {
      ++(indices[ 8 ]);
      if ((e = handle_ANYINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 8 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_ANYINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 9:
    {
      ++(indices[ 9 ]);
      if ((e = handle_BACKCOMMITINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 9 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_BACKCOMMITINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 13:
    {
      ++(indices[ 13 ]);
      if ((e = handle_BITMASKINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 13 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_BITMASKINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 10:
    {
      ++(indices[ 10 ]);
      if ((e = handle_CALLINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 10 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_CALLINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 11:
    {
      ++(indices[ 11 ]);
      if ((e = handle_CATCHINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 11 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_CATCHINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 12:
    {
      ++(indices[ 12 ]);
      if ((e = handle_CHARINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 12 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_CHARINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 14:
    {
      ++(indices[ 14 ]);
      if ((e = handle_CLOSECAPTUREINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 14 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_CLOSECAPTUREINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 43:
    {
      ++(indices[ 43 ]);
      if ((e = handle_CODE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 43 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_CODE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 54:
    {
      ++(indices[ 54 ]);
      if ((e = handle_COLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 54 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_COLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 3:
    {
      ++(indices[ 3 ]);
      if ((e = handle_COMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 3 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_COMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 15:
    {
      ++(indices[ 15 ]);
      if ((e = handle_COMMITINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 15 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_COMMITINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 39:
    {
      ++(indices[ 39 ]);
      if ((e = handle_CONDJUMPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 39 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_CONDJUMPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 38:
    {
      ++(indices[ 38 ]);
      if ((e = handle_COUNTERINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 38 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_COUNTERINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 7:
    {
      ++(indices[ 7 ]);
      if ((e = handle_END(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 7 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_END(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 16:
    {
      ++(indices[ 16 ]);
      if ((e = handle_ENDINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 16 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_ENDINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 41:
    {
      ++(indices[ 41 ]);
      if ((e = handle_ENDISOLATEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 41 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_ENDISOLATEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 27:
    {
      ++(indices[ 27 ]);
      if ((e = handle_ENDREPLACEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 27 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_ENDREPLACEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 17:
    {
      ++(indices[ 17 ]);
      if ((e = handle_FAILINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 17 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_FAILINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 18:
    {
      ++(indices[ 18 ]);
      if ((e = handle_FAILTWICEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 18 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_FAILTWICEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 44:
    {
      ++(indices[ 44 ]);
      if ((e = handle_HEXBYTE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 44 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_HEXBYTE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 45:
    {
      ++(indices[ 45 ]);
      if ((e = handle_HEXQUAD(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 45 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_HEXQUAD(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 5:
    {
      ++(indices[ 5 ]);
      if ((e = handle_INSTRUCTION(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 5 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_INSTRUCTION(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 4:
    {
      ++(indices[ 4 ]);
      if ((e = handle_INSTRUCTIONS(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 4 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_INSTRUCTIONS(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 19:
    {
      ++(indices[ 19 ]);
      if ((e = handle_INTRPCAPTUREINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 19 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_INTRPCAPTUREINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 58:
    {
      ++(indices[ 58 ]);
      if ((e = handle_INTRPCAPTURETYPES(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 58 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_INTRPCAPTURETYPES(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 59:
    {
      ++(indices[ 59 ]);
      if ((e = handle_INTRPCAPTURETYPES_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 59 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_INTRPCAPTURETYPES_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 40:
    {
      ++(indices[ 40 ]);
      if ((e = handle_ISOLATEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 40 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_ISOLATEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 20:
    {
      ++(indices[ 20 ]);
      if ((e = handle_JUMPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 20 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_JUMPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 46:
    {
      ++(indices[ 46 ]);
      if ((e = handle_LABEL(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 46 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_LABEL(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 42:
    {
      ++(indices[ 42 ]);
      if ((e = handle_LABELDEF(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 42 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_LABELDEF(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 2:
    {
      ++(indices[ 2 ]);
      if ((e = handle_MULTILINECOMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 2 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_MULTILINECOMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 21:
    {
      ++(indices[ 21 ]);
      if ((e = handle_NOOPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 21 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_NOOPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 48:
    {
      ++(indices[ 48 ]);
      if ((e = handle_NUMBER(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 48 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_NUMBER(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 23:
    {
      ++(indices[ 23 ]);
      if ((e = handle_OPENCAPTUREINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 23 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_OPENCAPTUREINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 24:
    {
      ++(indices[ 24 ]);
      if ((e = handle_PARTIALCOMMITINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 24 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_PARTIALCOMMITINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 49:
    {
      ++(indices[ 49 ]);
      if ((e = handle_QUAD(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 49 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_QUAD(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 25:
    {
      ++(indices[ 25 ]);
      if ((e = handle_QUADINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 25 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_QUADINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 30:
    {
      ++(indices[ 30 ]);
      if ((e = handle_RANGEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 30 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_RANGEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 52:
    {
      ++(indices[ 52 ]);
      if ((e = handle_REGISTER(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 52 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_REGISTER(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 26:
    {
      ++(indices[ 26 ]);
      if ((e = handle_REPLACEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 26 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_REPLACEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 28:
    {
      ++(indices[ 28 ]);
      if ((e = handle_RETINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 28 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_RETINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 6:
    {
      ++(indices[ 6 ]);
      if ((e = handle_RULEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 6 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_RULEINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 1:
    {
      ++(indices[ 1 ]);
      if ((e = handle_S(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 1 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_S(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 50:
    {
      ++(indices[ 50 ]);
      if ((e = handle_SET(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 50 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_SET(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 29:
    {
      ++(indices[ 29 ]);
      if ((e = handle_SETINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 29 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_SETINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 31:
    {
      ++(indices[ 31 ]);
      if ((e = handle_SKIPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 31 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_SKIPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 51:
    {
      ++(indices[ 51 ]);
      if ((e = handle_SLOT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 51 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_SLOT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 32:
    {
      ++(indices[ 32 ]);
      if ((e = handle_SPANINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 32 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_SPANINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 56:
    {
      ++(indices[ 56 ]);
      if ((e = handle_STRINGLITERAL(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 56 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_STRINGLITERAL(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 57:
    {
      ++(indices[ 57 ]);
      if ((e = handle_STRINGLITERAL_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 57 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_STRINGLITERAL_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 33:
    {
      ++(indices[ 33 ]);
      if ((e = handle_TESTANYINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 33 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_TESTANYINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 34:
    {
      ++(indices[ 34 ]);
      if ((e = handle_TESTCHARINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 34 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_TESTCHARINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 35:
    {
      ++(indices[ 35 ]);
      if ((e = handle_TESTQUADINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 35 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_TESTQUADINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 36:
    {
      ++(indices[ 36 ]);
      if ((e = handle_TESTSETINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 36 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_TESTSETINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 0:
    {
      ++(indices[ 0 ]);
      if ((e = handle_TOP(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 0 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_TOP(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 22:
    {
      ++(indices[ 22 ]);
      if ((e = handle_TRAPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 22 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_TRAPINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 53:
    {
      ++(indices[ 53 ]);
      if ((e = handle_TYPE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 53 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_TYPE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 47:
    {
      ++(indices[ 47 ]);
      if ((e = handle_UNSIGNED(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 47 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_UNSIGNED(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 37:
    {
      ++(indices[ 37 ]);
      if ((e = handle_VARINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 37 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_VARINSTR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;

  }
  return 0;
}
