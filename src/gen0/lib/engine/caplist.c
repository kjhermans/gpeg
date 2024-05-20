
#include <gpeg/lib/gpeg/gpeg_capturelist.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

extern int caplist_grammar_process_node(gpeg_capture_t*, void*);
static int do_node(gpeg_capture_t*, unsigned, gpeg_capture_t*, void*);

extern int caplist_handle_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_post_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_DEFINITION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_post_DEFINITION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_post_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_MAP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_post_MAP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_post_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_post_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_SEMICOLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_post_SEMICOLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_UNSIGNED(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int caplist_handle_post_UNSIGNED(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);



int caplist_grammar_process_node
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
  unsigned indices[ 8 ] = { 0 };

  switch (capture->type) {
  case 3:
    {
      ++(indices[ 3 ]);
      if ((e = caplist_handle_COMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 3 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = caplist_handle_post_COMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 5:
    {
      ++(indices[ 5 ]);
      if ((e = caplist_handle_DEFINITION(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 5 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = caplist_handle_post_DEFINITION(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 4:
    {
      ++(indices[ 4 ]);
      if ((e = caplist_handle_END(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 4 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = caplist_handle_post_END(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 0:
    {
      ++(indices[ 0 ]);
      if ((e = caplist_handle_MAP(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 0 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = caplist_handle_post_MAP(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 2:
    {
      ++(indices[ 2 ]);
      if ((e = caplist_handle_MULTILINECOMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 2 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = caplist_handle_post_MULTILINECOMMENT(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 1:
    {
      ++(indices[ 1 ]);
      if ((e = caplist_handle_S(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 1 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = caplist_handle_post_S(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 6:
    {
      ++(indices[ 6 ]);
      if ((e = caplist_handle_SEMICOLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 6 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = caplist_handle_post_SEMICOLON(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 7:
    {
      ++(indices[ 7 ]);
      if ((e = caplist_handle_UNSIGNED(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 7 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = caplist_handle_post_UNSIGNED(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;

  }
  return 0;
}
