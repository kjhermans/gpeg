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

#include <gpeg/engine/release.h>

struct compilestate
{
  unsigned      flags;
  unsigned      label;
  unsigned      counter;
  unsigned      capture;
  int           prefixset;
  int           firstrule;
  vec_t*        assembly;
  vec_t*        error;
  FILE*         slotmap;
  const char*   rulename;
  unsigned      rulecapture;
  str2int_map_t variables;
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
    if (!(state->firstrule)) {
      state->firstrule = 1;
      vec_printf(state->assembly,
        "-- GPEG compiler, release %-.*s\n"
        "  call %s\n"
        "  end 0\n"
        "\n"
        , release_len
        , release
        , rulename
      );
    }
    vec_printf(state->assembly, "%s:\n", rulename);
    if (state->prefixset) {
      vec_printf(state->assembly, "  call __prefix\n");
    }
    if (0 == strcmp(rulename, "__prefix")) {
      state->prefixset = 1;
    } else if (state->flags & GPEGC_FLG_AUTOCAPTURE) {
      unsigned capture = ++(state->capture);
      vec_append(vec, &capture, sizeof(capture));
      vec_printf(state->assembly, "  opencapture %u\n", capture);
      if (state->slotmap) {
        fprintf(state->slotmap, "#define SLOT_%s %u\n", rulename, capture);
      }
    }
    state->rulename = rulename;
    state->rulecapture = 0;
    state->variables.count = 0;
    break;
  case GPEG_FNC_POSTNODE:
    if (state->flags & GPEGC_FLG_AUTOCAPTURE) {
      unsigned* capture = (unsigned*)(vec->data);
      if (capture) {
        vec_printf(state->assembly, "  closecapture %u\n", *capture);
      }
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
  (gpege_node_t* node, unsigned phase, unsigned _i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  vec_t* string = &(node->children[ 0 ]->children[ 0 ]->vec);
  (void)_i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    for (unsigned i=0; i < string->size; i++) {
      unsigned char c = string->data[ i ];
      switch (c) {
      case '\\':
        if (i < string->size-1) {
          ++i;
          switch (c = string->data[ i ]) {
          case 'n':
            vec_printf(state->assembly, "  range 0a\n");
            break;
          case 'r':
            vec_printf(state->assembly, "  range 0d\n");
            break;
          case 't':
            vec_printf(state->assembly, "  range 09\n");
            break;
          case 'v':
            vec_printf(state->assembly, "  range 0b\n");
            break;
          case 'x':
            if (i < string->size-2) {
              vec_printf(state->assembly,
                "  range %-.*s\n", 2, &(string->data[ i + 1 ]));
            }
            i += 2;
            break;
          default:
            vec_printf(state->assembly, "  range %.2x\n", c);
          }
        } else {
          if (state->error) {
            vec_printf(state->error,
              "Error in escape sequence: backslash before end.\n"
            );
          }
          RETURN_ERR(GPEGC_ERR_ESCAPE);
        }
        break;
      default:
        vec_printf(state->assembly, "  range %.2x\n", c);
      }
    }
  }
  return 0;
}

static
void gpeg_compile_q_01_pre
  (struct compilestate* state, vec_t* vec)
{
  unsigned label = (state->label)++;
  vec_append(vec, &label, sizeof(label));
  vec_printf(state->assembly,
    "  catch L%u\n"
    , label
  );
}

static
void gpeg_compile_q_01_post
  (struct compilestate* state, vec_t* vec)
{
  unsigned* label = (unsigned*)(vec->data);
  vec_printf(state->assembly,
    "  commit __NEXT__\n"
    "L%u:\n"
    , *label
  );
}

static
void gpeg_compile_q_0p_pre
  (struct compilestate* state, vec_t* vec)
{
  unsigned label = (state->label)++;
  vec_append(vec, &label, sizeof(label));
  vec_printf(state->assembly,
    "  catch L%u\n"
    "LOOP%u:\n"
    , label
    , label
  );
}

static
void gpeg_compile_q_0p_post
  (struct compilestate* state, vec_t* vec)
{
  unsigned* label = (unsigned*)(vec->data);
  vec_printf(state->assembly,
    "  partialcommit LOOP%u\n"
    "L%u:\n"
    , *label
    , *label
  );
}

static
int gpeg_compile_q_1p_pre
  (gpege_node_t* node, struct compilestate* state, vec_t* vec)
{
  unsigned label = (state->label)++;

  vec_append(vec, &label, sizeof(label));
  CHECK(gpeg_result_run(node->children[ 0 ]));
  vec_printf(state->assembly,
    "  catch L%u\n"
    "LOOP%u:\n"
    , label
    , label
  );
  return 0;
}

static
void gpeg_compile_q_1p_post
  (struct compilestate* state, vec_t* vec)
{
  unsigned* label = (unsigned*)(vec->data);

  vec_printf(state->assembly,
    "  partialcommit LOOP%u\n"
    "L%u:\n"
    , *label
    , *label
  );
}

static
int gpeg_compile_q_ft_pre
  (
    gpege_node_t* node,
    struct compilestate* state,
    vec_t* vec,
    vec_t* fromstr,
    vec_t* untilstr
  )
{
  unsigned label = (state->label)++;
  unsigned counter0 = (state->counter)++;
  unsigned counter1 = (state->counter)++;
  unsigned from = atoi((char*)(fromstr->data));
  unsigned until = atoi((char*)(untilstr->data));

  if (until == 0 || until < from) {
    if (state->error) {
      vec_printf(state->error,
        "Error in range; until zero or until smaller than from (have %u-%u).\n"
        , from
        , until
      );
    }
    RETURN_ERR(GPEGC_ERR_RANGE);
  }
  vec_append(vec, &label, sizeof(label));
  vec_append(vec, &counter1, sizeof(counter1));
  switch (from) {
  case 0:
    break;
  case 1:
    CHECK(gpeg_result_run(node->children[ 0 ]));
    break;
  default:
    {
      vec_printf(state->assembly,
        "  counter %u %u\n"
        "CTR%u:\n"
        , counter0
        , from
        , counter0
      );
      CHECK(gpeg_result_run(node->children[ 0 ]));
      vec_printf(state->assembly,
        "  condjump %u CTR%u\n"
        , counter0
        , counter0
      );
    }
    break;
  }
  vec_printf(state->assembly,
    "  catch L%u\n"
    "  counter %u %u\n"
    "CTR%u:\n"
    , label
    , counter1
    , until - from
    , counter1
  );
  return 0;
}

static
void gpeg_compile_q_ft_post
  (
    struct compilestate* state,
    vec_t* vec
  )
{
  unsigned* label = (unsigned*)(vec->data);
  unsigned counter1 = label[ 1 ];

  vec_printf(state->assembly,
    "  partialcommit __NEXT__\n"
    "  condjump %u CTR%u\n"
    "  commit __NEXT__\n"
    "L%u:\n"
    , counter1
    , counter1
    , *label
  );
}

static
int gpeg_compile_q_fr_pre
  (
    gpege_node_t* node,
    struct compilestate* state,
    vec_t* vec,
    vec_t* fromstr
  )
{
  unsigned label = (state->label)++;
  unsigned counter = (state->counter)++;
  unsigned from = atoi((char*)(fromstr->data));

  vec_append(vec, &label, sizeof(label));
  if (from) {
    vec_printf(state->assembly,
      "  counter %u %u\n"
      "CTR%u:\n"
      , counter
      , from
      , counter
    );
    CHECK(gpeg_result_run(node->children[ 0 ]));
    vec_printf(state->assembly,
      "  condjump %u CTR%u\n"
      , counter
      , counter
    );
  }
  vec_printf(state->assembly,
    "  catch L%u\n"
    "LOOP%u:\n"
    , label
    , label
  );
  return 0;
}

static
void gpeg_compile_q_fr_post
  (
    struct compilestate* state,
    vec_t* vec
  )
{
  unsigned* label = (unsigned*)(vec->data);
  vec_printf(state->assembly,
    "  partialcommit LOOP%u\n"
    "L%u:\n"
    , *label
    , *label
  );
}

static
int gpeg_compile_q_un_pre
  (struct compilestate* state, vec_t* vec, vec_t* n)
{
  unsigned counter = (state->counter)++;
  unsigned label = (state->label)++;
  unsigned until = atoi((char*)(n->data));

  if (until == 0) {
    if (state->error) {
      vec_printf(state->error,
        "Error in range; until zero.\n"
      );
    }
    RETURN_ERR(GPEGC_ERR_RANGE);
  }
  vec_append(vec, &label, sizeof(label));
  vec_append(vec, &counter, sizeof(counter));
  vec_printf(state->assembly,
    "  catch L%u\n"
    "  counter %u %u\n"
    "CTR%u:\n"
    , label
    , counter
    , until
    , counter
  );
  return 0;
}

static
void gpeg_compile_q_un_post
  (struct compilestate* state, vec_t* vec)
{
  unsigned* label = (unsigned*)(vec->data);
  unsigned counter = label[ 1 ];

  vec_printf(state->assembly,
    "  partialcommit __NEXT__\n"
    "  condjump %u CTR%u\n"
    "  commit __NEXT__\n"
    "L%u:\n"
    , counter
    , counter
    , *label
  );
}

static
void gpeg_compile_q_sp_pre
  (struct compilestate* state, vec_t* vec, vec_t* n)
{
  unsigned counter = (state->counter)++;
  vec_append(vec, &counter, sizeof(counter));
  vec_printf(state->assembly,
    "  counter %u %s\n"
    "CTR%u:\n"
    , counter
    , (char*)(n->data)
    , counter
  );
}

static
void gpeg_compile_q_sp_post
  (struct compilestate* state, vec_t* vec)
{
  unsigned* counter = (unsigned*)(vec->data);
  vec_printf(state->assembly,
    "  condjump %u CTR%u\n"
    , *counter
    , *counter
  );
}

static
int gpeg_compile_q
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)i;

  if (node->nchildren == 2) {
    switch (phase) {
    case GPEG_FNC_PRENODE:
      switch (node->children[ 1 ]->children[ 0 ]->type) {
      case SLOT_Q_ZEROORONE:
        gpeg_compile_q_01_pre(state, vec);
        break;
      case SLOT_Q_ONEORMORE:
        CHECK(gpeg_compile_q_1p_pre(node, state, vec));
        break;
      case SLOT_Q_ZEROORMORE:
        gpeg_compile_q_0p_pre(state, vec);
        break;
      case SLOT_Q_FROMTO:
        CHECK(
          gpeg_compile_q_ft_pre(
            node,
            state,
            vec,
            &(node->children[ 1 ]->children[ 0 ]->children[ 0 ]->vec),
            &(node->children[ 1 ]->children[ 0 ]->children[ 1 ]->vec)
          )
        );
        break;
      case SLOT_Q_UNTIL:
        CHECK(
          gpeg_compile_q_un_pre(
            state,
            vec,
            &(node->children[ 1 ]->children[ 0 ]->children[ 0 ]->vec)
          )
        );
        break;
      case SLOT_Q_FROM:
        CHECK(
          gpeg_compile_q_fr_pre(
            node,
            state,
            vec,
            &(node->children[ 1 ]->children[ 0 ]->children[ 0 ]->vec)
          )
        );
        break;
      case SLOT_Q_SPECIFIC:
        gpeg_compile_q_sp_pre(
          state,
          vec,
          &(node->children[ 1 ]->children[ 0 ]->children[ 0 ]->vec)
        );
        break;
      }
      break;
    case GPEG_FNC_POSTNODE:
      switch (node->children[ 1 ]->children[ 0 ]->type) {
      case SLOT_Q_ZEROORONE:
        gpeg_compile_q_01_post(state, vec);
        break;
      case SLOT_Q_ONEORMORE:
        gpeg_compile_q_1p_post(state, vec);
        break;
      case SLOT_Q_ZEROORMORE:
        gpeg_compile_q_0p_post(state, vec);
        break;
      case SLOT_Q_FROMTO:
        gpeg_compile_q_ft_post(state, vec);
        break;
      case SLOT_Q_UNTIL:
        gpeg_compile_q_un_post(state, vec);
        break;
      case SLOT_Q_FROM:
        gpeg_compile_q_fr_post(
          state,
          vec
        );
        break;
      case SLOT_Q_SPECIFIC:
        gpeg_compile_q_sp_post(state, vec);
        break;
      }
      break;
    }
  }
  return 0;
}

