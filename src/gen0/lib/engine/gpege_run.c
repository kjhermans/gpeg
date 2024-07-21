/**
 * This file is part of GPEG, a parsing environment

Copyright (c) 2023, Kees-Jan Hermans <kees.jan.hermans@gmail.com>
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

#include <string.h>

#include "gpege_private.h"
#include <gpeg/lib/gpeg/gpeg_instructions.h>

/* Binary */

#define HANDLE_MOVETO { \
}

#define HANDLE_RMOVETO { \
}

#define HANDLE_IRMOVETO { \
}

#define HANDLE_EQ { \
}

#define HANDLE_NEQ { \
}

#define HANDLE_LT { \
}

#define HANDLE_GT { \
}

#define HANDLE_LTEQ { \
}

#define HANDLE_GTEQ { \
}

/* Other */

#define HANDLE_NOOP { \
  ec->bytecode_offset += instruction_size; \
}

#define HANDLE_END { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 8 \
  ); \
  ec->endcode = param; \
  return GPEG_OK; \
}

#define HANDLE_ANY { \
  if (ec->input_offset < ec->input->size) { \
    ++(ec->input_offset); \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->failed = 1; \
  } \
}

#define HANDLE_SKIP { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  if (ec->input_offset <= ec->input->size - param) { \
    ec->input_offset += param; \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->failed = 1; \
  } \
}

#define HANDLE_CHAR { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  if (ec->input_offset < ec->input->size && \
      ec->input->data[ ec->input_offset ] == param) \
  { \
    ++(ec->input_offset); \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->failed = 1; \
  } \
}

#define HANDLE_RANGE { \
  uint32_t param1 = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  uint32_t param2 = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 8 \
  ); \
  if (ec->input_offset < ec->input->size && \
      ec->input->data[ ec->input_offset ] >= param1 && \
      ec->input->data[ ec->input_offset ] <= param2) \
  { \
    ++(ec->input_offset); \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->failed = 1; \
  } \
}

#define HANDLE_BITMASK { \
  uint32_t nbits = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  uint32_t bits = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 8 \
  ); \
  uint32_t andmask = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 12 \
  ); \
  uint32_t nbytes = ((nbits + 7) / 8); \
  if (ec->input_offset + nbytes <= ec->input->size) { \
    for (unsigned i=0; i < nbytes; i++) { \
      uint8_t byte = bits & 0xff; \
      uint8_t mask = andmask & 0xff; \
      if ((ec->input->data[ ec->input_offset+i ] & mask) != byte) { \
        ec->failed = 1; \
        break; \
      } \
      nbits -= 8; \
      bits >>= 8; \
      andmask >>= 8; \
    } \
    if (!(ec->failed)) { \
      ec->input_offset += nbytes; \
      ec->bytecode_offset += instruction_size; \
    } \
  } else { \
    ec->failed = 1; \
  } \
}

#define HANDLE_QUAD { \
  unsigned char* set = gpege->bytecode.data + ec->bytecode_offset + 4; \
  if (ec->input_offset <= ec->input->size - 4 && \
      0 == memcmp(ec->input->data + ec->input_offset, set, 4)) \
  { \
    (ec->input_offset) += 4; \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->failed = 1; \
  } \
}

#define HANDLE_SET { \
  unsigned char* set = gpege->bytecode.data + ec->bytecode_offset + 4; \
  if (ec->input_offset < ec->input->size && \
      GPEGE_DATA_IN_SET(set, ec->input->data[ ec->input_offset ])) \
  { \
    ++(ec->input_offset); \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->failed = 1; \
  } \
}

#define HANDLE_TESTANY { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  if (ec->input_offset < ec->input->size) { \
    ++(ec->input_offset); \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->bytecode_offset = param; \
  } \
}

#define HANDLE_TESTCHAR { \
  uint32_t offset = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  uint32_t matchchar = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  if (ec->input_offset < ec->input->size && \
      ec->input->data[ ec->input_offset ] == matchchar) \
  { \
    ++(ec->input_offset); \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->bytecode_offset = offset; \
  } \
}

#define HANDLE_TESTSET { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  unsigned char* set = gpege->bytecode.data + ec->bytecode_offset + 8; \
  if (ec->input_offset < ec->input->size && \
      GPEGE_DATA_IN_SET(set, ec->input->data[ ec->input_offset ])) \
  { \
    ++(ec->input_offset); \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->bytecode_offset = param; \
  } \
}

