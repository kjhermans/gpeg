/**
 * This file is part of GPEG, a parsing environment

Copyright (c) 2026, Kees-Jan Hermans <kees.jan.hermans@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the organization nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL the copyright holder BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 *
 * \file
 * \brief
 */

#include <gpeg/compiler/lib.h>
#include <gpeg/engine/gpeg_engine.h>

static
#include <gpeg/compiler/grammar_bytecode.h>

struct compilestate
{
  unsigned  flags;
  unsigned  label;
  unsigned  capture;
  int       prefixset;
  vec_t*    assembly;
};

/*
#ifdef _DEBUG
static
void debug_capture
  (
    gpege_caplist_t* captures,
    unsigned i
  )
{
  gpege_capture_t* capture = &(captures->list[ i ]);
  for (; i < captures->count
       && captures->list[ i ].offset < capture->offset + capture->vec.size; i++)
  {
    gpege_capture_t* sub = &(captures->list[ i ]);
    fprintf(stderr,
      "%.3u: %.6u: %-.*s\n"
      , sub->reg
      , sub->offset
      , sub->vec.size
      , sub->vec.data
    );
  }
}
#endif

static
void unescape_string
  (gpege_capture_t* string, vec_t* assembly)
{
  for (unsigned i=0; i < string->vec.size; i++) {
    char c = string->vec.data[ i ];
    if (c == '\\') {
      char e = string->vec.data[ ++i ];
      switch (e) {
      case 'n': vec_printf(assembly, "  range 0a\n"); break;
      case 'r': vec_printf(assembly, "  range 0d\n"); break;
      case 't': vec_printf(assembly, "  range 09\n"); break;
      default:  vec_printf(assembly, "  range %.2x\n", e); break;
      }
    } else {
      vec_printf(assembly, "  range %.2x\n", c);
    }
  }
}

static
int gpeg_compile_p1_matcher
  (
    gpege_caplist_t* captures,
    gpege_capture_t* matcher,
    unsigned i,
    vec_t* assembly,
    struct compilestate* state
  )
{
  switch (matcher[ 1 ].reg) {
  case SLOT_ANY:
    vec_printf(assembly, "  range 00 ff\n");
    break;
  case SLOT_SET:
#ifdef _DEBUG
    fprintf(stderr, "SET:\n");
    debug_capture(captures, i);
    fprintf(stderr, "\n");
#endif
    break;
  case SLOT_STRING:
    unescape_string(&(matcher[ 3 ]), assembly);
    break;
  case SLOT_BITMASK:
    break;
  case SLOT_HEXLITERAL:
    break;
  case SLOT_VARCAPTURE:
    break;
  case SLOT_CAPTURE:
    break;
  case SLOT_GROUP:
    break;
  case SLOT_MACRO:
    break;
  case SLOT_ENDFORCE:
    break;
  case SLOT_VARREFERENCE:
    break;
  case SLOT_REFERENCE:
    vec_printf(assembly,
      "  call %-.*s\n", matcher[ 2 ].vec.size, matcher[ 2 ].vec.data
    );
    break;
  case SLOT_LIMITEDCALL:
    break;
  }
  return 0;
}

static
int gpeg_compile_p1_term
  (
    gpege_caplist_t* captures,
    gpege_capture_t* term,
    unsigned i,
    vec_t* assembly,
    struct compilestate* state
  )
{
  if (term[ 1 ].reg == SLOT_SCANMATCHER) {
    //..
  } else if (term[ 1 ].reg == SLOT_QUANTIFIEDMATCHER) {
    CHECK(
      gpeg_compile_p1_matcher(
        captures,
        &(captures->list[ i+2 ]),
        i+2,
        assembly,
        state
      )
    );
  }
  return 0;
}

static
int gpeg_compile_p1_terms
  (
    gpege_caplist_t* captures,
    gpege_capture_t* terms,
    unsigned i,
    vec_t* assembly,
    struct compilestate* state
  )
{
  for (; i < captures->count
         && captures->list[ i ].offset < terms->offset + terms->vec.size; i++)
  {
    gpege_capture_t* capture = &(captures->list[ i ]);
    if (capture->reg == SLOT_TERM) {
      CHECK(gpeg_compile_p1_term(captures, capture, i, assembly, state));
    }
  }
  return 0;
}

static
int gpeg_compile_p1_rule
  (
    gpege_caplist_t* captures,
    gpege_capture_t* rule,
    unsigned i,
    vec_t* assembly,
    struct compilestate* state
  )
{
  vec_t terms = { 0 };
  for (; i < captures->count
         && captures->list[ i ].offset < rule->offset + rule->vec.size; i++)
  {
    gpege_capture_t* capture = &(captures->list[ i ]);
    if (capture->reg == SLOT_TERMS && !(terms.data)) {
      CHECK(gpeg_compile_p1_terms(captures, capture, i, &terms, state));
    } else if (capture->reg == SLOT_OR) {
      vec_t alt = { 0 };
      CHECK(gpeg_compile_p1_rule(captures, rule, i+1, &alt, state));
      vec_printf(assembly,
        "  catch L_%u\n"
        "%s"
        "  commit L_%u\n"
        "L_%u:\n"
        "%s"
        "L_%u:\n"
        , state->label
        , terms.data
        , state->label + 1
        , state->label
        , alt.data
        , state->label + 1
      );
      state->label += 2;
      //free(terms.data); free(alt.data);
      return 0;
    }
  }
  vec_appendv(assembly, &terms);
  //free(terms.data);
  return 0;
}

static
int gpeg_compile_p1_rules
  (
    gpege_caplist_t* captures,
    vec_t* assembly,
    struct compilestate* state
  )
{
  for (unsigned i=0; i < captures->count; i++) {
    gpege_capture_t* capture = &(captures->list[ i ]);
    if (capture->reg == SLOT_RULE) {
      unsigned autocapture = 0;
      vec_printf(assembly,
        "%-.*s:\n", capture[ 1 ].vec.size, capture[ 1 ].vec.data
      );
      if (state->prefixset) {
        vec_printf(assembly,
          "  call __prefix\n"
        );
      }
      if (0 == vec_strcmp(&(capture[ 1 ].vec), "__prefix")) {
        state->prefixset = 1;
      }
      if (state->flags & GPEGC_FLG_AUTOCAPTURE) {
        autocapture = state->capture;
        ++(state->capture);
        vec_printf(assembly,
          "  opencapture %u\n"
          , autocapture
        );
      }
      CHECK(gpeg_compile_p1_rule(captures, capture, i, assembly, state));
      if (state->flags & GPEGC_FLG_AUTOCAPTURE) {
        vec_printf(assembly,
          "  closecapture %u\n"
          , autocapture
        );
      }
      vec_printf(assembly,
        "  ret\n\n"
      );
    }
  }
  return 0;
}
*/