static
int gpeg_compile_notand
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)i;

  switch (phase) {
  case GPEG_FNC_PRENODE:
    {
      unsigned label = (state->label)++;
      vec_append(vec, &label, sizeof(label));
      vec_printf(state->assembly,
        "  catch L%u\n"
        , label
      );
    }
    break;
  case GPEG_FNC_POSTNODE:
    if (node->children[ 0 ]->type == SLOT_NOT) {
      unsigned* label = (unsigned*)(vec->data);
      vec_printf(state->assembly,
        "  failtwice\n"
        "L%u:\n"
        , *label
      );
    } else if (node->children[ 0 ]->type == SLOT_AND) {
      unsigned* label = (unsigned*)(vec->data);
      vec_printf(state->assembly,
        "  backcommit OUT%u\n"
        "L%u:\n"
        "  fail\n"
        "OUT%u:\n"
        , *label
        , *label
        , *label
      );
    }
    break;
  }
  return 0;
}

static
int gpeg_compile_any
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    vec_printf(state->assembly,
      "  range 00 ff\n"
    );
  }
  return 0;
}

static
uint8_t dehex
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
uint8_t range_unescape
  (char* str)
{
  if (strlen(str) == 1) {
    return *str;
  } else if (*str == '\\') {
    switch (str[ 1 ]) {
    case 'n': return 0x0a;
    case 'r': return 0x0d;
    case 't': return 0x09;
    case 'v': return 0x0b;
    case 'x': return dehex(&(str[2]));
    default: return str[1];
    }
  } else {
    return 0;
  }
}