#define HANDLE_VAR { \
  unsigned char* value; \
  unsigned valuesize; \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  GPEG_CHECK(gpege_variable(gpege, ec, param, &value, &valuesize), PROPAGATE); \
  if (valuesize == 0) { \
    ec->failed = 1; \
  } else if (ec->input_offset + valuesize <= ec->input->size && \
             0 == memcmp(ec->input->data + ec->input_offset, value, valuesize)) \
  { \
    ec->input_offset += valuesize; \
    ec->bytecode_offset += instruction_size; \
  } else { \
    ec->failed = 1; \
  } \
}

#define HANDLE_CALL { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  unsigned callcontext = ++(ec->callcounter); \
  gpege_stack_push( \
    &(ec->stack), \
    (gpege_stackelt_t) { \
      .type = GPEGE_STACK_CALL, \
      .address = ec->bytecode_offset + instruction_size, \
      .input_offset = ec->input_offset, \
      .input_length = ec->input->size, \
      .action_count = ec->actions.count, \
      .register_count = ec->reg.count, \
      .call_context = ec->currentcall \
    } \
  ); \
  if (ec->stack.count > ec->stack_max) { ec->stack_max = ec->stack.count; } \
  ec->bytecode_offset = param; \
  ec->currentcall = callcontext; \
  if (ec->reg_ilen_set) { \
    ec->input->size = ec->reg_ilen; \
    ec->reg_ilen_set = 0; \
    ec->reg_ilen = 0; \
  } \
}

#define HANDLE_RET { \
  gpege_stackelt_t elt; \
  if (gpege_stack_size(&(ec->stack))) { \
    gpege_stack_pop(&(ec->stack), &elt); \
    if (elt.type == GPEGE_STACK_CALL) { \
      ec->bytecode_offset = elt.address; \
      ec->input->size = elt.input_length; \
      ec->currentcall = elt.call_context; \
      break; \
    } \
  } \
  RETURNERR(GPEG_ERR_BYTECODE); \
}

#define HANDLE_CATCH { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  gpege_stack_push( \
    &(ec->stack), \
    (gpege_stackelt_t) { \
      .type = GPEGE_STACK_CATCH, \
      .address = param, \
      .input_offset = ec->input_offset, \
      .input_length = ec->input->size, \
      .action_count = ec->actions.count, \
      .register_count = ec->reg.count \
    } \
  ); \
  if (ec->stack.count > ec->stack_max) { ec->stack_max = ec->stack.count; } \
  ec->bytecode_offset = ec->bytecode_offset + instruction_size; \
}

#define HANDLE_COMMIT { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  gpege_stackelt_t elt; \
  if (gpege_stack_size(&(ec->stack))) { \
    gpege_stack_pop(&(ec->stack), &elt); \
    if (elt.type == GPEGE_STACK_CATCH) { \
      ec->bytecode_offset = param; \
      break; \
    } \
  } \
  RETURNERR(GPEG_ERR_BYTECODE); \
}

#define HANDLE_BACKCOMMIT { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  gpege_stackelt_t elt; \
  if (gpege_stack_size(&(ec->stack))) { \
    gpege_stack_pop(&(ec->stack), &elt); \
    if (elt.action_count > ec->actions.count) { \
      RETURNERR(GPEG_ERR_BYTECODE); \
    } \
    if (elt.type == GPEGE_STACK_CATCH) { \
      ec->bytecode_offset = param; \
      ec->input_offset = elt.input_offset; \
      ec->actions.count = elt.action_count; \
      break; \
    } \
  } \
  RETURNERR(GPEG_ERR_BYTECODE); \
}

#define HANDLE_PARTIALCOMMIT { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  gpege_stackelt_t elt; \
  if (0 == gpege_stack_pop(&(ec->stack), &elt)) { \
    if (elt.type == GPEGE_STACK_CATCH) { \
      elt.input_offset = ec->input_offset; \
      elt.action_count = ec->actions.count; \
      ec->bytecode_offset = param; \
      gpege_stack_push(&(ec->stack), elt); \
      break; \
    } \
  } \
  RETURNERR(GPEG_ERR_BYTECODE); \
}
  
#define HANDLE_FAIL { \
  ec->failed = 1; \
}

#define HANDLE_FAILTWICE { \
  gpege_stackelt_t elt; \
  if (gpege_stack_pop(&(ec->stack), &elt) || \
      elt.type != GPEGE_STACK_CATCH) \
  { \
    RETURNERR(GPEG_ERR_BYTECODE); \
  } \
  if (0 == gpege_stack_size(&(ec->stack))) { \
    RETURNERR(GPEG_ERR_NOMATCH); \
  } \
  ec->failed = 1; \
}

