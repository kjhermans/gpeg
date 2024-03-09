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
int grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_ANYINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_ANYINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_BACKCOMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_BACKCOMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_CALLINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_CALLINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_CATCHINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_CATCHINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_CHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_CHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_CLOSECAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_CLOSECAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_COMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_COMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_CONDJUMPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_CONDJUMPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_COUNTERINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_COUNTERINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_ENDINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_ENDINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_ENDISOLATEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_ENDISOLATEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_ENDREPLACEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_ENDREPLACEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_FAILINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_FAILINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_FAILTWICEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_FAILTWICEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_INTRPCAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_INTRPCAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_INTRPCAPTURETYPES
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_INTRPCAPTURETYPES
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_INTRPCAPTURETYPES_0
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_INTRPCAPTURETYPES_0
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_ISOLATEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_ISOLATEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_JUMPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_JUMPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_LABEL
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_LABEL
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_LABELDEF
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_LABELDEF
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_MASKEDCHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_MASKEDCHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_NOOPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_NOOPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_OPENCAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_OPENCAPTUREINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_PARTIALCOMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_PARTIALCOMMITINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_QUADINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_QUADINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_RANGEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_RANGEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_REPLACEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_REPLACEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_RETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_RETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_RULEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_RULEINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_SETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_SETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_SKIPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_SKIPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_SPANINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_SPANINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_TESTANYINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_TESTANYINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_TESTCHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_TESTCHARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_TESTQUADINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_TESTQUADINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_TESTSETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_TESTSETINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_TRAPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_TRAPINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_VARINSTR
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./assembly_handler.c */
extern
int handle_post_VARINSTR
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
  (vec_t* input, vec_t* output, vec_t* error, unsigned flags)
  __attribute__ ((warn_unused_result));



#endif