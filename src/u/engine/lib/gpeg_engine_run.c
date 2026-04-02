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
  uint8_t       type;
  uint32_t      address;
  uint32_t      inputptr;
  unsigned      actioncount;
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
    if (address) {
      *address = elt.address;
    }
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

static
inline int stack_peek
  (gpege_stack_t* stack, gpege_stackelt_t** elt)
{
  if (stack->count) {
    *elt = &(stack->list[ stack->count-1 ]);
    return 0;
  } else {
    RETURN_ERR(GPEGE_ERR_STACKEMPTY);
  }
}

#define ACT_OPEN  1
#define ACT_CLOSE 2

typedef struct
{
  int      action;
  uint16_t reg;
  uint32_t offset;
}
gpege_action_t;

MAKE_ARRAY_HEADER(gpege_action_t, gpege_actionlist_);
MAKE_ARRAY_CODE(gpege_action_t, gpege_actionlist_);

void wrap_captures
  (
    const vec_t* input,
    unsigned flags,
    gpege_actionlist_t* actions,
    vec_list_t* captures
  )
{
  for (unsigned i=0; i < actions->count; i++) {
    gpege_action_t* action0 = &(actions->list[ i ]);
    if (action0->action == ACT_OPEN) {
      unsigned level = 1;
      for (unsigned j=i+1; j < actions->count; j++) {
        gpege_action_t* action1 = &(actions->list[ j ]);
        if (action1->action == ACT_OPEN) {
          ++level;
        } else if (action1->action == ACT_CLOSE) {
          --level;
          if (level == 0 && action1->reg == action0->reg) {
            vec_t vec = { 0 };
            if (flags & GPEGE_FLG_COPYCAPTURES) {
              vec_append(
                &vec,
                input->data + action0->offset,
                action1->offset - action0->offset
              );
            } else {
              vec.data = input->data + action0->offset;
              vec.size = action1->offset - action0->offset;
            }
            vec_list_push(captures, vec);
          }
        }
      }
    }
  }
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
    unsigned flags,
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
  uint_map_t capreg = { 0 };
  gpege_actionlist_t actions = { 0 };

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
      {
        gpege_stackelt_t elt = {
          .type = STACK_CALL,
          .address = instrptr + 4,
          .actioncount = actions.count,
        };
        gpege_stack_push(&stack, elt);
        instrptr = GPEGU_INSTR_OFFSET(instr8);
      }
      break;
    case OP_RET:
      CHECK(stack_pop(&stack, STACK_CALL, &instrptr));
      break;
    case OP_CATCH:
      {
        gpege_stackelt_t elt = {
          .type = STACK_CATCH,
          .address = GPEGU_INSTR_OFFSET(instr8),
          .actioncount = actions.count,
        };
        gpege_stack_push(&stack, elt);
        instrptr += 4;
      }
      break;
    case OP_COMMIT:
      CHECK(stack_pop(&stack, STACK_CATCH, NULL));
      instrptr = GPEGU_INSTR_OFFSET(instr8);
      break;
    case OP_BACKCOMMIT:
      {
        gpege_stackelt_t elt = { 0 };
        CHECK(gpege_stack_pop(&stack, &elt));
        inputptr = elt.inputptr;
        actions.count = elt.actioncount; // TODO: If actions.count smaller
        instrptr = GPEGU_INSTR_OFFSET(instr8);
      }
      break;
    case OP_PARTIALCOMMIT:
      {
        gpege_stackelt_t* eltptr = NULL;
        CHECK(stack_peek(&stack, &eltptr));
        eltptr->inputptr = inputptr;
        eltptr->actioncount = actions.count;
        instrptr = GPEGU_INSTR_OFFSET(instr8);
      }
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
      {
        uint16_t reg = (instr8[2] << 8) | instr8[3];
        gpege_action_t action = {
          .action = ACT_OPEN,
          .reg    = reg,
          .offset = inputptr,
        };
        gpege_actionlist_push(&actions, action);
        instrptr += 4;
      }
      break;
    case OP_CLOSECAPTURE:
      {
        uint16_t reg = (instr8[2] << 8) | instr8[3];
        gpege_action_t action = {
          .action = ACT_CLOSE,
          .reg    = reg,
          .offset = inputptr,
        };
        gpege_actionlist_push(&actions, action);
        instrptr += 4;
      }
      break;
    case OP_COUNTER:
      {
        uint8_t ctr = ((instr8[0] & 0x0f) << 4) | ((instr8[1] & 0xf0) >> 4);
        uint32_t value = GPEGU_INSTR_OFFSET(instr8);
        uint_map_put(&capreg, ctr, value);
        instrptr += 4;
      }
      break;
    case OP_CONDJUMP:
      {
        uint8_t ctr = ((instr8[0] & 0x0f) << 4) | ((instr8[1] & 0xf0) >> 4);
        uint32_t offset = GPEGU_INSTR_OFFSET(instr8);
        uint32_t value = 0;
        if (uint_map_get(&capreg, ctr, &value) == 0) {
          if (value == 1) {
            instrptr += 4;
          } else {
            instrptr = offset;
          }
        } else {
          RETURN_ERR(GPEGE_ERR_CAPREG);
        }
      }
      break;
    }
    if (failed) {
      CHECK(stack_fail(&stack, &instrptr));
    }
  }
  wrap_captures(input, flags, &actions, &(result->captures));
  return 0;
}
