/**
* \file
* \brief This file is an autogenerated function prototypes header file.
*
* Copyright 2018 K.J. Hermans
* WARNING: This file is automatically generated. Any changes will be lost.
*/

#ifndef _GPEGC_PRIVATE_FUNCTIONS_H__FUNCTIONS_H_
#define _GPEGC_PRIVATE_FUNCTIONS_H__FUNCTIONS_H_

/* declared in ./assembly.c */
extern
int gpega_grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_ANYINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_BACKCOMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_CALLINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_CATCHINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_CHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_CLOSECAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_COMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_CONDJUMPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_COUNTERINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_ENDINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_FAILINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_FAILTWICEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_INTRPCAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_ISOLATEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_JUMPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_LABELDEF
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_BITMASKINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_NOOPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_OPENCAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_PARTIALCOMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_QUADINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_RANGEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_RETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_SETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_SKIPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_SPANINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_TESTANYINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_TESTCHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_TESTQUADINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_TESTSETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_TRAPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int gpega_handle_VARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./gpega_assemble.c */
extern
GPEG_ERR_T gpega_assemble
  (vec_t* input, vec_t* output, vec_t* error, char* labelmap, unsigned flags)
  __attribute__ ((warn_unused_result));

/* declared in ./gpega_labelmap_write.c */
extern
GPEG_ERR_T gpega_labelmap_write
  (gpega_t* gpega, char* path)
  __attribute__ ((warn_unused_result));



#endif