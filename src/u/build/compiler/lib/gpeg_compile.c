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

static
int gpeg_compile_rule
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  char* rulename;
  (void)i;

  switch (phase) {
  case GPEG_FNC_PRENODE:
    rulename = (char*)(node->children[ 0 ]->vec.data);
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
    break;
  case GPEG_FNC_POSTNODE:
    if (state->flags & GPEGC_FLG_AUTOCAPTURE) {
      unsigned capture = *((unsigned*)(vec->data));
      vec_printf(state->assembly, "  closecapture %u\n", capture);
    }
    vec_printf(state->assembly, "  ret\n\n");
    break;
  }
  return 0;
}

static
int gpeg_compile_expr
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  unsigned* labels;

  if (node->nchildren > 1) {
    switch (phase) {
    case GPEG_FNC_PRENODE:
      {
        unsigned label = (state->label)++;
        vec_append(vec, &label, sizeof(label));
      }
      break;
    case GPEG_FNC_PRECHILD:
      {
        unsigned label = (state->label)++;
        vec_append(vec, &label, sizeof(label));
        labels = (unsigned*)(vec->data);
        if (i + 1 < node->nchildren) {
          vec_printf(state->assembly,
            "  catch L%u\n"
            , labels[ (vec->size / sizeof(unsigned)) - 1 ]);
        }
      }
      break;
    case GPEG_FNC_POSTCHILD:
      labels = (unsigned*)(vec->data);
      if (i + 1 < node->nchildren) {
        vec_printf(state->assembly,
          "  commit L%u\n"
          "L%u:\n"
          , labels[ 0 ]
          , labels[ (vec->size / sizeof(unsigned)) - 1 ]
        );
      }
      break;
    case GPEG_FNC_POSTNODE:
      labels = (unsigned*)(vec->data);
      vec_printf(state->assembly,
        "L%u:\n"
        , labels[ 0 ]
      );
      break;
    }
  }
  return 0;
}

static
int gpeg_compile_call
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  char* rulename = (char*)(node->children[ 0 ]->vec.data);
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    vec_printf(state->assembly, "  call %s\n", rulename);
  }
  return 0;
}

static
int gpeg_compile_string
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  vec_t* string = &(node->children[ 0 ]->children[ 0 ]->vec);
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    for (unsigned i=0; i < string->size; i++) {
      unsigned char c = string->data[ i ];
      switch (c) {
      case 0x5c:
        break;
      default:
        vec_printf(state->assembly, "  range %.2x\n", c);
      }
    }
  }
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

  gpege_node_t* tree = gpeg_result_to_tree(&result);
  gpeg_result_remove(tree, SLOT_S, 1, 1);
  gpeg_result_remove(tree, SLOT_MULTILINECOMMENT, 1, 1);
  gpeg_result_remove(tree, SLOT_COMMENT, 1, 1);
//gpeg_result_debug(tree);

  gpeg_result_callback(tree, SLOT_RULE, gpeg_compile_rule, &state);
  gpeg_result_callback(tree, SLOT_EXPRESSION, gpeg_compile_expr, &state);
  gpeg_result_callback(tree, SLOT_REFERENCE, gpeg_compile_call, &state);
  gpeg_result_callback(tree, SLOT_STRING, gpeg_compile_string, &state);
  CHECK(gpeg_result_run(tree));

  RETURN_OK;
}