static inline
void setbit
  (uint8_t* bits, unsigned bit)
{
  bits[ bit / 8 ] |= (1 << (bit % 8));
}

static inline
void unsetbit
  (uint8_t* bits, unsigned bit)
{
  bits[ bit / 8 ] &= ~(1 << (bit % 8));
}

static inline
int bitset
  (uint8_t* bits, unsigned bit)
{
  return (bits[ bit / 8 ] & (1 << (bit % 8))) ? 1 : 0;
}

static
int gpeg_compile_ranges
  (gpege_node_t* node, struct compilestate* state, int negative)
{
  uint8_t bits[ 32 ];
  unsigned label = (state->label)++;

  if (negative) {
    memset(bits, 0xff, sizeof(bits));
  } else {
    memset(bits, 0x00, sizeof(bits));
  }
  for (unsigned i=0; i < node->nchildren; i++) {
    gpege_node_t* child = node->children[ i ];
    switch (child->type) {
    case SLOT_SET_1:
      {
        gpege_node_t* child1 = node->children[ ++i ];
        unsigned char from = range_unescape((char*)(child->vec.data));
        unsigned char until = range_unescape((char*)(child1->vec.data));
        for (unsigned j=from; j <= until; j++) {
          if (negative) {
            unsetbit(bits, j);
          } else {
            setbit(bits, j);
          }
        }
      }
      break;
    case SLOT_SET_3:
      {
        unsigned char chr = range_unescape((char*)(child->vec.data));
        if (negative) {
          unsetbit(bits, chr);
        } else {
          setbit(bits, chr);
        }
      }
      break;
    }
  }
  int on = 0;
  int seenbits = 0;
  uint8_t range[ 2 ] = { 0, 0 };
  unsigned rangecount = 0;
  for (unsigned i=0; i < 256; i++) {
    if (bitset(bits, i) && !on) {
      seenbits = 1;
      if (range[ 1 ]) {
        vec_printf(state->assembly,
          "  catch SET%u_%u\n"
          "  range %.2x %.2x\n"
          "  commit L%u\n"
          "SET%u_%u:\n"
          , label
          , rangecount
          , range[ 0 ]
          , range[ 1 ]
          , label
          , label
          , rangecount
        );
        ++rangecount;
      }
      on = 1;
      range[ 0 ] = i;
      range[ 1 ] = 0;
    } else if (!bitset(bits, i) && on) {
      on = 0;
      range[ 1 ] = i-1;
    }
  }
  if (!seenbits) {
    if (state->error) {
      vec_printf(state->error,
        "Error in set; empty.\n"
      );
    }
    RETURN_ERR(GPEGC_ERR_SET);
  }
  if (!range[ 1 ]) {
    range[ 1 ] = 255;
  }
  vec_printf(state->assembly,
    "  range %.2x %.2x\n"
    "L%u:\n"
    , range[ 0 ]
    , range[ 1 ]
    , label
  );
  return 0;
}

