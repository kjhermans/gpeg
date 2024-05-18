/**
* \file
* \brief This file is an autogenerated function prototypes header file.
*
* Copyright 2018 K.J. Hermans
* WARNING: This file is automatically generated. Any changes will be lost.
*/

#ifndef _GPEGE_GEN0_FUNCTIONS_FUNCTIONS_H_
#define _GPEGE_GEN0_FUNCTIONS_FUNCTIONS_H_

/* declared in ./gpege_actions.c */
#define gen0_gpege_actionlist_debug gpege_actionlist_debug

extern
void gpege_actionlist_debug
  (gpege_actionlist_t* list);

/* declared in ./gpege_actions.c */
#define gen0_gpege_actionlist_output gpege_actionlist_output

extern
void gpege_actionlist_output
  (gpege_actionlist_t* list);

/* declared in ./gpege_actions2captures.c */
#define gen0_gpege_actions2captures gpege_actions2captures

extern
GPEG_ERR_T gpege_actions2captures
  (vec_t* input, gpege_actionlist_t* actions, gpeg_capturelist_t* captures)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_debug_verbose.c */
#define gen0_gpege_debug_verbose gpege_debug_verbose

extern
GPEG_ERR_T gpege_debug_verbose
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode, void* arg)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_ec_free.c */
#define gen0_gpege_ec_free gpege_ec_free

extern
void gpege_ec_free
  (gpege_ec_t* ec);

/* declared in ./gpege_ec_init.c */
#define gen0_gpege_ec_init gpege_ec_init

extern
void gpege_ec_init
  (gpege_ec_t* ec, void* input, unsigned inputlen);

/* declared in ./gpege_init.c */
#define gen0_gpege_init gpege_init

extern
void gpege_init
  (gpege_t* gpege);

/* declared in ./gpege_run.c */
#define gen0_gpege_run gpege_run

extern
GPEG_ERR_T gpege_run
  (gpege_t* gpege, gpege_ec_t* ec)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_slotmap_absorb.c */
#define gen0_gpege_slotmap_absorb gpege_slotmap_absorb

extern
int gpege_slotmap_absorb
  (gpege_t* gpege, char* slotmaptext)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_slotmap_absorb.c */
#define gen0_gpege_slotmap_absorb_file gpege_slotmap_absorb_file

extern
int gpege_slotmap_absorb_file
  (gpege_t* gpege, char* path)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_stack.c */
#define gen0_gpege_stack_get_furthest gpege_stack_get_furthest

extern
void gpege_stack_get_furthest
  (gpege_stack_t* stack, unsigned* index, gpege_stackelt_t* elt);

/* declared in ./gpege_variable.c */
#define gen0_gpege_variable gpege_variable

extern
GPEG_ERR_T gpege_variable
  (
    gpege_t* gpege,
    gpege_ec_t* ec,
    uint32_t slot,
    unsigned char** value,
    unsigned* valuesize
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap.c */
#define gen0_simap_grammar_process_node simap_grammar_process_node

extern
int simap_grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_COMMENT simap_handle_COMMENT

extern
int simap_handle_COMMENT
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_post_COMMENT simap_handle_post_COMMENT

extern
int simap_handle_post_COMMENT
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_DEFINITION simap_handle_DEFINITION

extern
int simap_handle_DEFINITION
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_post_DEFINITION simap_handle_post_DEFINITION

extern
int simap_handle_post_DEFINITION
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_END simap_handle_END

extern
int simap_handle_END
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_post_END simap_handle_post_END

extern
int simap_handle_post_END
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_IDENT simap_handle_IDENT

extern
int simap_handle_IDENT
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_post_IDENT simap_handle_post_IDENT

extern
int simap_handle_post_IDENT
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_MAP simap_handle_MAP

extern
int simap_handle_MAP
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_post_MAP simap_handle_post_MAP

extern
int simap_handle_post_MAP
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_MULTILINECOMMENT simap_handle_MULTILINECOMMENT

extern
int simap_handle_MULTILINECOMMENT
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_post_MULTILINECOMMENT simap_handle_post_MULTILINECOMMENT

extern
int simap_handle_post_MULTILINECOMMENT
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_S simap_handle_S

extern
int simap_handle_S
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_post_S simap_handle_post_S

extern
int simap_handle_post_S
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_UNSIGNED simap_handle_UNSIGNED

extern
int simap_handle_UNSIGNED
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define gen0_simap_handle_post_UNSIGNED simap_handle_post_UNSIGNED

extern
int simap_handle_post_UNSIGNED
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));



#endif