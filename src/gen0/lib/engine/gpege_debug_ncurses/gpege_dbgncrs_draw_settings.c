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

#include "gpege_dbgncrs_private.h"

/**
 *
 */
void gpege_dbgncrs_draw_settings
  (gpege_t* gpege)
{
  unsigned field = 0;
  int k;

  clear();
  move(0, 0);
  addstr(
"============================================ GPEG Ncurses Debugger Settings =="
  );
  move(3, 3); addstr("Expand Input:");
  move(4, 3); addstr("Expand Stack:");
  move(5, 3); addstr("Expand Captures:");
  move(6, 3); printw("Labels loaded:       %u", gpege->labelmap.count);

  move(3, 24);
  if (gpege_dbgncrs_exp_input) {
    addstr("Enabled");
  } else {
    addstr("Disabled");
  }
  move(4, 24);
  if (gpege_dbgncrs_exp_stack) {
    addstr("Enabled");
  } else {
    addstr("Disabled");
  }
  move(5, 24);
  if (gpege_dbgncrs_exp_captures) {
    addstr("Enabled");
  } else {
    addstr("Disabled");
  }

  move(10, 3); addstr("<Q>uit Settings");

  while (1) {
    switch (field) {
    case 0:
      k = ncurses_widget_toggle(
        3, 24, &(gpege_dbgncrs_exp_input)
      );
      break;
    case 1:
      k = ncurses_widget_toggle(
        4, 24, &(gpege_dbgncrs_exp_stack)
      );
      break;
    case 2:
      k = ncurses_widget_toggle(
        5, 24, &(gpege_dbgncrs_exp_captures)
      );
      break;
    }
    switch (k) {
    case 'q': return;
    case KEY_UP: field--; field %= 3; break;
    case KEY_DOWN: field++; field %= 3; break;
    }
  }
}

#endif
