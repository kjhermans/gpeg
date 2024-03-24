/**
 * This file is part of GPEG, a parsing environment

Copyright (c) 2024, Kees-Jan Hermans <kees.jan.hermans@gmail.com>
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

#include <stdio.h>

#include "gpege_private.h"
#include <gpeg/lib/gpeg/gpeg_instructions.h>

GPEG_ERR_T gpege_debug_verbose
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode, void* arg)
{
  (void)gpege;
  (void)ec;
  (void)arg;

  if (opcode == OPCODE_FAILURE) {
    fprintf(stderr, "-- FAIL --");
  } else {
    char* opcodestring = gpeg_opcode2string(opcode);
    fprintf(stderr,
      "%.8d: %.6u: %.6u: "
      , ec->ninstructions
      , ec->bytecode_offset
      , ec->input_offset
    );
    for (unsigned i=0; i < 8; i++) {
      if (ec->input_offset + i < ec->input->size) {
        unsigned char c = ec->input->data[ ec->input_offset + i ];
        if (c >= 32 && c < 127) {
          fprintf(stderr, "%c", c);
        } else {
          fprintf(stderr, ".");
        }
      } else {
        fprintf(stderr, "*");
      }
    }
    fprintf(stderr, ": %s ", opcodestring);
    switch (opcode) {
    case OPCODE_ANY:
    case OPCODE_FAIL:
    case OPCODE_FAILTWICE:
    case OPCODE_NOOP:
    case OPCODE_RET:
    case OPCODE_TRAP:
      break;
    case OPCODE_BACKCOMMIT:   /* single argument */
    case OPCODE_CALL:
    case OPCODE_PARTIALCOMMIT:
    case OPCODE_CATCH:
    case OPCODE_COMMIT:
    case OPCODE_JUMP:
    case OPCODE_CHAR:
    case OPCODE_END:
    case OPCODE_OPENCAPTURE:
    case OPCODE_CLOSECAPTURE:
    case OPCODE_SKIP:
    case OPCODE_TESTANY:
    case OPCODE_VAR:
      {
        uint32_t param = GET_32BIT_VALUE(
          gpege->bytecode.data,
          ec->bytecode_offset + 4
        );
        fprintf(stderr, "%u ", param);
      }
      break;
    case OPCODE_CONDJUMP:     /* double argument */
    case OPCODE_COUNTER:
    case OPCODE_INTRPCAPTURE:
    case OPCODE_RANGE:
    case OPCODE_TESTCHAR:
      {
        uint32_t param0 = GET_32BIT_VALUE(
          gpege->bytecode.data,
          ec->bytecode_offset + 4
        );
        uint32_t param1 = GET_32BIT_VALUE(
          gpege->bytecode.data,
          ec->bytecode_offset + 8
        );
        fprintf(stderr, "%u %u ", param0, param1);
      }
      break;
    case OPCODE_QUAD:
      {
        for (unsigned i=0; i < 4; i++) {
          char c = gpege->bytecode.data[ ec->bytecode_offset + 4 + i ];
          if (c >= 32 && c < 127) {
            fprintf(stderr, "%c", c);
          } else {
            fprintf(stderr, ".");
          }
        }
      }
      break;
    case OPCODE_ENDISOLATE:
    case OPCODE_ENDREPLACE:
    case OPCODE_ISOLATE:
    case OPCODE_MASKEDCHAR:
    case OPCODE_REPLACE:
    case OPCODE_SET:
    case OPCODE_SPAN:
    case OPCODE_TESTQUAD:
    case OPCODE_TESTSET:
      break;
    }
    fprintf(stderr, "[%u:", ec->stack.count);
    unsigned s = 0;
    if (ec->stack.count > 3) {
      fprintf(stderr, " ..");
      s = ec->stack.count-3;
    }
    for (unsigned i=s; i < ec->stack.count; i++) {
      if (ec->stack.list[ i ].type == GPEGE_STACK_CATCH) {
        fprintf(stderr, " alt/%u", ec->stack.list[ i ].address);
      } else if (ec->stack.list[ i ].type == GPEGE_STACK_CALL) {
        fprintf(stderr, " ret/%u", ec->stack.list[ i ].address);
      }
    }
    fprintf(stderr, "]");
  }
  fprintf(stderr, "\n");

  return GPEG_OK;
}