static
int gpeg_compile_pre_rule
  (gpege_node_t* node, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  char* rulename = node->children[ 0 ]->vec.data;

  vec_printf(state->assembly, "%s:\n", rulename);
  if (state->prefixset) {
    vec_printf(state->assembly, "  call __prefix\n");
  }
  if (state->flags & GPEGC_FLG_AUTOCAPTURE) {
    unsigned capture = (state->capture)++;
    vec_append(vec, &capture, sizeof(capture));
    vec_printf(state->assembly, "  opencapture %u\n", capture);
  }
  if (0 == strcmp(rulename, "__prefix")) {
    state->prefixset = 1;
  }
  return 0;
}

static
int gpeg_compile_post_rule
  (gpege_node_t* node, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;

  if (state->flags & GPEGC_FLG_AUTOCAPTURE) {
    unsigned capture = *((unsigned*)(vec->data));
    vec_printf(state->assembly, "  opencapture %u\n", capture);
  }
  vec_printf(state->assembly, "  ret\n\n");
  return 0;
}

/**
 *
 */
int gpeg_compile
  (
    const vec_t* grammar,
    vec_t* assembly,
    unsigned flags
  )
{
  DEBUGFUNCTION
  ASSERT(grammar)
  ASSERT(assembly)

  vec_t bytecode = { (unsigned char*)grammar_byc, grammar_byc_len };
  gpege_result_t result = { 0 };
  struct compilestate state = {
    .flags = flags,
    .label = 1,
    .prefixset  = 0,
    .capture = 0,
    .assembly = assembly,
  };

  CHECK(gpeg_engine_run(&bytecode, grammar, 0, &result));
  if (!(result.success)) {
    fprintf(stderr, "Parser error at [TODO].\n");
    RETURN_ERR(GPEGC_ERR_PARSER);
  }
/*
  CHECK(gpeg_compile_p1_rules(&(result.captures), assembly, &state));
*/

  gpege_node_t* tree = gpeg_result_to_tree(&result);
  gpeg_result_remove(tree, SLOT_S, 1, 1);
  gpeg_result_remove(tree, SLOT_MULTILINECOMMENT, 1, 1);
  gpeg_result_remove(tree, SLOT_COMMENT, 1, 1);
//gpeg_result_debug(tree);
  gpeg_result_prefunc(tree, SLOT_RULE, gpeg_compile_pre_rule, &state);
  gpeg_result_postfunc(tree, SLOT_RULE, gpeg_compile_post_rule, &state);
  CHECK(gpeg_result_run(tree));

  RETURN_OK;
}
