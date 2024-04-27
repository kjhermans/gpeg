/**
* \file
* \brief This file is an autogenerated function prototypes header file.
*
* Copyright 2018 K.J. Hermans
* WARNING: This file is automatically generated. Any changes will be lost.
*/

#ifndef _GPEGE_PR_FUNCTIONS_FUNCTIONS_H_
#define _GPEGE_PR_FUNCTIONS_FUNCTIONS_H_

/* declared in ./gpege_actions.c */
#define gen1_gpege_actionlist_debug gpege_actionlist_debug

extern
void gpege_actionlist_debug
  (gpege_actionlist_t* list);

/* declared in ./gpege_actions2captures.c */
#define gen1_gpege_actions2captures gpege_actions2captures

extern
GPEG_ERR_T gpege_actions2captures
  (vec_t* input, gpege_actionlist_t* actions, gpeg_capturelist_t* captures)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_ec_free.c */
#define gen1_gpege_ec_free gpege_ec_free

extern
void gpege_ec_free
  (gpege_ec_t* ec);

/* declared in ./gpege_ec_init.c */
#define gen1_gpege_ec_init gpege_ec_init

extern
void gpege_ec_init
  (gpege_ec_t* ec, void* input, unsigned inputlen);

/* declared in ./gpege_init.c */
#define gen1_gpege_init gpege_init

extern
void gpege_init
  (gpege_t* gpege);

/* declared in ./gpege_run.c */
#define gen1_gpege_run gpege_run

extern
GPEG_ERR_T gpege_run
  (gpege_t* gpege, gpege_ec_t* ec)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_stack.c */
#define gen1_gpege_stack_get_furthest gpege_stack_get_furthest

extern
void gpege_stack_get_furthest
  (gpege_stack_t* stack, unsigned* index, gpege_stackelt_t* elt);

/* declared in ./gpege_variable.c */
#define gen1_gpege_variable gpege_variable

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