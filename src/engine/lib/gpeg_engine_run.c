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

#include <andy/uint32list.h>
MAKE_ARRAY_CODE(uint32_t, uint32list_)

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

MAKE_ARRAY_CODE(gpege_stackelt_t, gpege_stack_);
MAKE_ARRAY_CODE(gpege_action_t, gpege_actionlist_);
MAKE_ARRAY_CODE(gpege_capture_t, gpege_caplist_);

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

#ifdef _DEBUG
static
inline int stack_fail
  (gpege_stack_t* stack, gpege_stackelt_t* ret, int debug)
{
  gpege_stackelt_t elt = { 0 };
  if (stack->count == 0) {
    RETURN_ERR(GPEGE_ERR_STACKEMPTY);
  }
  if (debug) {
    fprintf(stderr, "FAIL: ");
  }
  while (stack->count) {
    stack_pop(stack, 0, &elt);
    if (debug) {
      fprintf(stderr, "[%s,%u]"
        , (elt.type == STACK_CATCH ? "ctc" : "cll"), elt.instrptr);
    }
    if (elt.type == STACK_CATCH) {
      if (ret) { *ret = elt; }
      break;
    } else if (debug) {
      fprintf(stderr, ", ");
    }
  }
  if (elt.type == STACK_CATCH && debug) {
    fprintf(stderr, "\n");
  }
  return 0;
}
#else

static
inline int stack_fail
  (gpege_stack_t* stack, gpege_stackelt_t* ret)
{
  gpege_stackelt_t elt = { 0 };
  if (stack->count == 0) {
    RETURN_ERR(GPEGE_ERR_STACKEMPTY);
  }
  while (stack->count) {
    stack_pop(stack, 0, &elt);
    if (elt.type == STACK_CATCH) {
      if (ret) { *ret = elt; }
      break;
    }
  }
  return 0;
}
#endif

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

#ifdef _DEBUG
__attribute__ ((unused))
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
#endif

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
static char readable_buf[ 17 ];
int readable_hex = 0;

static
char* readable_text
  (const vec_t* input, unsigned inputptr)
{
  unsigned o = 0;
  char hex[] = "0123456789abcdef";
  while (o < sizeof(readable_buf)-1 && o + inputptr < input->size) {
    unsigned char c = input->data[ inputptr + o ];
    if (readable_hex) {
      readable_buf[ o++ ] = hex[ c >> 4 ];
      readable_buf[ o++ ] = hex[ c & 0x0f ];
    } else {
      if (c > 32 && c < 127) {
        readable_buf[ o ] = c;
      } else {
        readable_buf[ o ] = '.';
      }
      o++;
    }
  }
  readable_buf[ o ] = 0;
  return readable_buf;
}
#endif

#define CLEANUP { r = __r; goto CLEAN_UP; }

static
unsigned maxinstrctr = GPEGE_MAX_INSTRUCTIONS;

void gpeg_engine_set_maxinstr
  (unsigned m)
{
  maxinstrctr = m;
}

#ifdef _DEBUG
#define DEBUGPOINT_INSTRUCTION \
    if (flags & GPEGE_FLG_DEBUG) { \
      fprintf(stderr, \
        "%.8u: %.8u: %s: %.6u: %.6u: %s: #s=%u\n" \
        , state.instrctr-1 \
        , state.instrptr \
        , instrstr[opcode] \
        , state.inputptr \
        , state.inputsiz \
        , (state.eof ? "EOF" : readable_text(input, state.inputptr)) \
        , state.stack.count \
      ); \
    }
#else
#define DEBUGPOINT_INSTRUCTION { }
#endif

#ifdef _DEBUGGER
#define DEBUGGER_INSTRUCTION \
  { \
    int dontstep = 1; \
    while (dontstep) { \
      gpeg_debug_instruction(&state, &dontstep); \
    } \
  }
#else
#define DEBUGGER_INSTRUCTION { }
#endif

static inline
void gpeg_engine_run_end
  (uint8_t* instr8, gpege_result_t* result, gpege_state_t* state)
{
  result->success = 1;
  result->endcode = (
    (instr8[1]<<16) |
    (instr8[2]<<8) |
    instr8[3]
  );
  state->ended = 1;
}

