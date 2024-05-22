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

#if defined __has_include
#  if __has_include (<ncurses.h>)
#    define _HAS_NCURSES_
#    include <ncurses.h>
#  endif
#endif

#ifdef _HAS_NCURSES_

#include <gpeg/lib/gpeg/gpeg_instructions.h>

#include "gpege_dbgncrs_private.h"

/**
 *
 */
void gpege_dbgncrs_draw_header
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode)
{
  char myline[ 80 ];

  move(0, 0);
  addstr(
"===================================================== GPEG Ncurses Debugger =="
  );

  snprintf(myline, sizeof(myline),
    "Instr#: %.8d, instrptr: %.6u, input offset: %.6u"
    , ec->ninstructions
    , ec->bytecode_offset
    , ec->input_offset
  );
  move(1, 1); addstr(myline);
  if (opcode == OPCODE_FAILURE) {
    move(2, 1); addstr("FAIL");
  } else {
    char* opcodestring = gpeg_opcode2string(opcode);

    switch (opcode) {
    case OPCODE_RET:
      if (gpege_dbgncrs_stepover
          && ec->stack.count < gpege_dbgncrs_stacksize)
      {
        gpege_dbgncrs_stepover = 0;
      }
      __attribute__ ((fallthrough));
    case OPCODE_ANY:
    case OPCODE_FAIL:
    case OPCODE_FAILTWICE:
    case OPCODE_NOOP:
    case OPCODE_TRAP:
      snprintf(myline, sizeof(myline), "%s", opcodestring);
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
        snprintf(myline, sizeof(myline), "%s %u", opcodestring, param);
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
        snprintf(myline, sizeof(myline), "%s %u %u"
          , opcodestring, param0, param1
        );
      }
      break;
    case OPCODE_QUAD:
      {
        unsigned char* quad = &(gpege->bytecode.data[ ec->bytecode_offset+4 ]);
        snprintf(myline, sizeof(myline),
          "QUAD %.2x%.2x%.2x%.2x -- '%c%c%c%c'"
          , quad[ 0 ], quad[ 1 ], quad[ 2 ], quad[ 3 ]
          , quad[ 0 ], quad[ 1 ], quad[ 2 ], quad[ 3 ]
        );
      }
      break;
    case OPCODE_BITMASK:
      {
        unsigned char* param = &(gpege->bytecode.data[ ec->bytecode_offset+4 ]);
        unsigned nbits   = ntohl(*((uint32_t*)(param)));
        unsigned bits    = ntohl(*((uint32_t*)(param + 4)));
        unsigned andmask = ntohl(*((uint32_t*)(param + 8)));
        unsigned ormask  = ntohl(*((uint32_t*)(param + 12)));
        snprintf(myline, sizeof(myline),
          "BITMASK %u %x %x %x"
          , nbits, bits, andmask, ormask
        );
      }
      break;
    case OPCODE_SET:
    case OPCODE_SPAN:
      {
        unsigned char* param = &(gpege->bytecode.data[ ec->bytecode_offset+4 ]);
        snprintf(myline, sizeof(myline),
          "%s %.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x"
          "%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x"
          , opcodestring
          , param[0], param[1], param[2], param[3]
          , param[4], param[5], param[6], param[4]
          , param[8], param[9], param[10], param[11]
          , param[12], param[13], param[14], param[15]
          , param[16], param[17], param[18], param[19]
          , param[20], param[21], param[22], param[23]
          , param[24], param[25], param[26], param[27]
          , param[28], param[29], param[30], param[31]
        );
      }
      break;
    case OPCODE_TESTQUAD:
    case OPCODE_TESTSET:
      myline[ 0 ] = 0;
      break;
    }
    move(2, 1); addstr(myline);
  }
}

#endif
