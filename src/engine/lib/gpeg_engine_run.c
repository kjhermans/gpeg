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

static
char* instrstr[] = {
  "end",
  "rng",
  "lim",
  "cll",
  "ret",
  "ctc",
  "com",
  "bcm",
  "pcm",
  "fai",
  "fa2",
  "var",
  "ocp",
  "ccp",
  "ctr",
  "cjp",
};

#define GPEGU_INSTR_OFFSET(_ptr8) \
  (uint32_t)(((_ptr8[1]&0x0f)<<16)|(_ptr8[2]<<8)|_ptr8[3])

typedef struct
{
  uint8_t       type;
  uint32_t      instrptr;
  uint32_t      inputptr;
  unsigned      actioncount;
  unsigned      countercount;
}
gpege_stackelt_t;

#undef ARRAY_EQUALS
#define ARRAY_EQUALS(a,b) (&a == &b)
MAKE_ARRAY_HEADER(gpege_stackelt_t, gpege_stack_);
MAKE_ARRAY_CODE(gpege_stackelt_t, gpege_stack_);

static
inline int stack_pop
  (
    gpege_stack_t* stack,
    unsigned type,
    gpege_stackelt_t* found
  )
{
  gpege_stackelt_t elt = { 0 };
  if (stack->count == 0) {
    RETURN_ERR(GPEGE_ERR_STACKEMPTY);
  }
  gpege_stack_pop(stack, &elt);
  if (type && elt.type != type) {
    RETURN_ERR(GPEGE_ERR_STACKELT);
  }
  if (found != NULL) {
    *found = elt;
  }
  return 0;
}

static
inline int stack_fail
  (gpege_stack_t* stack, gpege_stackelt_t* ret)
{
  gpege_stackelt_t elt = { 0 };
  if (stack->count == 0) {
    RETURN_ERR(GPEGE_ERR_STACKEMPTY);
  }
#ifdef _DEBUG
  fprintf(stderr, "FAIL: ");
#endif
  while (stack->count) {
    stack_pop(stack, 0, &elt);
#ifdef _DEBUG
    fprintf(stderr, "[%s,%u]"
      , (elt.type == STACK_CATCH ? "ctc" : "cll"), elt.instrptr);
#endif
    if (elt.type == STACK_CATCH) {
      if (ret) { *ret = elt; }
      break;
    }
#ifdef _DEBUG
    else { fprintf(stderr, ", "); }
#endif
  }
#ifdef _DEBUG
  fprintf(stderr, "\n");
#endif
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
  unsigned stacklen;
}
gpege_action_t;

MAKE_ARRAY_HEADER(gpege_action_t, gpege_actionlist_);
MAKE_ARRAY_CODE(gpege_action_t, gpege_actionlist_);

MAKE_ARRAY_CODE(gpege_capture_t, gpege_caplist_);

static
inline void wrap_captures
  (
    const vec_t* input,
    unsigned flags,
    gpege_actionlist_t* actions,
    gpege_caplist_t* captures
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
            gpege_capture_t capture = {
              .reg = action0->reg,
              .offset = action0->offset,
            };
            if (flags & GPEGE_FLG_COPYCAPTURES) {
              vec_append(
                &(capture.vec),
                input->data + action0->offset,
                action1->offset - action0->offset
              );
            } else {
              capture.vec.data = input->data + action0->offset;
              capture.vec.size = action1->offset - action0->offset;
            }
            gpege_caplist_push(captures, capture);
            break;
          }
        }
      }
    }
  }
}

/*
static
void gpege_actionlist_debug
  (const vec_t* input, gpege_actionlist_t* list)
{
  for (unsigned i=0; i < list->count; i++) {
    fprintf(stderr,
      "ACTION %u: %s reg=%u off=%u stk=%u "
      , i
      , list->list[ i ].action == ACT_OPEN ? "open " : "close"
      , list->list[ i ].reg
      , list->list[ i ].offset
      , list->list[ i ].stacklen
    );
    if (input && list->list[ i ].action == ACT_OPEN) {
      for (unsigned j=0; j < 12; j++) {
        char c = input->data[ list->list[ i ].offset + j ];
        fprintf(stderr, "%c", (c >= 32 && c < 127) ? c : '.');
      }
    }
    fprintf(stderr, "\n");
  }
}
*/