static
int gpeg_compile_set
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    if (node->children[ 1 ]->type == SLOT_SET_0) {
      CHECK(gpeg_compile_ranges(node, state, 1));
    } else {
      CHECK(gpeg_compile_ranges(node, state, 0));
    }
  }
  return 0;
}

static
int gpeg_compile_macro
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  unsigned label;
  (void)node;
  (void)i;
  (void)vec;

  if (phase == GPEG_FNC_PRENODE) {
    label = (state->label)++;
    if (0 == strcmp((char*)(node->vec.data), "%s")) {
      vec_printf(state->assembly,
        "  catch MACRO%u_1\n"
        "  range 09 0b\n"
        "  commit L%u\n"
        "MACRO%u_1:\n"
        "  catch MACRO%u_2\n"
        "  range 0d\n"
        "  commit L%u\n"
        "MACRO%u_2:\n"
        "  range 20\n"
        "L%u:\n"
        , label
        , label
        , label
        , label
        , label
        , label
        , label
        /*
        "  catch MACRO%u_1\n"
        "  range 20\n"
        "  commit L%u\n"
        "MACRO%u_1:\n"
        "  range 07 0d\n"
        "L%u:\n"
        , label
        , label
        , label
        , label
        */
      );
    } else if (0 == strcmp((char*)(node->vec.data), "%w")) {
      vec_printf(state->assembly,
        "  catch MACRO%u_1\n"
        "  range 41 5a\n"
        "  commit L%u\n"
        "MACRO%u_1:\n"
        "  range 61 7a\n"
        "L%u:\n"
        , label
        , label
        , label
        , label
      );
    } else if (0 == strcmp((char*)(node->vec.data), "%a")) {
      vec_printf(state->assembly,
        "  catch MACRO%u_1\n"
        "  range 41 5a\n"
        "  commit L%u\n"
        "MACRO%u_1:\n"
        "  catch MACRO%u_2\n"
        "  range 61 7a\n"
        "  commit L%u\n"
        "MACRO%u_2:\n"
        "  range 30 39\n"
        "L%u:\n"
        , label
        , label
        , label
        , label
        , label
        , label
        , label
      );
    } else if (0 == strcmp((char*)(node->vec.data), "%n")) {
      vec_printf(state->assembly,
        "  range 30 39\n"
      );
    } else if (0 == strcmp((char*)(node->vec.data), "%p")) {
      vec_printf(state->assembly,
        "  catch MACRO%u_1\n"
        "  range 20 7e\n"
        "  commit L%u\n"
        "MACRO%u_1:\n"
        "  catch MACRO%u_2\n"
        "  range 0a\n"
        "  commit L%u\n"
        "MACRO%u_2:\n"
        "  range 0c\n"
        "L%u:\n"
        , label
        , label
        , label
        , label
        , label
        , label
        , label
      );
    } else if (0 == strcmp((char*)(node->vec.data), "%n")) {
      vec_printf(state->assembly,
        "  range 30 39\n"
      );
    } else {
      if (state->error) {
        vec_printf(state->error,
          "Error in macro; unknown macro.\n"
        );
      }
      RETURN_ERR(GPEGC_ERR_MACRO);
    }
  }
  return 0;
}

