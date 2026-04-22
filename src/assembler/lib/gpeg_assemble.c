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
  str2int_map_t offsets;
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
      char* label = (char*)(node->children[ 0 ]->vec.data);
      str2int_map_put(&(state->offsets), label, state->offset);
    }
  }
  return 0;
}

static
void gpeg_asm_instr
  (uint32_t* instr, uint8_t opcode, unsigned nfields, ...)
{
  va_list ap;
  uint8_t* bytes = (uint8_t*)instr;

  bytes[ 0 ] = (opcode << 4);
  bytes[ 1 ] = 0;
  bytes[ 2 ] = 0;
  bytes[ 3 ] = 0;
  va_start(ap, nfields);
  for (unsigned i=0; i < nfields; i++) {
    unsigned offset = va_arg(ap, unsigned);
    unsigned length = va_arg(ap, unsigned);
    unsigned field = va_arg(ap, unsigned);
    ASSERT(offset + length <= 32)
    for (unsigned j=0; j < length; j++) {
      if (field & (1 << j)) {
        unsigned byte = (offset + length - j - 1) / 8;
        unsigned bit = 7 - ((offset + length - j - 1) % 8);
        bytes[ byte ] |= (1 << bit);
      }
    }
  }
  va_end(ap);
}

static
int gpeg_asm_labeled_instr
  (struct assemblerstate* state, gpege_node_t* node, uint8_t opcode)
{
  char* label = (char*)(node->children[ 0 ]->vec.data);
  unsigned o;
  unsigned* offset;

  if (0 == strcmp(label, "__NEXT__")) {
    o = state->bytecode->size + GPEG_INSTR_SIZE;
    offset = &o;
  } else {
    offset = str2int_map_getptr(&(state->offsets), label);
    if (offset && *offset == state->bytecode->size) {
      RETURN_ERR(GPEGA_ERR_ENDLESSLOOP);
    }
  }
  if (offset) {
    uint32_t instr = 0;
    gpeg_asm_instr(&instr, opcode, 1, 12, 20, *offset);
    vec_append(state->bytecode, &instr, sizeof(instr));
    return 0;
  } else {
    RETURN_ERR(GPEGA_ERR_LABEL);
  }
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      CHECK(gpeg_asm_labeled_instr(state, node, OP_BACKCOMMIT));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      CHECK(gpeg_asm_labeled_instr(state, node, OP_CALL));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      CHECK(gpeg_asm_labeled_instr(state, node, OP_CATCH));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      uint32_t instr = 0;
      unsigned capture = atoi((char*)(node->children[ 0 ]->vec.data));
      gpeg_asm_instr(&instr, OP_CLOSECAPTURE, 1, 16, 16, capture);
      vec_append(state->bytecode, &instr, sizeof(instr));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      CHECK(gpeg_asm_labeled_instr(state, node, OP_COMMIT));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      uint32_t instr = 0;
      unsigned endcode = atoi((char*)(node->children[ 0 ]->vec.data));
      gpeg_asm_instr(&instr, OP_END, 1, 8, 24, endcode);
      vec_append(state->bytecode, &instr, sizeof(instr));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      uint32_t instr = 0;
      gpeg_asm_instr(&instr, OP_FAIL, 0);
      vec_append(state->bytecode, &instr, sizeof(instr));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      uint32_t instr = 0;
      gpeg_asm_instr(&instr, OP_FAILTWICE, 0);
      vec_append(state->bytecode, &instr, sizeof(instr));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      uint32_t instr = 0;
      unsigned capture = atoi((char*)(node->children[ 0 ]->vec.data));
      gpeg_asm_instr(&instr, OP_OPENCAPTURE, 1, 16, 16, capture);
      vec_append(state->bytecode, &instr, sizeof(instr));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      CHECK(gpeg_asm_labeled_instr(state, node, OP_PARTIALCOMMIT));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      uint32_t instr = 0;
      gpeg_asm_instr(&instr, OP_RET, 0);
      vec_append(state->bytecode, &instr, sizeof(instr));
    }
  }
  return 0;
}

