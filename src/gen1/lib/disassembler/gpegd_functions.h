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
int grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_any
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_backcommit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_call
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_catch
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_char
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_closecapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_commit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_condjump
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_counter
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_end
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_endisolate
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_endreplace
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_fail
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_failtwice
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_intrpcapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_isolate
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_jump
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_maskedchar
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_noop
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_opencapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_partialcommit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_quad
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_range
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_replace
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_ret
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_set
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_skip
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_span
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_testany
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_testchar
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_testquad
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_testset
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_trap
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./disasm_handler.c */
extern
int handle_var
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