static
inline int resolve_variable
  (
    const vec_t* input,
    gpege_actionlist_t* actions,
    uint16_t reg,
    unsigned stacklen,
    vec_t* result
  )
{
  int option_set = 0;
  unsigned option_offset = 0;
  unsigned option_length = 0;
  unsigned option_stacklen = 0;

  for (unsigned i=0; i < actions->count; i++) {
    gpege_action_t* action0 = &(actions->list[ i ]);
    if (action0->action == ACT_OPEN
        && (0 == reg || action0->reg == reg)
        && action0->stacklen >= stacklen)
    {
      unsigned level = 1;
      for (unsigned j = i+1; j < actions->count; j++) {
        gpege_action_t* action1 = &(actions->list[ j ]);
        if (action1->action == ACT_CLOSE) {
          --level;
          if (level == 0 && (0 == reg || action1->reg == action0->reg)) {
            if (option_set == 0) {
              option_set = 1;
              option_offset = action0->offset;
              option_length = action1->offset - action0->offset;
              option_stacklen = action0->stacklen;
            } else if (action0->stacklen <= option_stacklen) {
              option_offset = action0->offset;
              option_length = action1->offset - action0->offset;
              option_stacklen = action0->stacklen;
            }
          }
        } else if (action1->action == ACT_OPEN) {
          ++level;
        }
      }
    }
  }
  if (option_set) {
    result->data = input->data + option_offset;
    result->size = option_length;
    return 0;
  } else {
    RETURN_ERR(GPEGE_ERR_VARIABLE);
  }
}

#ifdef _DEBUG
static char readable_buf[ 9 ];

static
char* readable_text
  (const vec_t* input, unsigned inputptr)
{
  unsigned o = 0;
  while (o < sizeof(readable_buf)-1 && o + inputptr < input->size) {
    char c = input->data[ inputptr + o ];
    if (c > 32 && c < 127) {
      readable_buf[ o ] = c;
    } else {
      readable_buf[ o ] = '.';
    }
    o++;
  }
  readable_buf[ o ] = 0;
  return readable_buf;
}
#endif

#define CLEANUP { r = __r; goto CLEAN_UP; }

