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
void gpege_dbgncrs_recalculate
  ()
{
  unsigned w = COLS, h = LINES;
  unsigned nsections;
  unsigned sectionheight = 1;

  if (w < 40) {
    return;
  }
  if (h < 12) {
    return;
  }
  if (w > 128) {
    w = 128;
  }
  if (h > 50) {
    h = 50;
  }
  gpege_dbgncrs_width = w;
  gpege_dbgncrs_height = h;
  nsections =
    gpege_dbgncrs_exp_input +
    gpege_dbgncrs_exp_stack +
    gpege_dbgncrs_exp_captures;
  if (nsections) {
    sectionheight = ((h - 8) / nsections);
  }
  move(1,70); printw("ns: %u, sh: %u\n", nsections, sectionheight);
  if (gpege_dbgncrs_exp_input) {
    gpege_dbgncrs_noinputlines = sectionheight;
  } else {
    gpege_dbgncrs_noinputlines = 1;
  }
  if (gpege_dbgncrs_exp_stack) {
    gpege_dbgncrs_nostacklines = sectionheight;
  } else {
    gpege_dbgncrs_nostacklines = 1;
  }
  if (gpege_dbgncrs_exp_captures) {
    gpege_dbgncrs_nocapturelines = sectionheight;
  } else {
    gpege_dbgncrs_nocapturelines = 1;
  }
}

#endif
