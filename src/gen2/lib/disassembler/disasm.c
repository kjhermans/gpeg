#include <gpeg/lib/gpeg/gpeg_capturelist.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

extern int gpegd_grammar_process_node(gpeg_capture_t*,void*);
static int do_node(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);

extern int gpegd_handle_instr_any(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_any(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_backcommit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_backcommit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_bitmask(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_bitmask(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_call(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_call(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_catch(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_catch(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_char(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_char(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_closecapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_closecapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_commit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_commit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_condjump(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_condjump(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_counter(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_counter(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_end(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_end(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_fail(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_fail(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_failtwice(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_failtwice(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_intrpcapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_intrpcapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_jump(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_jump(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_noop(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_noop(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_opencapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_opencapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_partialcommit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_partialcommit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_quad(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_quad(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_range(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_range(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_ret(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_ret(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_set(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_set(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_skip(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_skip(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_span(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_span(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_testany(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_testany(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_testchar(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_testchar(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_testquad(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_testquad(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_testset(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_testset(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_trap(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_trap(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_instr_var(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegd_handle_post_instr_var(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);

int gpegd_grammar_process_node
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
  unsigned indices[ 30 ] = { 0 };

  switch (capture->type) {
  case 0:
    {
      ++indices[ 0 ];
      if ((e = gpegd_handle_instr_any(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 0 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_any(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 1:
    {
      ++indices[ 1 ];
      if ((e = gpegd_handle_instr_backcommit(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 1 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_backcommit(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 2:
    {
      ++indices[ 2 ];
      if ((e = gpegd_handle_instr_bitmask(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 2 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_bitmask(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 3:
    {
      ++indices[ 3 ];
      if ((e = gpegd_handle_instr_call(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 3 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_call(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 4:
    {
      ++indices[ 4 ];
      if ((e = gpegd_handle_instr_catch(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 4 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_catch(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 5:
    {
      ++indices[ 5 ];
      if ((e = gpegd_handle_instr_char(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 5 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_char(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 6:
    {
      ++indices[ 6 ];
      if ((e = gpegd_handle_instr_closecapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 6 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_closecapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 7:
    {
      ++indices[ 7 ];
      if ((e = gpegd_handle_instr_commit(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 7 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_commit(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 8:
    {
      ++indices[ 8 ];
      if ((e = gpegd_handle_instr_condjump(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 8 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_condjump(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 9:
    {
      ++indices[ 9 ];
      if ((e = gpegd_handle_instr_counter(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 9 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_counter(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 10:
    {
      ++indices[ 10 ];
      if ((e = gpegd_handle_instr_end(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 10 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_end(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 11:
    {
      ++indices[ 11 ];
      if ((e = gpegd_handle_instr_fail(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 11 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_fail(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 12:
    {
      ++indices[ 12 ];
      if ((e = gpegd_handle_instr_failtwice(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 12 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_failtwice(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 13:
    {
      ++indices[ 13 ];
      if ((e = gpegd_handle_instr_intrpcapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 13 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_intrpcapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 14:
    {
      ++indices[ 14 ];
      if ((e = gpegd_handle_instr_jump(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 14 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_jump(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 15:
    {
      ++indices[ 15 ];
      if ((e = gpegd_handle_instr_noop(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 15 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_noop(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 16:
    {
      ++indices[ 16 ];
      if ((e = gpegd_handle_instr_opencapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 16 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_opencapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 17:
    {
      ++indices[ 17 ];
      if ((e = gpegd_handle_instr_partialcommit(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 17 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_partialcommit(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 18:
    {
      ++indices[ 18 ];
      if ((e = gpegd_handle_instr_quad(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 18 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_quad(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 19:
    {
      ++indices[ 19 ];
      if ((e = gpegd_handle_instr_range(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 19 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_range(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 20:
    {
      ++indices[ 20 ];
      if ((e = gpegd_handle_instr_ret(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 20 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_ret(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 21:
    {
      ++indices[ 21 ];
      if ((e = gpegd_handle_instr_set(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 21 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_set(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 22:
    {
      ++indices[ 22 ];
      if ((e = gpegd_handle_instr_skip(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 22 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_skip(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 23:
    {
      ++indices[ 23 ];
      if ((e = gpegd_handle_instr_span(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 23 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_span(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 24:
    {
      ++indices[ 24 ];
      if ((e = gpegd_handle_instr_testany(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 24 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_testany(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 25:
    {
      ++indices[ 25 ];
      if ((e = gpegd_handle_instr_testchar(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 25 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_testchar(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 26:
    {
      ++indices[ 26 ];
      if ((e = gpegd_handle_instr_testquad(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 26 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_testquad(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 27:
    {
      ++indices[ 27 ];
      if ((e = gpegd_handle_instr_testset(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 27 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_testset(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 28:
    {
      ++indices[ 28 ];
      if ((e = gpegd_handle_instr_trap(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 28 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_trap(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 29:
    {
      ++indices[ 29 ];
      if ((e = gpegd_handle_instr_var(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 29 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = gpegd_handle_post_instr_var(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  }
  return 0;
}
