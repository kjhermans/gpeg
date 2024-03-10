
#include <gpeg/lib/gpeg/gpeg_capturelist.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

extern int grammar_process_node(gpeg_capture_t*, void*);
static int do_node(gpeg_capture_t*, unsigned, gpeg_capture_t*, void*);

extern int handle_INSTRUCTION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_INSTRUCTION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_TOP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_TOP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_any(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_any(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_backcommit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_backcommit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_backcommit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_backcommit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_call(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_call(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_call_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_call_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_catch(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_catch(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_catch_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_catch_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_char(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_char(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_char_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_char_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_closecapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_closecapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_closecapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_closecapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_commit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_commit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_commit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_commit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_condjump(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_condjump(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_condjump_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_condjump_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_counter(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_counter(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_counter_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_counter_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_end(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_end(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_end_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_end_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_endisolate(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_endisolate(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_endreplace(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_endreplace(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_fail(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_fail(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_failtwice(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_failtwice(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_intrpcapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_intrpcapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_intrpcapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_intrpcapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_isolate(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_isolate(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_isolate_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_isolate_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_jump(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_jump(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_jump_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_jump_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_maskedchar(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_maskedchar(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_maskedchar_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_maskedchar_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_noop(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_noop(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_opencapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_opencapture(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_opencapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_opencapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_partialcommit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_partialcommit(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_partialcommit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_partialcommit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_quad(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_quad(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_quad_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_quad_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_range(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_range(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_range_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_range_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_replace(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_replace(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_replace_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_replace_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_ret(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_ret(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_set(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_set(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_set_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_set_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_skip(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_skip(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_skip_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_skip_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_span(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_span(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_span_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_span_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_testany(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_testany(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_testany_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_testany_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_testchar(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_testchar(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_testchar_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_testchar_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_testquad(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_testquad(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_testquad_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_testquad_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_testset(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_testset(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_testset_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_testset_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_trap(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_trap(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_var(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_var(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_var_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_var_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);



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
  unsigned indices[ 62 ] = { 0 };

  switch (capture->type) {
  case 1:
    {
      ++(indices[ 1 ]);
      if ((e = handle_INSTRUCTION(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 1 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_INSTRUCTION(parent, index, capture, ptr)) != 0) {
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
  case 2:
    {
      ++(indices[ 2 ]);
      if ((e = handle_any(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 2 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_any(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 3:
    {
      ++(indices[ 3 ]);
      if ((e = handle_backcommit(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 3 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_backcommit(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 4:
    {
      ++(indices[ 4 ]);
      if ((e = handle_backcommit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 4 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_backcommit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 5:
    {
      ++(indices[ 5 ]);
      if ((e = handle_call(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 5 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_call(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 6:
    {
      ++(indices[ 6 ]);
      if ((e = handle_call_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 6 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_call_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 7:
    {
      ++(indices[ 7 ]);
      if ((e = handle_catch(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 7 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_catch(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 8:
    {
      ++(indices[ 8 ]);
      if ((e = handle_catch_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 8 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_catch_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 9:
    {
      ++(indices[ 9 ]);
      if ((e = handle_char(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 9 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_char(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 10:
    {
      ++(indices[ 10 ]);
      if ((e = handle_char_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 10 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_char_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 11:
    {
      ++(indices[ 11 ]);
      if ((e = handle_closecapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 11 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_closecapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 12:
    {
      ++(indices[ 12 ]);
      if ((e = handle_closecapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 12 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_closecapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 13:
    {
      ++(indices[ 13 ]);
      if ((e = handle_commit(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 13 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_commit(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 14:
    {
      ++(indices[ 14 ]);
      if ((e = handle_commit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 14 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_commit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 15:
    {
      ++(indices[ 15 ]);
      if ((e = handle_condjump(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 15 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_condjump(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 16:
    {
      ++(indices[ 16 ]);
      if ((e = handle_condjump_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 16 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_condjump_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 17:
    {
      ++(indices[ 17 ]);
      if ((e = handle_counter(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 17 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_counter(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 18:
    {
      ++(indices[ 18 ]);
      if ((e = handle_counter_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 18 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_counter_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 19:
    {
      ++(indices[ 19 ]);
      if ((e = handle_end(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 19 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_end(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 20:
    {
      ++(indices[ 20 ]);
      if ((e = handle_end_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 20 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_end_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 21:
    {
      ++(indices[ 21 ]);
      if ((e = handle_endisolate(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 21 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_endisolate(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 22:
    {
      ++(indices[ 22 ]);
      if ((e = handle_endreplace(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 22 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_endreplace(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 23:
    {
      ++(indices[ 23 ]);
      if ((e = handle_fail(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 23 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_fail(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 24:
    {
      ++(indices[ 24 ]);
      if ((e = handle_failtwice(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 24 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_failtwice(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 25:
    {
      ++(indices[ 25 ]);
      if ((e = handle_intrpcapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 25 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_intrpcapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 26:
    {
      ++(indices[ 26 ]);
      if ((e = handle_intrpcapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 26 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_intrpcapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 27:
    {
      ++(indices[ 27 ]);
      if ((e = handle_isolate(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 27 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_isolate(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 28:
    {
      ++(indices[ 28 ]);
      if ((e = handle_isolate_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 28 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_isolate_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 29:
    {
      ++(indices[ 29 ]);
      if ((e = handle_jump(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 29 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_jump(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 30:
    {
      ++(indices[ 30 ]);
      if ((e = handle_jump_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 30 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_jump_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 31:
    {
      ++(indices[ 31 ]);
      if ((e = handle_maskedchar(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 31 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_maskedchar(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 32:
    {
      ++(indices[ 32 ]);
      if ((e = handle_maskedchar_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 32 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_maskedchar_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 33:
    {
      ++(indices[ 33 ]);
      if ((e = handle_noop(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 33 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_noop(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 34:
    {
      ++(indices[ 34 ]);
      if ((e = handle_opencapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 34 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_opencapture(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 35:
    {
      ++(indices[ 35 ]);
      if ((e = handle_opencapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 35 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_opencapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 36:
    {
      ++(indices[ 36 ]);
      if ((e = handle_partialcommit(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 36 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_partialcommit(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 37:
    {
      ++(indices[ 37 ]);
      if ((e = handle_partialcommit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 37 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_partialcommit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 38:
    {
      ++(indices[ 38 ]);
      if ((e = handle_quad(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 38 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_quad(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 39:
    {
      ++(indices[ 39 ]);
      if ((e = handle_quad_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 39 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_quad_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 40:
    {
      ++(indices[ 40 ]);
      if ((e = handle_range(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 40 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_range(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 41:
    {
      ++(indices[ 41 ]);
      if ((e = handle_range_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 41 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_range_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 42:
    {
      ++(indices[ 42 ]);
      if ((e = handle_replace(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 42 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_replace(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 43:
    {
      ++(indices[ 43 ]);
      if ((e = handle_replace_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 43 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_replace_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 44:
    {
      ++(indices[ 44 ]);
      if ((e = handle_ret(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 44 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_ret(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 45:
    {
      ++(indices[ 45 ]);
      if ((e = handle_set(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 45 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_set(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 46:
    {
      ++(indices[ 46 ]);
      if ((e = handle_set_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 46 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_set_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 47:
    {
      ++(indices[ 47 ]);
      if ((e = handle_skip(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 47 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_skip(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 48:
    {
      ++(indices[ 48 ]);
      if ((e = handle_skip_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 48 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_skip_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 49:
    {
      ++(indices[ 49 ]);
      if ((e = handle_span(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 49 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_span(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 50:
    {
      ++(indices[ 50 ]);
      if ((e = handle_span_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 50 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_span_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 51:
    {
      ++(indices[ 51 ]);
      if ((e = handle_testany(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 51 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_testany(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 52:
    {
      ++(indices[ 52 ]);
      if ((e = handle_testany_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 52 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_testany_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 53:
    {
      ++(indices[ 53 ]);
      if ((e = handle_testchar(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 53 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_testchar(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 54:
    {
      ++(indices[ 54 ]);
      if ((e = handle_testchar_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 54 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_testchar_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 55:
    {
      ++(indices[ 55 ]);
      if ((e = handle_testquad(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 55 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_testquad(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 56:
    {
      ++(indices[ 56 ]);
      if ((e = handle_testquad_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 56 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_testquad_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 57:
    {
      ++(indices[ 57 ]);
      if ((e = handle_testset(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 57 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_testset(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 58:
    {
      ++(indices[ 58 ]);
      if ((e = handle_testset_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 58 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_testset_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 59:
    {
      ++(indices[ 59 ]);
      if ((e = handle_trap(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 59 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_trap(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 60:
    {
      ++(indices[ 60 ]);
      if ((e = handle_var(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 60 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_var(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 61:
    {
      ++(indices[ 61 ]);
      if ((e = handle_var_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 61 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_var_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;

  }
  return 0;
}