static
int gpeg_compile_capture
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)node;
  (void)i;

  switch (phase) {
  case GPEG_FNC_PRENODE:
    {
      unsigned capture;
      memcpy(&capture, node->aux, sizeof(capture));
      if (capture == 0) {
        capture = ++(state->capture);
        memcpy(node->aux, &capture, sizeof(capture));
      }
      vec_append(vec, &capture, sizeof(capture));
      vec_printf(state->assembly,
        "  opencapture %u\n"
        , capture
      );
      if (state->slotmap) {
        fprintf(state->slotmap,
          "#define SLOT_%s_%u %u\n"
          , state->rulename
          , (state->rulecapture)++
          , capture
        );
      }
    }
    break;
  case GPEG_FNC_POSTNODE:
    {
      unsigned* capture = (unsigned*)(vec->data);
      vec_printf(state->assembly,
        "  closecapture %u\n"
        , *capture
      );
    }
    break;
  }
  return 0;
}

static
int gpeg_compile_varcapture
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)node;
  (void)i;

  switch (phase) {
  case GPEG_FNC_PRENODE:
    {
      char* variablename = (char*)(node->children[ 2 ]->vec.data);
      unsigned capture;
      memcpy(&capture, node->aux, sizeof(capture));
      if (capture == 0) {
        capture = ++(state->capture);
        memcpy(node->aux, &capture, sizeof(capture));
      }
      str2int_map_put(&(state->variables), variablename, capture);
      vec_append(vec, &capture, sizeof(capture));
      vec_printf(state->assembly,
        "  opencapture %u\n"
        , capture
      );
      if (state->slotmap) {
        fprintf(state->slotmap,
          "#define SLOT_%s_%u %u\n"
          , state->rulename
          , (state->rulecapture)++
          , capture
        );
      }
    }
    break;
  case GPEG_FNC_POSTNODE:
    {
      unsigned* capture = (unsigned*)(vec->data);
      vec_printf(state->assembly,
        "  closecapture %u\n"
        , *capture
      );
    }
    break;
  }
  return 0;
}