static
unsigned maxinstrctr = GPEGE_MAX_INSTRUCTIONS;

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
  DEBUGFUNCTION
  ASSERT(bytecode)
  ASSERT(input)
  ASSERT(result)

  int ended = 0;
  int failed = 0;
  unsigned instrptr = 0;
  uint8_t* instr8 = 0;
  unsigned inputptr = 0;
  unsigned inputsiz = input->size;
  uint8_t* input8 = 0;
  uint8_t opcode = 0;
  int eof = 0;
  gpege_stack_t stack = { 0 };
  gpege_actionlist_t actions = { 0 };
  uint32list_t inputsizes = { 0 };
  int r = 0;
  unsigned instrctr = 0;
  unsigned counters[ GPEGE_MAX_COUNTERS ][ 2 ] = { 0 };
  unsigned countercount = 0;

  (void)instrstr;

  while (!ended && !(failed && stack.count == 0)) {
    if (++instrctr > maxinstrctr) {
      RETURN_ERR2(GPEGE_ERR_MAXINSTR, CLEANUP);
    }
    failed = 0;
    if (instrptr >= bytecode->size + 4) {
      RETURN_ERR2(GPEGE_ERR_OVERFLOW, CLEANUP);
    }
    if (inputptr >= inputsiz) {
      eof = 1;
    } else {
      eof = 0;
      input8 = input->data + inputptr;
    }
    if (inputptr > result->maxinputptr) {
      result->maxinputptr = inputptr;
    }
    instr8 = bytecode->data + instrptr;
    opcode = instr8[0] >> 4;
#ifdef _DEBUG
    fprintf(stderr,
      "%.8u: %.8u: %s: %.8u: %s: #s=%u\n"
      , instrctr-1
      , instrptr
      , instrstr[opcode]
      , inputptr
      , (eof ? "EOF" : readable_text(input, inputptr))
      , stack.count
    );
#endif
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
      {
        unsigned O   = ((instr8[1]>>6)&0x01);
        unsigned E   = ((instr8[1]>>5)&0x01);
        unsigned S   =  (instr8[1]&0x1f) + 1;
        unsigned reg = ((instr8[2]<<8)|(instr8[3]));
        if (O) {
          uint32_t len = 0;
          vec_t value = { 0 };
          CHECK2(
            resolve_variable(input, &actions, reg, stack.count, &value),
            CLEANUP
          );
          for (unsigned i=0; i < S && i < value.size * 8; i++) {
            int bit = 0;
            if (E) {
              bit = (value.data[ value.size-((i/8)+1) ] & (1<<(i%8)) ? 1 : 0);
            } else {
              bit = (value.data[ i/8 ] & (1<<(i%8)) ? 1 : 0);
            }
            if (bit) {
              len |= (1<<i);
            }
          }
          uint32list_push(&inputsizes, len);
          if (len > inputsiz) {
            RETURN_ERR(GPEGE_ERR_LIMIT);
          }
          inputsiz = len;
        } else {
          uint32list_pop(&inputsizes, 0);
        }
        instrptr += 4;
      }
      break;
    case OP_CALL:
      {
        gpege_stackelt_t elt = {
          .type = STACK_CALL,
          .instrptr= instrptr + 4,
          .inputptr = inputptr,
          .actioncount = actions.count,
          .countercount = countercount,
        };
        gpege_stack_push(&stack, elt);
        instrptr = GPEGU_INSTR_OFFSET(instr8);
      }
      break;
    case OP_RET:
      {
        gpege_stackelt_t elt = { 0 };
        CHECK2(stack_pop(&stack, STACK_CALL, &elt), CLEANUP);
        instrptr = elt.instrptr;
      }
      break;
    case OP_CATCH:
      {
        gpege_stackelt_t elt = {
          .type = STACK_CATCH,
          .instrptr = GPEGU_INSTR_OFFSET(instr8),
          .inputptr = inputptr,
          .actioncount = actions.count,
          .countercount = countercount,
        };
        gpege_stack_push(&stack, elt);
        instrptr += 4;
      }
      break;
    case OP_COMMIT:
      CHECK2(stack_pop(&stack, STACK_CATCH, NULL), CLEANUP);
      instrptr = GPEGU_INSTR_OFFSET(instr8);
      break;
    case OP_BACKCOMMIT:
      {
        gpege_stackelt_t elt = { 0 };
        CHECK2(stack_pop(&stack, 0, &elt), CLEANUP);
        inputptr = elt.inputptr;
        actions.count = elt.actioncount;
        countercount = elt.countercount;
        instrptr = GPEGU_INSTR_OFFSET(instr8);
      }
      break;
    case OP_PARTIALCOMMIT:
      {
        gpege_stackelt_t* eltptr = NULL;
        CHECK2(stack_peek(&stack, &eltptr), CLEANUP);
        eltptr->inputptr = inputptr;
        eltptr->actioncount = actions.count;
        eltptr->countercount = countercount;
        instrptr = GPEGU_INSTR_OFFSET(instr8);
      }
      break;
    case OP_FAIL:
      failed = 1;
      break;
    case OP_FAILTWICE:
      CHECK2(stack_fail(&stack, NULL), CLEANUP);
      failed = 1;
      break;
    case OP_VAR:
      {
        uint16_t reg = (instr8[2] << 8) | instr8[3];
        vec_t value = { 0 };
        CHECK2(
          resolve_variable(input, &actions, reg, stack.count, &value),
          CLEANUP
        );
        if (value.size == 0) {
          failed = 1;
        } else if (inputptr + value.size > input->size) {
          failed = 1;
        } else if (eof) {
          failed = 1;
        } else if (0 != memcmp(input8, value.data, value.size)) {
          failed = 1;
        } else {
          inputptr += value.size;
          instrptr += 4;
        }
      }
      break;
    case OP_OPENCAPTURE:
      {
        uint16_t reg = (instr8[2] << 8) | instr8[3];
        gpege_action_t action = {
          .action   = ACT_OPEN,
          .reg      = reg,
          .offset   = inputptr,
          .stacklen = stack.count,
        };
        gpege_actionlist_push(&actions, action);
        instrptr += 4;
      }
      break;
    case OP_CLOSECAPTURE:
      {
        uint16_t reg = (instr8[2] << 8) | instr8[3];
        gpege_action_t action = {
          .action   = ACT_CLOSE,
          .reg      = reg,
          .offset   = inputptr,
          .stacklen = stack.count,
        };
        gpege_actionlist_push(&actions, action);
        instrptr += 4;
      }
      break;
    case OP_COUNTER:
      {
        uint8_t ctr = ((instr8[0] & 0x0f) << 4) | ((instr8[1] & 0xf0) >> 4);
        uint32_t value = GPEGU_INSTR_OFFSET(instr8);
        if (countercount == GPEGE_MAX_COUNTERS) {
          RETURN_ERR(GPEGE_ERR_COUNTER);
        }
        counters[ countercount ][ 0 ] = ctr;
        counters[ countercount ][ 1 ] = value;
        ++countercount;
        instrptr += 4;
      }
      break;
    case OP_CONDJUMP:
      {
        uint8_t ctr = ((instr8[0] & 0x0f) << 4) | ((instr8[1] & 0xf0) >> 4);
        uint32_t offset = GPEGU_INSTR_OFFSET(instr8);
        for (unsigned i=countercount; i > 0; i--) {
          if (counters[ i-1 ][ 0 ] == ctr) {
            --(counters[ i-1 ][ 1 ]);
            if (counters[ i-1 ][ 1 ] == 0) {
              if (i == countercount-1) {
                --countercount;
              } else {
                memmove(
                  &(counters[ i-1 ]),
                  &(counters[ i ]),
                  sizeof(unsigned) * 2 * (countercount - i)
                );
              }
              instrptr += 4;
            } else {
              instrptr = offset;
            }
            goto CTRFOUND;
          }
        }
        RETURN_ERR(GPEGE_ERR_CAPREG);
CTRFOUND: ;
      }
      break;
    }
    if (failed) {
      gpege_stackelt_t elt = { 0 };
      CHECK2(stack_fail(&stack, &elt), CLEANUP);
      inputptr = elt.inputptr;
      instrptr = elt.instrptr;
      actions.count = elt.actioncount;
    }
  }
  wrap_captures(input, flags, &actions, &(result->captures));
CLEAN_UP:
  if (stack.list) { free(stack.list); }
  if (actions.list) { free(actions.list); }
  return r;
}
