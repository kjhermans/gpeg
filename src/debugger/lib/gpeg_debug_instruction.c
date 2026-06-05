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

#define GPEG_DBGRSTAT_NEXTCALL  (1<<0)

int gpeg_debugger_off = 0;

extern void gpeg_engine_state_print
  (gpege_state_t* state);

extern int readable_hex;

static
void gpege_actionlist_debug
  (const vec_t* input, gpege_actionlist_t* list)
{
  if (list->count == 0) {
    fprintf(stderr, "No actions.\n");
  } else {
    fprintf(stderr, "Actions:\n");
    for (unsigned i=0; i < list->count; i++) {
      fprintf(stderr,
        "  Action %u: %s reg=%u off=%u stk=%u "
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
}

static
void gpeg_instruction_print_labeled
  (gpege_state_t* state, char* opcodestring)
{
  uint8_t* instr8 = state->bytecode->data + state->instrptr;
  unsigned offset = (((instr8[ 1 ] & 0x0f) << 16) | (instr8[ 2 ] << 8) | instr8[ 3]);
  char* label = NULL;

  if (offset == state->instrptr + 4) {
    fprintf(stderr, "  %s __NEXT__\n", opcodestring);
  } else if (gpeg_labelmap &&
             (label = gpeg_labelmap_inverse(gpeg_labelmap, offset)) != NULL)
  {
    fprintf(stderr, "  %s %s\n", opcodestring, label);
  } else {
    fprintf(stderr, "  %s %u\n", opcodestring, offset);
  }
}

static
void gpeg_instruction_print
  (gpege_state_t* state)
{
  uint8_t* instr8 = state->bytecode->data + state->instrptr;
  uint8_t opcode = instr8[0] >> 4;

  switch (opcode) {
  case OP_END: fprintf(stderr, "  end %u\n", ((instr8[1]<<16) | (instr8[2]<<8) | instr8[3])); break;
  case OP_RANGE: break;
  case OP_LIMIT: break;
  case OP_CALL: gpeg_instruction_print_labeled(state, "call"); break;
  case OP_RET: break;
  case OP_CATCH: gpeg_instruction_print_labeled(state, "catch"); break;
  case OP_COMMIT: gpeg_instruction_print_labeled(state, "commit"); break;
  case OP_BACKCOMMIT: gpeg_instruction_print_labeled(state, "backcommit"); break;
  case OP_PARTIALCOMMIT: gpeg_instruction_print_labeled(state, "partialcommit"); break;
  case OP_FAIL: fprintf(stderr, "  fail\n"); break;
  case OP_FAILTWICE: fprintf(stderr, "  failtwice\n"); break;
  case OP_VAR: break;
  case OP_OPENCAPTURE: break;
  case OP_CLOSECAPTURE: break;
  case OP_COUNTER: break;
  case OP_CONDJUMP: break;
  }
}

void gpeg_debug_instruction
  (gpege_state_t* state)
{
  char buf[ 32 ] = { 0 };
  uint8_t* instr8 = state->bytecode->data + state->instrptr;
  uint8_t opcode = instr8[0] >> 4;

  if (gpeg_debugger_off) { return; }
  if (state->flags & GPEGE_FLG_DEBUGHEX) { readable_hex = 1; }

AGAIN:
  gpeg_engine_state_print(state);
  gpeg_instruction_print(state);

  if ((state->debuggerstate & GPEG_DBGRSTAT_NEXTCALL) && opcode != OP_CALL) {
    return;
  }
  fprintf(stderr, "[?qcoarSAHF] > ");
  if (fgets(buf, sizeof(buf), stdin)) {
    if (0 == strcmp(buf, "q\n")) {
      fprintf(stderr, "Exiting.\n");
      exit(0);
    } else if (0 == strcmp(buf, "?\n") || 0 == strcmp(buf, "h\n")) {
      fprintf(stderr,
"Help:\n\n"
"q           Quit\n"
"? or h      Print this help text.\n"
"<Enter>     Step.\n"
"c           Run to the next call.\n"
"o           Step over the call.\n"
"a           Always step over this call.\n"
"r <n>       Run to instruction number <n>.\n"
"S           Print stack.\n"
"A           Print action list.\n"
"H           Toggle input in hex.\n"
"F           Introduce a FAIL.\n"
      );
    } else if (0 == strcmp(buf, "\n")) {
      return;
    } else if (0 == strcmp(buf, "H\n")) {
      fprintf(stderr, "Input now in hex.\n");
      readable_hex = !readable_hex;
    } else if (0 == strcmp(buf, "c\n")) {
      state->debuggerstate |= GPEG_DBGRSTAT_NEXTCALL;
      return;
    } else if (0 == strcmp(buf, "A\n")) {
      gpege_actionlist_debug(state->input, &(state->actions));
    } else if (0 == strcmp(buf, "S\n")) {
      if (state->stack.count == 0) {
        fprintf(stderr, "No stack.\n");
      } else {
        fprintf(stderr, "Stack:\n");
        for (unsigned i=0; i < state->stack.count; i++) {
          fprintf(stderr,
            "  #%u; typ=%s, instr=%u, input=%u, #act=%u, #ctrs=%u, inplen=%u\n"
            , i
            , (state->stack.list[ i ].type == 1 ? "call" : "catch")
            , state->stack.list[ i ].instrptr
            , state->stack.list[ i ].inputptr
            , state->stack.list[ i ].actioncount
            , state->stack.list[ i ].countercount
            , state->stack.list[ i ].inputsizescount
          );
        }
      }
    } else if (0 == strcmp(buf, "F\n")) {
      state->failed = 1;
      return;
    }
  }
  goto AGAIN;
}