#define HANDLE_OPENCAPTURE { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  gpege_actionlist_push(&(ec->actions), (gpege_action_t){ \
    .type = GPEGE_ACTION_OPENCAPTURE, \
    .slot = param, \
    .input_offset = ec->input_offset, \
    .call_context = ec->currentcall \
  }); \
  ec->bytecode_offset += instruction_size; \
}

#define HANDLE_CLOSECAPTURE { \
  uint32_t param = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  gpege_actionlist_push(&(ec->actions), (gpege_action_t){ \
    .type = GPEGE_ACTION_CLOSECAPTURE, \
    .slot = param, \
    .input_offset = ec->input_offset, \
    .call_context = ec->currentcall \
  }); \
  ec->bytecode_offset += instruction_size; \
}

#define HANDLE_COUNTER { \
  uint32_t param1 = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  uint32_t param2 = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 8 \
  ); \
  gpege_register_push(&(ec->reg), (gpege_regelt_t){ \
    .reg = param1, \
    .stacklen = ec->stack.count, \
    .value = param2 \
  }); \
  ec->bytecode_offset += instruction_size; \
}

#define HANDLE_CONDJUMP { \
  int i; \
  gpege_regelt_t* elt; \
  uint32_t param1 = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  uint32_t param2 = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 8 \
  ); \
  if ((i = gpege_register_lastindexof(&(ec->reg), (gpege_regelt_t){ \
          .reg = param1, \
          .stacklen = ec->stack.count, \
        })) == -1) \
  { \
    RETURNERR(GPEG_ERR_BYTECODE); \
  } \
  elt = gpege_register_getptr(&(ec->reg), i); \
  if (elt->value <= 1) { \
    ec->bytecode_offset += instruction_size; \
    gpege_register_rem(&(ec->reg), i, 0); \
  } else { \
    --(elt->value); \
    ec->bytecode_offset = param2; \
  } \
}

#define HANDLE_FAILURE { \
  while (gpege_stack_size(&(ec->stack))) { \
    gpege_stackelt_t elt; \
    gpege_stack_pop(&(ec->stack), &elt); \
    if (elt.type == GPEGE_STACK_CATCH) { \
      ec->bytecode_offset = elt.address; \
      ec->input_offset = elt.input_offset; \
      ec->actions.count = elt.action_count; \
      ec->reg.count = elt.register_count; \
      break; \
    } else if (elt.type == GPEGE_STACK_CALL) { \
      ec->currentcall = elt.call_context; \
    } \
  } \
  if (0 == gpege_stack_size(&(ec->stack))) { \
    RETURNERR(GPEG_ERR_NOMATCH); \
  } \
}

#define HANDLE_INTRPCAPTURE { \
  uint32_t param1 = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 4 \
  ); \
  uint32_t param2 = GET_32BIT_VALUE( \
    gpege->bytecode.data, \
    ec->bytecode_offset + 8 \
  ); \
  unsigned char* value; \
  unsigned valuesize; \
  GPEG_CHECK(gpege_variable(gpege, ec, param1, &value, &valuesize), PROPAGATE); \
  if (valuesize == 0) { \
    RETURNERR(GPEG_ERR_INTRPCAPTURE); \
  } \
  switch (param2) { \
  case GPEG_INTRPCAPTURE_RUINT32: \
    if (valuesize <= 4) { \
      ec->reg_ilen = \
        (value[ 0 ] << ((valuesize-1) * 8)) | \
        ((valuesize > 1) ? (value[ 1 ] << ((valuesize-2) * 8)) : 0) | \
        ((valuesize > 2) ? (value[ 2 ] << ((valuesize-3) * 8)) : 0) | \
        ((valuesize > 3) ? (value[ 3 ]) : 0); \
      ec->reg_ilen += ec->input_offset; \
      if (ec->reg_ilen > ec->input->size) { \
        RETURNERR(GPEG_ERR_INTRPCAPTURE); \
      } \
      ec->reg_ilen_set = 1; \
    } else { \
      RETURNERR(GPEG_ERR_INTRPCAPTURE); \
    } \
  } \
  ec->bytecode_offset += instruction_size; \
}

#define HANDLE_TRAP { \
  if (!(gpege->debugger)) { \
    RETURNERR(GPEG_ERR_TRAP); \
  } \
  ec->bytecode_offset += instruction_size; \
}


/**
 *
 */