static
uint8_t gpeg_asm_hex
  (char* hex)
{
  uint8_t result = 0;
  if (hex[ 0 ] >= 'a' && hex[ 0 ] <= 'f') {
    result |= ((10 + hex[ 0 ] - 'a') << 4);
  } else if (hex[ 0 ] >= 'A' && hex[ 0 ] <= 'F') {
    result |= ((10 + hex[ 0 ] - 'A') << 4);
  } else if (hex[ 0 ] >= '0' && hex[ 0 ] <= '9') {
    result |= ((hex[ 0 ] - '0') << 4);
  }
  if (hex[ 1 ] >= 'a' && hex[ 1 ] <= 'f') {
    result |= (10 + hex[ 1 ] - 'a');
  } else if (hex[ 1 ] >= 'A' && hex[ 1 ] <= 'F') {
    result |= (10 + hex[ 1 ] - 'A');
  } else if (hex[ 1 ] >= '0' && hex[ 1 ] <= '9') {
    result |= (hex[ 1 ] - '0');
  }
  return result;
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      uint32_t instr = 0;
      unsigned p1 = 0xff, p2 = 0, p3 = 0;
      switch (node->nchildren) {
      case 1:
        p2 = p3 = gpeg_asm_hex((char*)(node->children[ 0 ]->vec.data));
        break;
      case 2:
        p2 = gpeg_asm_hex((char*)(node->children[ 0 ]->vec.data));
        p3 = gpeg_asm_hex((char*)(node->children[ 1 ]->vec.data));
        break;
      case 3:
        p1 = gpeg_asm_hex((char*)(node->children[ 2 ]->vec.data));
        p2 = gpeg_asm_hex((char*)(node->children[ 0 ]->vec.data));
        p3 = gpeg_asm_hex((char*)(node->children[ 1 ]->vec.data));
        break;
      }
      gpeg_asm_instr(&instr, OP_RANGE, 3, 8, 8, p1, 16, 8, p2, 24, 8, p3);
      vec_append(state->bytecode, &instr, sizeof(instr));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      uint32_t instr = 0;
      unsigned capture = atoi((char*)(node->children[ 0 ]->vec.data));
      gpeg_asm_instr(&instr, OP_VAR, 1, 16, 16, capture);
      vec_append(state->bytecode, &instr, sizeof(instr));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      unsigned counter = atoi((char*)(node->children[ 0 ]->vec.data));
      unsigned value = atoi((char*)(node->children[ 1 ]->vec.data));
      uint32_t instr = 0;
      gpeg_asm_instr(&instr, OP_COUNTER, 2, 4, 8, counter, 12, 20, value);
      vec_append(state->bytecode, &instr, sizeof(instr));
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
      state->offset += GPEG_INSTR_SIZE;
    } else {
      unsigned counter = atoi((char*)(node->children[ 0 ]->vec.data));
      unsigned* offset = str2int_map_getptr(
          &(state->offsets),
          (char*)(node->children[ 1 ]->vec.data));
      uint32_t instr = 0;
      if (NULL == offset) {
        RETURN_ERR(GPEGA_ERR_LABEL);
      }
      gpeg_asm_instr(&instr, OP_CONDJUMP, 2, 4, 8, counter, 12, 20, *offset);
      vec_append(state->bytecode, &instr, sizeof(instr));
    }
  }
  return 0;
}

static
int gpeg_asm_limit
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct assemblerstate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (state->pass == 1) {
      state->offset += GPEG_INSTR_SIZE;
    } else {
      unsigned endianness = atoi((char*)(node->children[ 0 ]->vec.data));
      unsigned bitlength = atoi((char*)(node->children[ 1 ]->vec.data));
      unsigned slot = atoi((char*)(node->children[ 2 ]->vec.data));
      uint32_t instr = 0;
      if (bitlength > 32) {
        RETURN_ERR(GPEGA_ERR_LIMIT);
      }
      gpeg_asm_instr(&instr, OP_LIMIT, 4
        , 9, 1, 1
        , 10, 1, endianness
        , 11, 5, bitlength-1
        , 16, 16, slot
      );
      vec_append(state->bytecode, &instr, sizeof(instr));
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
  gpeg_result_callback(tree, SLOT_LIMITINSTR, gpeg_asm_limit, &state);

  state.pass = 1;
  CHECK(gpeg_result_run(tree));
  state.pass = 2;
  CHECK(gpeg_result_run(tree));

  RETURN_OK;
}
