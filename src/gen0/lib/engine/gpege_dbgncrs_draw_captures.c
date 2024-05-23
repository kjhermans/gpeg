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
void gpege_dbgncrs_draw_captures
  (gpege_t* gpege, gpege_ec_t* ec)
{
  char lines[ gpege_dbgncrs_nocapturelines ][ 80 ];
  unsigned curline = gpege_dbgncrs_nocapturelines - 1;
  (void)gpege;

  memset(lines, 0, sizeof(lines));
  move(
    5 + gpege_dbgncrs_noinputlines + gpege_dbgncrs_nostacklines,
    0
  );
    addstr(
"===============================================================<3> Captures =="
  );
  for (unsigned i=ec->actions.count; i > 0; i--) {
    gpege_action_t* a1 = &(ec->actions.list[ i-1 ]);
    if (a1->type == GPEGE_ACTION_CLOSECAPTURE) {
      unsigned level = 1;
      for (unsigned j=i-1; j > 0; j--) {
        gpege_action_t* a0 = &(ec->actions.list[ j-1 ]);
        if (a0->type == GPEGE_ACTION_OPENCAPTURE
            && a0->slot == a1->slot)
        {
          --level;
          if (level == 0) {
            unsigned ll;
            if (gpege->slotmap.count) {
              char* slotname =
                str2int_map_reverse_lookup(&(gpege->slotmap), a0->slot);
              snprintf(lines[ curline ], 80,
                "Slot %u (%s), off %u, len %u :"
                , a0->slot
                , slotname ? slotname : "unknown"
                , a0->input_offset
                , a1->input_offset - a0->input_offset
              );
            } else {
              snprintf(lines[ curline ], 80,
                "Slot %u, off %u, len %u :"
                , a0->slot
                , a0->input_offset
                , a1->input_offset - a0->input_offset
              );
            }
            ll = strlen(lines[ curline ]);
            for (unsigned k=a0->input_offset; k < a1->input_offset; k++) {
              if (k - a0->input_offset > 40) {
                lines[ curline ][ ll++ ] = '.';
                lines[ curline ][ ll++ ] = '.';
                lines[ curline ][ ll++ ] = '.';
                lines[ curline ][ ll ] = 0;
                break;
              } else {
                char c = ec->input->data[ k ];
                if (c >= 32 && c < 127) {
                  lines[ curline ][ ll++ ] = c;
                } else {
                  lines[ curline ][ ll++ ] = '?';
                }
                lines[ curline ][ ll ] = 0;
              }
            }
            break;
          }
        } else if (a0->type == GPEGE_ACTION_CLOSECAPTURE) {
          ++level;
        }
      }
      if (lines[ curline ][ 0 ]) {
        if (curline) {
          --curline;
        } else {
          break;
        }
      }
    }
  }
  for (unsigned i=0; i < gpege_dbgncrs_nocapturelines - curline; i++) {
    move(
      i + 6 + gpege_dbgncrs_noinputlines + gpege_dbgncrs_nostacklines,
      0
    );
    addstr(lines[ curline + i ]);
  }
}

#endif
