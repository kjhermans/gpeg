/**
* \file
* \brief This file is an autogenerated function prototypes header file.
*
* Copyright 2018 K.J. Hermans
* WARNING: This file is automatically generated. Any changes will be lost.
*/

#ifndef _GPEGE_GEN0_PR_FUNCTIONS_FUNCTIONS_H_
#define _GPEGE_GEN0_PR_FUNCTIONS_FUNCTIONS_H_

/* declared in ./caplist.c */
#define caplist_grammar_process_node gen0_caplist_grammar_process_node

extern
int caplist_grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_actions.c */
#define gpege_actionlist_debug gen0_gpege_actionlist_debug

extern
void gpege_actionlist_debug
  (gpege_actionlist_t* list);

/* declared in ./gpege_actions.c */
#define gpege_actionlist_output gen0_gpege_actionlist_output

extern
void gpege_actionlist_output
  (gpege_actionlist_t* list);

/* declared in ./gpege_actions2captures.c */
#define gpege_actions2captures gen0_gpege_actions2captures

extern
GPEG_ERR_T gpege_actions2captures
  (vec_t* input, gpege_actionlist_t* actions, gpeg_capturelist_t* captures)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_dbgncrs_draw_captures.c */
#define gpege_dbgncrs_draw_captures gen0_gpege_dbgncrs_draw_captures

extern
void gpege_dbgncrs_draw_captures
  (gpege_t* gpege, gpege_ec_t* ec);

/* declared in ./gpege_dbgncrs_draw_header.c */
#define gpege_dbgncrs_draw_header gen0_gpege_dbgncrs_draw_header

extern
void gpege_dbgncrs_draw_header
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode);

/* declared in ./gpege_dbgncrs_draw_input.c */
#define gpege_dbgncrs_draw_input gen0_gpege_dbgncrs_draw_input

extern
void gpege_dbgncrs_draw_input
  (gpege_ec_t* ec);

/* declared in ./gpege_dbgncrs_draw_settings.c */
#define gpege_dbgncrs_draw_settings gen0_gpege_dbgncrs_draw_settings

extern
void gpege_dbgncrs_draw_settings
  (gpege_t* gpege);

/* declared in ./gpege_dbgncrs_draw_stack.c */
#define gpege_dbgncrs_draw_stack gen0_gpege_dbgncrs_draw_stack

extern
void gpege_dbgncrs_draw_stack
  (gpege_t* gpege, gpege_ec_t* ec);

/* declared in ./gpege_dbgncrs_recalculate.c */
#define gpege_dbgncrs_recalculate gen0_gpege_dbgncrs_recalculate

extern
void gpege_dbgncrs_recalculate
  ();

/* declared in ./gpege_debug_ncurses.c */
#define gpege_debug_ncurses_exit gen0_gpege_debug_ncurses_exit

extern
void gpege_debug_ncurses_exit
  ();

/* declared in ./gpege_debug_ncurses.c */
#define gpege_debug_ncurses gen0_gpege_debug_ncurses

extern
GPEG_ERR_T gpege_debug_ncurses
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode, void* arg)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_debug_verbose.c */
#define gpege_debug_verbose gen0_gpege_debug_verbose

extern
GPEG_ERR_T gpege_debug_verbose
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode, void* arg)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_ec_copy.c */
#define gpege_ec_copy gen0_gpege_ec_copy

extern
GPEG_ERR_T gpege_ec_copy
  (gpege_ec_t* dst, gpege_ec_t* src)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_ec_free.c */
#define gpege_ec_free gen0_gpege_ec_free

extern
void gpege_ec_free
  (gpege_ec_t* ec);

/* declared in ./gpege_ec_init.c */
#define gpege_ec_init gen0_gpege_ec_init

extern
void gpege_ec_init
  (gpege_ec_t* ec, void* input, unsigned inputlen);

/* declared in ./gpege_init.c */
#define gpege_init gen0_gpege_init

extern
void gpege_init
  (gpege_t* gpege);

/* declared in ./gpege_run.c */
#define gpege_run gen0_gpege_run

extern
GPEG_ERR_T gpege_run
  (gpege_t* gpege, gpege_ec_t* ec)
  __attribute__ ((warn_unused_result));

/* declared in ./gpege_stack.c */
#define gpege_stack_get_furthest gen0_gpege_stack_get_furthest

extern
void gpege_stack_get_furthest
  (gpege_stack_t* stack, unsigned* index, gpege_stackelt_t* elt);

/* declared in ./gpege_variable.c */
#define gpege_variable gen0_gpege_variable

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

/* declared in ./ncurses_widget_input.c */
#define ncurses_widget_input gen0_ncurses_widget_input

extern
int ncurses_widget_input
  (unsigned y, unsigned x, unsigned w, char* value, unsigned valuesize)
  __attribute__ ((warn_unused_result));

/* declared in ./ncurses_widget_list.c */
#define ncurses_widget_list gen0_ncurses_widget_list

extern
int ncurses_widget_list
  (
    unsigned y,
    unsigned x,
    unsigned h,
    unsigned w,
    char*  (*iterator)(void*),
    void*    arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./ncurses_widget_toggle.c */
#define ncurses_widget_toggle gen0_ncurses_widget_toggle

extern
int ncurses_widget_toggle
  (
    unsigned y,
    unsigned x,
    int* value
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap.c */
#define simap_grammar_process_node gen0_simap_grammar_process_node

extern
int simap_grammar_process_node
  (
    gpeg_capture_t* capture,
    void* ptr
  )
  __attribute__ ((warn_unused_result));

/* declared in ./simap_handler.c */
#define simap_handle_COMMENT gen0_simap_handle_COMMENT

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
#define simap_handle_post_COMMENT gen0_simap_handle_post_COMMENT

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
#define simap_handle_DEFINITION gen0_simap_handle_DEFINITION

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
#define simap_handle_post_DEFINITION gen0_simap_handle_post_DEFINITION

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
#define simap_handle_END gen0_simap_handle_END

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
#define simap_handle_post_END gen0_simap_handle_post_END

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
#define simap_handle_IDENT gen0_simap_handle_IDENT

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
#define simap_handle_post_IDENT gen0_simap_handle_post_IDENT

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
#define simap_handle_MAP gen0_simap_handle_MAP

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
#define simap_handle_post_MAP gen0_simap_handle_post_MAP

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
#define simap_handle_MULTILINECOMMENT gen0_simap_handle_MULTILINECOMMENT

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
#define simap_handle_post_MULTILINECOMMENT gen0_simap_handle_post_MULTILINECOMMENT

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
#define simap_handle_S gen0_simap_handle_S

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
#define simap_handle_post_S gen0_simap_handle_post_S

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
#define simap_handle_UNSIGNED gen0_simap_handle_UNSIGNED

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
#define simap_handle_post_UNSIGNED gen0_simap_handle_post_UNSIGNED

extern
int simap_handle_post_UNSIGNED
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
  __attribute__ ((warn_unused_result));

/* declared in ./str2int_map_absorb.c */
#define str2int_map_absorb gen0_str2int_map_absorb

extern
int str2int_map_absorb
  (str2int_map_t* map, char* maptext)
  __attribute__ ((warn_unused_result));

/* declared in ./str2int_map_absorb.c */
#define str2int_map_absorb_file gen0_str2int_map_absorb_file

extern
int str2int_map_absorb_file
  (str2int_map_t* str2int_map, char* path)
  __attribute__ ((warn_unused_result));



#endif