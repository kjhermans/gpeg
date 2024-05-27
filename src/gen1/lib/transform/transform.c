
#include <gpeg/lib/gpeg/gpeg_capturelist.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

extern int gpegt_grammar_process_node(gpeg_capture_t*, void*);
static int do_node(gpeg_capture_t*, unsigned, gpeg_capture_t*, void*);

extern int gpegt_handle_CHAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_CHAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_COLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_COLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_DEFINITION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_DEFINITION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_DOLLAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_DOLLAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_EXPRESSION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_EXPRESSION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_IDENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_IDENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_REFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_REFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_SLOT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_SLOT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_STRING(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_STRING(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_STRING_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_STRING_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_TERM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_TERM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_TRANSFORM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegt_handle_post_TRANSFORM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);



int gpegt_grammar_process_node
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
  unsigned indices[ 16 ] = { 0 };

  switch (capture->type) {
  case 12:
    {
      ++(indices[ 12 ]);
      if ((e = gpegt_handle_CHAR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 12 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_CHAR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 14:
    {
      ++(indices[ 14 ]);
      if ((e = gpegt_handle_COLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 14 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_COLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 3:
    {
      ++(indices[ 3 ]);
      if ((e = gpegt_handle_COMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 3 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_COMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 5:
    {
      ++(indices[ 5 ]);
      if ((e = gpegt_handle_DEFINITION(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 5 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_DEFINITION(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 15:
    {
      ++(indices[ 15 ]);
      if ((e = gpegt_handle_DOLLAR(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 15 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_DOLLAR(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 4:
    {
      ++(indices[ 4 ]);
      if ((e = gpegt_handle_END(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 4 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_END(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 7:
    {
      ++(indices[ 7 ]);
      if ((e = gpegt_handle_EXPRESSION(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 7 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_EXPRESSION(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 13:
    {
      ++(indices[ 13 ]);
      if ((e = gpegt_handle_IDENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 13 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_IDENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 2:
    {
      ++(indices[ 2 ]);
      if ((e = gpegt_handle_MULTILINECOMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 2 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_MULTILINECOMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 11:
    {
      ++(indices[ 11 ]);
      if ((e = gpegt_handle_REFERENCE(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 11 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_REFERENCE(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 1:
    {
      ++(indices[ 1 ]);
      if ((e = gpegt_handle_S(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 1 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_S(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 6:
    {
      ++(indices[ 6 ]);
      if ((e = gpegt_handle_SLOT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 6 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_SLOT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 9:
    {
      ++(indices[ 9 ]);
      if ((e = gpegt_handle_STRING(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 9 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_STRING(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 10:
    {
      ++(indices[ 10 ]);
      if ((e = gpegt_handle_STRING_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 10 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_STRING_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 8:
    {
      ++(indices[ 8 ]);
      if ((e = gpegt_handle_TERM(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 8 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_TERM(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 0:
    {
      ++(indices[ 0 ]);
      if ((e = gpegt_handle_TRANSFORM(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 0 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegt_handle_post_TRANSFORM(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;

  }
  return 0;
}