static
int gpeg_compile_varref
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  switch (phase) {
  case GPEG_FNC_PRENODE:
    {
      char* variablename = (char*)(node->children[ 0 ]->vec.data);
      unsigned capture = 0;
      if (strcmp(variablename, "_")) {
        if (str2int_map_get(&(state->variables), variablename, &capture)) {
          if (state->error) {
            vec_printf(state->error,
              "Error in variable reference; unknown identifier.\n"
            );
          }
          RETURN_ERR(GPEGC_ERR_VARIABLE);
        }
      }
      vec_printf(state->assembly,
        "  var %u\n"
        , capture
      );
    }
    break;
  }
  return 0;
}

static
int gpeg_compile_hex
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  switch (phase) {
  case GPEG_FNC_PRENODE:
    {
      vec_printf(state->assembly,
        "  range %s\n"
        , (char*)(&(node->vec.data[ 2 ]))
      );
    }
    break;
  }
  return 0;
}

static
int gpeg_compile_endforce
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)node;
  (void)i;
  (void)vec;

  switch (phase) {
  case GPEG_FNC_PRENODE:
    {
      vec_printf(state->assembly,
        "  end %s\n"
        , (char*)(node->children[ 0 ]->vec.data)
      );
    }
    break;
  }
  return 0;
}

static
int gpeg_compile_bitmask
  (gpege_node_t* node, unsigned phase, unsigned _i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  (void)node;
  (void)_i;
  (void)vec;

  switch (phase) {
  case GPEG_FNC_PRENODE:
    {
      uint8_t target = 0, mask = 0;
      for (unsigned i=0; i < 8; i++) {
        switch (node->vec.data[ i+1 ]) {
        case '0':
          mask |= (1<<(7-i));
          break;
        case '1':
          target |= (1<<(7-i));
          mask |= (1<<(7-i));
          break;
        case '_':
          break;
        }
      }
      vec_printf(state->assembly,
        "  range %.2x %.2x %.2x\n"
        , target
        , target
        , mask
      );
    }
    break;
  }
  return 0;
}

