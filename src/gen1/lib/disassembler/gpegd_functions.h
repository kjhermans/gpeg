/**
* \file
* \brief This file is an autogenerated function prototypes header file.
*
* Copyright 2018 K.J. Hermans
* WARNING: This file is automatically generated. Any changes will be lost.
*/

#ifndef _GPEGD_PRIVATE_FUNCTIONS_H__FUNCTIONS_H_
#define _GPEGD_PRIVATE_FUNCTIONS_H__FUNCTIONS_H_

/* declared in ./disasm.c */
extern
int gpegd_grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_any
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_backcommit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_call
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_catch
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_char
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_closecapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_commit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_condjump
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_counter
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_end
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_endisolate
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_endreplace
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_fail
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_failtwice
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_intrpcapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_isolate
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_jump
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_bitmask
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_noop
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_opencapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_partialcommit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_quad
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_range
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_replace
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_ret
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_set
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_skip
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_span
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_testany
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_testchar
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_testquad
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_testset
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_trap
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_var
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_eq
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_neq
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_lt
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_gt
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_lteq
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_gteq
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_moveto
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_imoveto
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_rmoveto
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int gpegd_handle_instr_irmoveto
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./gpegd_disassemble.c */
extern
GPEG_ERR_T gpegd_disassemble
  (vec_t* input, vec_t* output, vec_t* error, unsigned flags)
  __attribute__ ((warn_unused_result));



#endif