#include <gpeg/lib/gpeg/gpeg_capturelist.h>

#ifdef _DEBUG
#include <stdio.h>
#endif

extern int grammar_process_node(gpeg_capture_t*, void*);
static int do_node(gpeg_capture_t*, unsigned, gpeg_capture_t*, void*);

extern int handle_instr_any_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_any_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_backcommit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_backcommit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_bitmask_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_bitmask_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_call_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_call_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_catch_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_catch_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_char_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_char_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_closecapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_closecapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_commit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_commit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_condjump_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_condjump_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_counter_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_counter_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_end_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_end_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_endisolate_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_endisolate_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_endreplace_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_endreplace_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_fail_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_fail_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_failtwice_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_failtwice_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_intrpcapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_intrpcapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_isolate_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_isolate_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_jump_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_jump_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_noop_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_noop_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_opencapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_opencapture_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_partialcommit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_partialcommit_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_quad_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_quad_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_range_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_range_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_replace_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_replace_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_ret_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_ret_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_set_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_set_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_skip_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_skip_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_span_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_span_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_testany_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_testany_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_testchar_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_testchar_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_testquad_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_testquad_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_testset_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_testset_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_trap_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_trap_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_instr_var_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int handle_post_instr_var_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);

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
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* ptr
  )
{
  int e;
  unsigned indices[ 34 ] = { 0 };

  switch (capture->type) {
  case 0:
    {
      ++indices[ 0 ];
      if ((e = handle_instr_any_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 0 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_any_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 1:
    {
      ++indices[ 1 ];
      if ((e = handle_instr_backcommit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 1 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_backcommit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 2:
    {
      ++indices[ 2 ];
      if ((e = handle_instr_bitmask_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 2 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_bitmask_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 3:
    {
      ++indices[ 3 ];
      if ((e = handle_instr_call_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 3 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_call_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 4:
    {
      ++indices[ 4 ];
      if ((e = handle_instr_catch_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 4 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_catch_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 5:
    {
      ++indices[ 5 ];
      if ((e = handle_instr_char_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 5 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_char_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 6:
    {
      ++indices[ 6 ];
      if ((e = handle_instr_closecapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 6 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_closecapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 7:
    {
      ++indices[ 7 ];
      if ((e = handle_instr_commit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 7 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_commit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 8:
    {
      ++indices[ 8 ];
      if ((e = handle_instr_condjump_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 8 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_condjump_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 9:
    {
      ++indices[ 9 ];
      if ((e = handle_instr_counter_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 9 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_counter_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 10:
    {
      ++indices[ 10 ];
      if ((e = handle_instr_end_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 10 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_end_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 11:
    {
      ++indices[ 11 ];
      if ((e = handle_instr_endisolate_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 11 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_endisolate_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 12:
    {
      ++indices[ 12 ];
      if ((e = handle_instr_endreplace_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 12 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_endreplace_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 13:
    {
      ++indices[ 13 ];
      if ((e = handle_instr_fail_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 13 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_fail_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 14:
    {
      ++indices[ 14 ];
      if ((e = handle_instr_failtwice_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 14 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_failtwice_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 15:
    {
      ++indices[ 15 ];
      if ((e = handle_instr_intrpcapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 15 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_intrpcapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 16:
    {
      ++indices[ 16 ];
      if ((e = handle_instr_isolate_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 16 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_isolate_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 17:
    {
      ++indices[ 17 ];
      if ((e = handle_instr_jump_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 17 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_jump_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 18:
    {
      ++indices[ 18 ];
      if ((e = handle_instr_noop_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 18 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_noop_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 19:
    {
      ++indices[ 19 ];
      if ((e = handle_instr_opencapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 19 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_opencapture_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 20:
    {
      ++indices[ 20 ];
      if ((e = handle_instr_partialcommit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 20 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_partialcommit_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 21:
    {
      ++indices[ 21 ];
      if ((e = handle_instr_quad_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 21 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_quad_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 22:
    {
      ++indices[ 22 ];
      if ((e = handle_instr_range_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 22 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_range_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 23:
    {
      ++indices[ 23 ];
      if ((e = handle_instr_replace_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 23 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_replace_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 24:
    {
      ++indices[ 24 ];
      if ((e = handle_instr_ret_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 24 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_ret_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 25:
    {
      ++indices[ 25 ];
      if ((e = handle_instr_set_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 25 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_set_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 26:
    {
      ++indices[ 26 ];
      if ((e = handle_instr_skip_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 26 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_skip_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 27:
    {
      ++indices[ 27 ];
      if ((e = handle_instr_span_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 27 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_span_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 28:
    {
      ++indices[ 28 ];
      if ((e = handle_instr_testany_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 28 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_testany_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 29:
    {
      ++indices[ 29 ];
      if ((e = handle_instr_testchar_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 29 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_testchar_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 30:
    {
      ++indices[ 30 ];
      if ((e = handle_instr_testquad_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 30 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_testquad_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 31:
    {
      ++indices[ 31 ];
      if ((e = handle_instr_testset_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 31 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_testset_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 32:
    {
      ++indices[ 32 ];
      if ((e = handle_instr_trap_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 32 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_trap_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  case 33:
    {
      ++indices[ 33 ];
      if ((e = handle_instr_var_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
      for (unsigned i=0; i < capture->children.count; i++) {
        if ((e = do_node(capture, indices[ 33 ], &(capture->children.list[ i ]), ptr)) != 0) {
          return e;
        }
      }
      if ((e = handle_post_instr_var_0(parent, index, capture, ptr)) != 0) {
        return e;
      }
    }
    break;
  }
  return 0;
}
