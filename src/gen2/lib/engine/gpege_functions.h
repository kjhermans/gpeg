/**
* \file
* \brief This file is an autogenerated function prototypes header file.
*
* Copyright 2018 K.J. Hermans
* WARNING: This file is automatically generated. Any changes will be lost.
*/

#ifndef _GPEGE_GEN2_PR_FUNCTIONS_FUNCTIONS_H_
#define _GPEGE_GEN2_PR_FUNCTIONS_FUNCTIONS_H_

/* declared in ./gpege_actions.c */
#define gpege_actionlist_debug gen2_gpege_actionlist_debug

extern
void gpege_actionlist_debug
  (gpege_actionlist_t* list);

/* declared in ./gpege_actions.c */
#define gpege_actionlist_output gen2_gpege_actionlist_output

extern
void gpege_actionlist_output
  (gpege_actionlist_t* list);

/* declared in ./gpege_actions2captures.c */
#define gpege_actions2captures gen2_gpege_actions2captures

extern
GPEG_ERR_T gpege_actions2captures
  (vec_t* input, gpege_actionlist_t* actions, gpeg_capturelist_t* captures)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_debug_verbose.c */
#define gpege_debug_verbose gen2_gpege_debug_verbose

extern
GPEG_ERR_T gpege_debug_verbose
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode, void* arg)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_ec_free.c */
#define gpege_ec_free gen2_gpege_ec_free

extern
void gpege_ec_free
  (gpege_ec_t* ec);

/* declared in ./gpege_ec_init.c */
#define gpege_ec_init gen2_gpege_ec_init

extern
void gpege_ec_init
  (gpege_ec_t* ec, void* input, unsigned inputlen);

/* declared in ./gpege_init.c */
#define gpege_init gen2_gpege_init

extern
void gpege_init
  (gpege_t* gpege);

/* declared in ./gpege_run.c */
#define gpege_run gen2_gpege_run

extern
GPEG_ERR_T gpege_run
  (gpege_t* gpege, gpege_ec_t* ec)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_stack.c */
#define gpege_stack_get_furthest gen2_gpege_stack_get_furthest

extern
void gpege_stack_get_furthest
  (gpege_stack_t* stack, unsigned* index, gpege_stackelt_t* elt);

/* declared in ./gpege_variable.c */
#define gpege_variable gen2_gpege_variable

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



#endif