static inline
void gpeg_engine_run_range
  (uint8_t* instr8, uint8_t* input8, gpege_state_t* state)
{
  unsigned R = instr8[ 0 ] & 0x08;
  unsigned nbits = (instr8[ 0 ] & 0x07) + 1;
  unsigned mask = instr8[ 1 ];
  unsigned from = instr8[ 2 ];
  unsigned until = instr8[ 3 ];
  unsigned chr = 0;

  if (state->inputbit == 0 && nbits == 8) {
    chr = *input8;
  } else if (state->inputbit + nbits <= 8) {
    chr = (input8[ 8 ] >> state->inputbit) & ((1 << nbits) - 1);
  } else {
    abort();
  }
  if (state->eof) {
    state->failed = 1;
  } else if (R) {
//fprintf(stderr, "TRUE RANGE: matching %.2x <= %.2x & %.2x <= %.2x\n", from, chr, mask, until);
    if ((chr & mask) < from || (chr & mask) > until) {
      state->failed = 1;
    } else {
      state->instrptr += 4;
      state->inputbit += nbits;
      if (state->inputbit >= 8) {
        state->inputptr++;
        state->inputbit -= 8;
      }
    }
  } else {
//fprintf(stderr, "Match %.2x & %.2x == %.2x\n", chr, mask, from);
    if ((chr & mask) == from || (chr & mask) == until) {
      state->instrptr += 4;
      state->inputbit += nbits;
      if (state->inputbit >= 8) {
        state->inputptr++;
        state->inputbit -= 8;
      }
    } else {
      state->failed = 1;
    }
  }
}

