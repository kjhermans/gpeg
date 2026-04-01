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

#include <gpeg/engine/lib.h>

#define STACK_CALL  1
#define STACK_CATCH 2

#define GPEGU_INSTR_OFFSET(_ptr8) \
  (uint32_t)(((_ptr8[1]&0x0f)<<16)|(_ptr8[2]<<8)|_ptr8[3])

typedef struct
{
  uint8_t type;
  uint32_t address;
}
gpege_stackelt_t;

#undef ARRAY_EQUALS
#define ARRAY_EQUALS(a,b) (&a == &b)
MAKE_ARRAY_HEADER(gpege_stackelt_t, gpege_stack_);
MAKE_ARRAY_CODE(gpege_stackelt_t, gpege_stack_);

static
inline void stack_push
  (gpege_stack_t* stack, uint8_t type, uint32_t address)
{
  gpege_stackelt_t elt = {
    .type = type,
    .address = address,
  };
  gpege_stack_push(stack, elt);
}

static
inline int stack_pop
  (gpege_stack_t* stack, uint8_t type, uint32_t* address)
{
  gpege_stackelt_t elt = { 0 };
  if (stack->count == 0) {
    RETURN_ERR(GPEGE_ERR_STACKEMPTY);
  }
  if (gpege_stack_pop(stack, &elt) == 0) {
    if (elt.type != type) {
      RETURN_ERR(GPEGE_ERR_STACKELT);
    }
    *address = elt.address;
  }
  return 0;
}

static
inline int stack_fail
  (gpege_stack_t* stack, uint32_t* address)
{
  if (stack->count == 0) {
    RETURN_ERR(GPEGE_ERR_STACKEMPTY);
  }
  while (stack->count) {
    gpege_stackelt_t elt = { 0 };
    if (gpege_stack_pop(stack, &elt) == 0) {
      if (elt.type == STACK_CATCH) {
        *address = elt.address;
        return 0;
      }
    }
  }
  return 0;
}

/**
 * Runs the GPEG engine using \p bytecode on \p input.
 * Returns zero on success (no fatal errors), or non-zero on fatal errors.
 * A non-match is not a fatal error; therefore examining the \p result
 * structure is probably wise.
 */
int gpeg_engine_run
  (
    const vec_t* bytecode,
    const vec_t* input,
    gpege_result_t* result
  )
{
  int ended = 0;
  int failed = 0;
  unsigned instrptr = 0;
  uint8_t* instr8 = 0;
  unsigned inputptr = 0;
  uint8_t* input8 = 0;
  uint8_t opcode = 0;
  int eof = 0;
  gpege_stack_t stack = { 0 };

  while (!ended && !(failed && stack.count == 0)) {
    failed = 0;
    if (instrptr >= bytecode->size + 4) {
      RETURN_ERR(GPEGE_ERR_OVERFLOW);
    }
    if (inputptr >= input->size) {
      eof = 1;
    } else {
      eof = 0;
      input8 = input->data + inputptr;
    }
    instr8 = bytecode->data + instrptr;
    opcode = (*instr8) >> 4;
    switch (opcode) {
    case OP_END:
      result->success = 1;
      result->endcode = (
        (instr8[1]<<16) |
        (instr8[2]<<8) |
        instr8[3]
      );
      ended = 1;
      break;
    case OP_RANGE:
      if (eof ||
          (*input8 & instr8[1]) < instr8[2] ||
          (*input8 & instr8[1]) > instr8[3])
      {
        failed = 1;
      } else {
        instrptr += 4;
        inputptr++;
      }
      break;
    case OP_LIMIT:
      break;
    case OP_CALL:
      stack_push(&stack, STACK_CALL, instrptr + 4);
      instrptr = GPEGU_INSTR_OFFSET(instr8);
      break;
    case OP_RET:
      CHECK(stack_pop(&stack, STACK_CALL, &instrptr));
      break;
    case OP_CATCH:
      stack_push(&stack, STACK_CATCH, GPEGU_INSTR_OFFSET(instr8));
      instrptr += 4;
      break;
    case OP_COMMIT:
      CHECK(stack_pop(&stack, STACK_CATCH, &instrptr));
      break;
    case OP_BACKCOMMIT:
      break;
    case OP_PARTIALCOMMIT:
      break;
    case OP_FAIL:
      failed = 1;
      break;
    case OP_FAILTWICE:
      CHECK(stack_fail(&stack, &instrptr));
      failed = 1;
      break;
    case OP_VAR:
      break;
    case OP_OPENCAPTURE:
      break;
    case OP_CLOSECAPTURE:
      break;
    case OP_COUNTER:
      break;
    case OP_CONDJUMP:
      break;
    }
    if (failed) {
      CHECK(stack_fail(&stack, &instrptr));
    }
  }
  return 0;
}
