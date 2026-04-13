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

#include <gpeg/assembler/lib.h>
#include <gpeg/engine/gpeg_engine.h>

static
#include <gpeg/assembler/assembly_bytecode.h>

#include <gpeg/engine/release.h>

struct assemblerstate
{
  unsigned      pass;
  unsigned      offset;
  vec_t*        bytecode;
};

static
int gpeg_asm_label
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
gpeg_result_debug(node);
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_bcm
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_cll
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_ctc
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_ccp
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_com
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_end
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_fai
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_fa2
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_ocp
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_pcm
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_ret
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_rng
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_var
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_ctr
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

static
int gpeg_asm_cjp
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += 4;
    } else {
    }
  }
  return 0;
}

/**
 *
 */
int gpeg_assemble
  (
    const vec_t* assembly,
    vec_t* bytecode
  )
{
  DEBUGFUNCTION
  ASSERT(assembly)
  ASSERT(bytecode)

  vec_t assemblybytecode = { (unsigned char*)assembly_byc, assembly_byc_len };
  gpege_result_t result = { 0 };
  struct assemblerstate state = {
    .bytecode = bytecode,
    .pass = 0,
    .offset = 0,
  };

  CHECK(gpeg_engine_run(&assemblybytecode, assembly, 0, &result));
  if (!(result.success)) {
    fprintf(stderr, "Parser error at [TODO].\n");
    RETURN_ERR(GPEGA_ERR_PARSER);
  }

  gpege_node_t* tree = gpeg_result_to_tree(&result);
  gpeg_result_remove(tree, SLOT_S, 1, 1);
  gpeg_result_remove(tree, SLOT_MULTILINECOMMENT, 1, 1);
  gpeg_result_remove(tree, SLOT_COMMENT, 1, 1);

  gpeg_result_callback(tree, SLOT_LABELDEF, gpeg_asm_label, &state);
  gpeg_result_callback(tree, SLOT_BACKCOMMITINSTR, gpeg_asm_bcm, &state);
  gpeg_result_callback(tree, SLOT_CALLINSTR, gpeg_asm_cll, &state);
  gpeg_result_callback(tree, SLOT_CATCHINSTR, gpeg_asm_ctc, &state);
  gpeg_result_callback(tree, SLOT_CLOSECAPTUREINSTR, gpeg_asm_ccp, &state);
  gpeg_result_callback(tree, SLOT_COMMITINSTR, gpeg_asm_com, &state);
  gpeg_result_callback(tree, SLOT_ENDINSTR, gpeg_asm_end, &state);
  gpeg_result_callback(tree, SLOT_FAILINSTR, gpeg_asm_fai, &state);
  gpeg_result_callback(tree, SLOT_FAILTWICEINSTR, gpeg_asm_fa2, &state);
  gpeg_result_callback(tree, SLOT_OPENCAPTUREINSTR, gpeg_asm_ocp, &state);
  gpeg_result_callback(tree, SLOT_PARTIALCOMMITINSTR, gpeg_asm_pcm, &state);
  gpeg_result_callback(tree, SLOT_RETINSTR, gpeg_asm_ret, &state);
  gpeg_result_callback(tree, SLOT_RANGEINSTR, gpeg_asm_rng, &state);
  gpeg_result_callback(tree, SLOT_VARINSTR, gpeg_asm_var, &state);
  gpeg_result_callback(tree, SLOT_COUNTERINSTR, gpeg_asm_ctr, &state);
  gpeg_result_callback(tree, SLOT_CONDJUMPINSTR, gpeg_asm_cjp, &state);

  state.pass = 1;
  CHECK(gpeg_result_run(tree));
  state.pass = 2;
  CHECK(gpeg_result_run(tree));

  RETURN_OK;
}
