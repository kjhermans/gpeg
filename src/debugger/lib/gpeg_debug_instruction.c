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

void gpeg_debug_instruction
  (gpege_state_t* state)
{
  char buf[ 32 ] = { 0 };
  uint8_t* instr8 = state->bytecode->data + state->instrptr;
  uint8_t opcode = instr8[0] >> 4;

  if (gpeg_debugger_off) { return; }
  if (state->flags & GPEGE_FLG_DEBUGHEX) { readable_hex = 1; }

  gpeg_engine_state_print(state);

  if ((state->debuggerstate & GPEG_DBGRSTAT_NEXTCALL) && opcode != OP_CALL) {
    return;
  }
  fprintf(stderr, "[?qcoarsHf] > ");
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
"s           Print stack fully.\n"
"H           Toggle input in hex.\n"
"f           Introduce a FAIL.\n"
      );
    } else if (0 == strcmp(buf, "\n")) {
      return;
    } else if (0 == strcmp(buf, "H\n")) {
      fprintf(stderr, "Input now in hex.\n");
      readable_hex = !readable_hex;
    } else if (0 == strcmp(buf, "c\n")) {
      state->debuggerstate |= GPEG_DBGRSTAT_NEXTCALL;
    } else if (0 == strcmp(buf, "s\n")) {
      if (state->stack.count == 0) {
        fprintf(stderr, "No stack.\n");
      }
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
    } else if (0 == strcmp(buf, "f\n")) {
      //.. introduce a FAIL condition
    }
  }
}