GPEG_ERR_T gpege_run
  (gpege_t* gpege, gpege_ec_t* ec)
{
  DEBUGFUNCTION;
  ASSERT(gpege);
  ASSERT(ec);

  uint32_t opcode;
  unsigned instruction_size;

  while (1) {
    if (ec->bytecode_offset > gpege->bytecode.size) {
      RETURNERR(GPEG_ERR_OVERFLOW);
    }
    opcode = GET_32BIT_VALUE(gpege->bytecode.data, ec->bytecode_offset);
    instruction_size = ((opcode >> 16) & 0xff) + 4;
    if (ec->bytecode_offset + instruction_size > gpege->bytecode.size) {
      RETURNERR(GPEG_ERR_OVERFLOW);
    }
    if (gpege->debugger) {
      GPEG_CHECK(
        gpege->debugger(gpege, ec, opcode, gpege->debugarg),
        PROPAGATE
      );
    }
    if (ec->input_offset > ec->input_offset_max) {
      ec->input_offset_max = ec->input_offset;
    }
    switch (opcode) {
    case OPCODE_END:             { HANDLE_END }             break;
    case OPCODE_ANY:             { HANDLE_ANY }             break;
    case OPCODE_RANGE:           { HANDLE_RANGE }           break;
    case OPCODE_CALL:            { HANDLE_CALL }            break;
    case OPCODE_RET:             { HANDLE_RET }             break;
    case OPCODE_CATCH:           { HANDLE_CATCH }           break;
    case OPCODE_COMMIT:          { HANDLE_COMMIT }          break;
    case OPCODE_BACKCOMMIT:      { HANDLE_BACKCOMMIT }      break;
    case OPCODE_PARTIALCOMMIT:   { HANDLE_PARTIALCOMMIT }   break;
    case OPCODE_FAIL:            { HANDLE_FAIL }            break;
    case OPCODE_FAILTWICE:       { HANDLE_FAILTWICE }       break;
    case OPCODE_VAR:             { HANDLE_VAR }             break;
    case OPCODE_OPENCAPTURE:     { HANDLE_OPENCAPTURE }     break;
    case OPCODE_CLOSECAPTURE:    { HANDLE_CLOSECAPTURE }    break;
#ifdef _GPEG_INSTRSET_OPTIMIZED_
    case OPCODE_COUNTER:         { HANDLE_COUNTER }         break;
    case OPCODE_CONDJUMP:        { HANDLE_CONDJUMP }        break;
    case OPCODE_SKIP:            { HANDLE_SKIP }            break;
    case OPCODE_NOOP:            { HANDLE_NOOP }            break;
    case OPCODE_TRAP:            { HANDLE_TRAP }            break;
    case OPCODE_QUAD:            { HANDLE_QUAD }            break;
    case OPCODE_CHAR:            { HANDLE_CHAR }            break;
    case OPCODE_SET:             { HANDLE_SET }             break;
    case OPCODE_TESTANY:         { HANDLE_TESTANY }         break;
    case OPCODE_TESTCHAR:        { HANDLE_TESTCHAR }        break;
    case OPCODE_TESTSET:         { HANDLE_TESTSET }         break;
#endif
#ifdef _GPEG_INSTRSET_BINARY_
    case OPCODE_BITMASK:         { HANDLE_BITMASK }         break;
    case OPCODE_INTRPCAPTURE:    { HANDLE_INTRPCAPTURE }    break;
    case OPCODE_MOVETO:          { HANDLE_MOVETO }          break;
    case OPCODE_RMOVETO:         { HANDLE_RMOVETO }         break;
    case OPCODE_IRMOVETO:        { HANDLE_IRMOVETO }        break;
    case OPCODE_NEQ:             { HANDLE_NEQ }             break;
    case OPCODE_EQ:              { HANDLE_EQ }              break;
    case OPCODE_LT:              { HANDLE_LT }              break;
    case OPCODE_GT:              { HANDLE_GT }              break;
    case OPCODE_LTEQ:            { HANDLE_LTEQ }            break;
    case OPCODE_GTEQ:            { HANDLE_GTEQ }            break;
#endif
    default: RETURNERR(GPEG_ERR_BYTECODE);
    }
    if (ec->failed) {
      ec->failed = 0;
      if (gpege->debugger) {
        GPEG_CHECK(
          gpege->debugger(gpege, ec, OPCODE_FAILURE, gpege->debugarg),
          PROPAGATE
        );
      }
      HANDLE_FAILURE
    }
    ++(ec->ninstructions);
    if (gpege->maxinstructions && ec->ninstructions > gpege->maxinstructions) {
      RETURNERR(GPEG_ERR_MAXINSTRUCTIONS);
    }
  }
}