static
int gpeg_compile_lim
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  struct compilestate* state = arg;
  char* variablename = (char*)(node->children[ 0 ]->vec.data);
  unsigned endian = atoi((char*)(node->children[ 2 ]->vec.data));
  unsigned bitlength = atoi((char*)(node->children[ 4 ]->vec.data));
  char* function = (char*)(node->children[ 6 ]->vec.data);
  unsigned capture = 0;

  (void)node;
  (void)i;
  (void)vec;

  if (bitlength > 32) {
    if (state->error) {
      vec_printf(state->error,
        "Error in limit; bitlength > 32.\n"
      );
    }
    RETURN_ERR(GPEGC_ERR_BITLENGTH);
  }
  if (strcmp(variablename, "_")) {
    if (str2int_map_get(&(state->variables), variablename, &capture)) {
    if (state->error) {
      vec_printf(state->error,
        "Error in limit; variable reference not found.\n"
      );
    }
      RETURN_ERR(GPEGC_ERR_VARIABLE);
    }
  }
  switch (phase) {
  case GPEG_FNC_PRENODE:
    {
      vec_printf(state->assembly,
        "  limit %u %u %u\n"
        "  call %s\n"
        , (endian ? 1 : 0)
        , bitlength
        , capture
        , function
      );
    }
    break;
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
    unsigned flags,
    FILE* slotmap,
    vec_t* error
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
    .error = error,
    .slotmap = slotmap,
  };
  int e;

  if ((e = gpeg_engine_run(&bytecode, grammar, 0, &result)) != 0) {
    if (error) {
      char* errs[] = GPEGE_ERR_STRINGS;
      vec_printf(error,
        "Compiler parser engine ended in error; %s.\n", errs[ e ]
      );
    }
    RETURN_ERR(GPEGC_ERR_PARSER);
  } else if (!(result.success)) {
    if (error) {
      unsigned yx[ 2 ] = { 0 };
      e = strxypos((char*)(grammar->data), result.maxinputptr, yx);
      vec_printf(error,
        "Compiler parser engine ended in no match;\n"
        "Furthest input position reached: %u, which is line %u, character %u.\n"
        , result.maxinputptr
        , yx[ 0 ]
        , yx[ 1 ]
      );
    }
    RETURN_ERR(GPEGC_ERR_PARSER);
  }

  gpege_node_t* tree = gpeg_result_to_tree(&result);
  gpeg_result_remove(tree, SLOT_S, 1, 1);
  gpeg_result_remove(tree, SLOT_MULTILINECOMMENT, 1, 1);
  gpeg_result_remove(tree, SLOT_COMMENT, 1, 1);
  gpeg_result_callback(tree, SLOT_RULE, gpeg_compile_rule, &state);
  gpeg_result_callback(tree, SLOT_EXPRESSION, gpeg_compile_expr, &state);
  gpeg_result_callback(tree, SLOT_REFERENCE, gpeg_compile_call, &state);
  gpeg_result_callback(tree, SLOT_ANY, gpeg_compile_any, &state);
  gpeg_result_callback(tree, SLOT_STRING, gpeg_compile_string, &state);
  gpeg_result_callback(tree, SLOT_QUANTIFIEDMATCHER, gpeg_compile_q, &state);
  gpeg_result_callback(tree, SLOT_SCANMATCHER, gpeg_compile_notand, &state);
  gpeg_result_callback(tree, SLOT_SET, gpeg_compile_set, &state);
  gpeg_result_callback(tree, SLOT_MACRO, gpeg_compile_macro, &state);
  gpeg_result_callback(tree, SLOT_CAPTURE, gpeg_compile_capture, &state);
  gpeg_result_callback(tree, SLOT_VARCAPTURE, gpeg_compile_varcapture, &state);
  gpeg_result_callback(tree, SLOT_VARREFERENCE, gpeg_compile_varref, &state);
  gpeg_result_callback(tree, SLOT_HEXLITERAL, gpeg_compile_hex, &state);
  gpeg_result_callback(tree, SLOT_ENDFORCE, gpeg_compile_endforce, &state);
  gpeg_result_callback(tree, SLOT_BITMASK, gpeg_compile_bitmask, &state);
  gpeg_result_callback(tree, SLOT_LIMITEDCALL, gpeg_compile_lim, &state);
  CHECK(gpeg_result_run(tree));

  RETURN_OK;
}
