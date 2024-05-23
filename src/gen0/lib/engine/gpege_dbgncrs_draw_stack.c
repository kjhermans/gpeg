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

#include "gpege_private.h"

/**
 *
 */
void gpege_dbgncrs_draw_stack
  (gpege_t* gpege, gpege_ec_t* ec)
{
  unsigned start = 0;
  char line[ 80 ];
  char* label;

  move(4 + gpege_dbgncrs_noinputlines, 0);
    addstr(
"==================================================================<2> Stack =="
  );
  if (ec->stack.count > gpege_dbgncrs_nostacklines) {
    start = ec->stack.count - gpege_dbgncrs_nostacklines;
  }
  for (unsigned i=start; i < ec->stack.count; i++) {
    move(5 + gpege_dbgncrs_noinputlines + i - start, 0);
    if (ec->stack.list[ i ].type == GPEGE_STACK_CATCH) {
      label = str2int_map_reverse_lookup(
                &(gpege->labelmap), ec->stack.list[ i ].address
              );
      snprintf(line, sizeof(line),
               "%.5u CATCH %u (%s)"
               , i
               , ec->stack.list[ i ].address
               , label ? label : "Not found"
      );
    } else if (ec->stack.list[ i ].type == GPEGE_STACK_CALL) {
      uint32_t address = htonl(
        *((int32_t*)
          (&(gpege->bytecode.data[ ec->stack.list[ i ].address - 4 ])))
      );
      label = str2int_map_reverse_lookup(
                &(gpege->labelmap), address
              );
      snprintf(line, sizeof(line),
               "%.5u CALL  %u (%s)"
               , i
               , ec->stack.list[ i ].address
               , label ? label : "Not found"
      );
    }
    addstr(line);
  }
}

#endif