static inline
int gpeg_engine_run_limit
  (uint8_t* instr8, const vec_t* input, gpege_state_t* state)
{
  unsigned O   = ((instr8[1]>>6)&0x01);
  unsigned E   = ((instr8[1]>>5)&0x01);
  unsigned S   =  (instr8[1]&0x1f) + 1;
  unsigned reg = ((instr8[2]<<8)|(instr8[3]));

  if (O) {
    uint32_t len = 0;
    vec_t value = { 0 };
    CHECK(
      resolve_variable(
        input,
        &(state->actions),
        reg,
        state->stack.count,
        &value
      )
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
    len += state->inputptr;
    if (len > input->size) {
      DBGMSG("Limit: length %u + %u > %u\n"
             , len-state->inputptr
             , state->inputptr
             , input->size);
      RETURN_ERR(GPEGE_ERR_LIMIT);
    }
    uint32list_push(&(state->inputsizes), len);
    state->inputsiz = len;
  } else {
    uint32list_pop(&(state->inputsizes), 0);
  }
  state->instrptr += 4;
  return 0;
}

static inline
void gpeg_engine_run_call
  (uint8_t* instr8, gpege_state_t* state)
{
  gpege_stackelt_t elt = {
    .type = STACK_CALL,
    .instrptr= state->instrptr + 4,
    .inputptr = state->inputptr,
    .actioncount = state->actions.count,
    .countercount = state->countercount,
    .inputsizescount = state->inputsizes.count,
  };
  gpege_stack_push(&(state->stack), elt);
  state->instrptr = GPEGU_INSTR_OFFSET(instr8);
}

static inline
int gpeg_engine_run_ret
  (const vec_t* input, gpege_state_t* state)
{
  gpege_stackelt_t elt = { 0 };
  CHECK(stack_pop(&(state->stack), STACK_CALL, &elt));
  state->instrptr = elt.instrptr;
  state->inputsizes.count = elt.inputsizescount;
  state->inputsiz = (state->inputsizes.count ?
                     state->inputsizes.list[ state->inputsizes.count-1 ] :
                     input->size);
  return 0;
}

static inline
void gpeg_engine_run_catch
  (uint8_t* instr8, gpege_state_t* state)
{
  gpege_stackelt_t elt = {
    .type = STACK_CATCH,
    .instrptr = GPEGU_INSTR_OFFSET(instr8),
    .inputptr = state->inputptr,
    .actioncount = state->actions.count,
    .countercount = state->countercount,
    .inputsizescount = state->inputsizes.count,
  };
  gpege_stack_push(&(state->stack), elt);
  state->instrptr += 4;
}

static inline
int gpeg_engine_run_backcommit
  (uint8_t* instr8, const vec_t* input, gpege_state_t* state)
{
  gpege_stackelt_t elt = { 0 };
  CHECK(stack_pop(&(state->stack), 0, &elt));
  state->inputptr = elt.inputptr;
  //state->actions.count = elt.actioncount;
  state->countercount = elt.countercount;
  state->inputsizes.count = elt.inputsizescount;
  state->inputsiz = (state->inputsizes.count ?
                     state->inputsizes.list[ state->inputsizes.count-1 ] :
                     input->size);
  state->instrptr = GPEGU_INSTR_OFFSET(instr8);
  return 0;
}

static inline
int gpeg_engine_run_partialcommit
  (uint8_t* instr8, gpege_state_t* state)
{
  gpege_stackelt_t* eltptr = NULL;
  CHECK(stack_peek(&(state->stack), &eltptr));
  eltptr->inputptr = state->inputptr;
  eltptr->actioncount = state->actions.count;
  eltptr->countercount = state->countercount;
  eltptr->inputsizescount = state->inputsizes.count;
  state->instrptr = GPEGU_INSTR_OFFSET(instr8);
  return 0;
}

static inline
int gpeg_engine_run_failtwice
  (gpege_state_t* state, unsigned flags)
{
  (void)flags;
#ifdef _DEBUG
  CHECK(stack_fail(&(state->stack), NULL, flags & GPEGE_FLG_DEBUG));
#else
  CHECK(stack_fail(&(state->stack), NULL));
#endif
  state->failed = 1;
  return 0;
}

static inline
int gpeg_engine_run_var
  (uint8_t* instr8, uint8_t* input8, const vec_t* input, gpege_state_t* state)
{
  uint16_t reg = (instr8[2] << 8) | instr8[3];
  vec_t value = { 0 };
  CHECK(
    resolve_variable(input, &(state->actions), reg, state->stack.count, &value)
  );
  if (value.size == 0) {
    state->failed = 1;
  } else if (state->inputptr + value.size > input->size) {
    state->failed = 1;
  } else if (state->eof) {
    state->failed = 1;
  } else if (0 != memcmp(input8, value.data, value.size)) {
    state->failed = 1;
  } else {
    state->inputptr += value.size;
    state->instrptr += 4;
  }
  return 0;
}

static inline
void gpeg_engine_run_opencapture
  (uint8_t* instr8, gpege_state_t* state)
{
  uint16_t reg = (instr8[2] << 8) | instr8[3];
  gpege_action_t action = {
    .action   = ACT_OPEN,
    .reg      = reg,
    .offset   = state->inputptr,
    .stacklen = state->stack.count,
  };
  gpege_actionlist_push(&state->actions, action);
  state->instrptr += 4;
}

static inline
void gpeg_engine_run_closecapture
  (uint8_t* instr8, gpege_state_t* state)
{
  uint16_t reg = (instr8[2] << 8) | instr8[3];
  gpege_action_t action = {
    .action   = ACT_CLOSE,
    .reg      = reg,
    .offset   = state->inputptr,
    .stacklen = state->stack.count,
  };
  gpege_actionlist_push(&state->actions, action);
  state->instrptr += 4;
}

static inline
int gpeg_engine_run_counter
  (uint8_t* instr8, gpege_state_t* state)
{
  uint8_t ctr = ((instr8[0] & 0x0f) << 4) | ((instr8[1] & 0xf0) >> 4);
  uint32_t value = GPEGU_INSTR_OFFSET(instr8);
  if (state->countercount >= GPEGE_MAX_COUNTERS) {
    RETURN_ERR(GPEGE_ERR_MAXCOUNTER);
  }
  state->counters[ state->countercount ][ 0 ] = ctr;
  state->counters[ state->countercount ][ 1 ] = value;
  ++state->countercount;
  state->instrptr += 4;
  return 0;
}

static inline
int gpeg_engine_run_condjump
  (uint8_t* instr8, gpege_state_t* state)
{
  uint8_t ctr = ((instr8[0] & 0x0f) << 4) | ((instr8[1] & 0xf0) >> 4);
  uint32_t offset = GPEGU_INSTR_OFFSET(instr8);
  for (unsigned i=state->countercount; i > 0; i--) {
    if (state->counters[ i-1 ][ 0 ] == ctr) {
      --(state->counters[ i-1 ][ 1 ]);
      if (state->counters[ i-1 ][ 1 ] == 0) {
        if (i == state->countercount-1) {
          --state->countercount;
        } else {
          memmove(
            &(state->counters[ i-1 ]),
            &(state->counters[ i ]),
            sizeof(unsigned) * 2 * (state->countercount - i)
          );
          --state->countercount;
        }
        state->instrptr += 4;
      } else {
        state->instrptr = offset;
      }
      goto CTRFOUND;
    }
  }
  RETURN_ERR(GPEGE_ERR_COUNTER);
CTRFOUND: ;
  return 0;
}

static inline
int gpeg_engine_fail
  (const vec_t* input, gpege_state_t* state, unsigned flags)
{
  gpege_stackelt_t elt = { 0 };
  (void)flags;
#ifdef _DEBUG
  CHECK(stack_fail(&(state->stack), &elt, flags & GPEGE_FLG_DEBUG));
#else
  CHECK(stack_fail(&(state->stack), &elt));
#endif
  state->inputptr = elt.inputptr;
  state->instrptr = elt.instrptr;
  state->actions.count = elt.actioncount;
  state->countercount = elt.countercount;
  state->inputsizes.count = elt.inputsizescount;
  state->inputsiz = (state->inputsizes.count ?
                    state->inputsizes.list[ state->inputsizes.count-1 ] :
                    input->size);
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
    unsigned flags,
    gpege_result_t* result
  )
{
  DEBUGFUNCTION
  ASSERT(bytecode)
  ASSERT(input)
  ASSERT(result)

  uint8_t* instr8 = 0;
  uint8_t* input8 = 0;
  uint8_t opcode = 0;
  int r = 0;
  gpege_state_t state = { 0 };

  state.bytecode = bytecode;
  state.input = input;
  state.inputsiz = input->size;
  result->flags = flags;

  (void)instrstr;

#ifdef _DEBUG
  if (flags & GPEGE_FLG_DEBUGHEX) { readable_hex = 1; }
#endif

  while (!state.ended && !(state.failed && state.stack.count == 0)) {
    if (maxinstrctr && ++state.instrctr > maxinstrctr) {
      RETURN_ERR2(GPEGE_ERR_MAXINSTR, CLEANUP);
    }
    state.failed = 0;
    if (state.instrptr >= bytecode->size + 4) {
      RETURN_ERR2(GPEGE_ERR_OVERFLOW, CLEANUP);
    }
    instr8 = bytecode->data + state.instrptr;
    opcode = instr8[0] >> 4;
    if (state.inputptr >= state.inputsiz) {
      state.eof = 1;
    } else {
      state.eof = 0;
      input8 = input->data + state.inputptr;
    }
    if (state.inputptr > result->maxinputptr) {
      result->maxinputptr = state.inputptr;
    }

DEBUGPOINT_INSTRUCTION
DEBUGGER_INSTRUCTION

    switch (opcode) {
    case OP_END:
      gpeg_engine_run_end(instr8, result, &state);
      break;
    case OP_RANGE:
      gpeg_engine_run_range(instr8, input8, &state);
      break;
    case OP_LIMIT:
      CHECK2(gpeg_engine_run_limit(instr8, input, &state), CLEANUP);
      break;
    case OP_CALL:
      gpeg_engine_run_call(instr8, &state);
      break;
    case OP_RET:
      CHECK2(gpeg_engine_run_ret(input, &state), CLEANUP);
      break;
    case OP_CATCH:
      gpeg_engine_run_catch(instr8, &state);
      break;
    case OP_COMMIT:
      CHECK2(stack_pop(&(state.stack), STACK_CATCH, NULL), CLEANUP);
      state.instrptr = GPEGU_INSTR_OFFSET(instr8);
      break;
    case OP_BACKCOMMIT:
      CHECK2(gpeg_engine_run_backcommit(instr8, input, &state), CLEANUP);
      break;
    case OP_PARTIALCOMMIT:
      CHECK2(gpeg_engine_run_partialcommit(instr8, &state), CLEANUP);
      break;
    case OP_FAIL:
      state.failed = 1;
      break;
    case OP_FAILTWICE:
      CHECK2(gpeg_engine_run_failtwice(&state, flags), CLEANUP);
      break;
    case OP_VAR:
      CHECK2(gpeg_engine_run_var(instr8, input8, input, &state), CLEANUP);
      break;
    case OP_OPENCAPTURE:
      gpeg_engine_run_opencapture(instr8, &state);
      break;
    case OP_CLOSECAPTURE:
      gpeg_engine_run_closecapture(instr8, &state);
      break;
    case OP_COUNTER:
      CHECK2(gpeg_engine_run_counter(instr8, &state), CLEANUP);
      break;
    case OP_CONDJUMP:
      CHECK2(gpeg_engine_run_condjump(instr8, &state), CLEANUP);
      break;
    }

    if (state.failed) {
      CHECK2(gpeg_engine_fail(input, &state, flags), CLEANUP);
    }
  }

  wrap_captures(input, flags, &state.actions, &(result->captures));
CLEAN_UP:
  if (state.stack.list) { free(state.stack.list); }
  if (state.actions.list) { free(state.actions.list); }
  return r;
}
