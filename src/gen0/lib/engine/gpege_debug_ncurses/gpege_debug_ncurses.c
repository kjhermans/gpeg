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

#include <gpeg/lib/gpeg/gpeg_instructions.h>

#if defined __has_include
#  if __has_include (<ncurses.h>)
#    define _HAS_NCURSES_
#    include <ncurses.h>
#  endif
#endif

#ifdef _HAS_NCURSES_

#include "gpege_dbgncrs_private.h"

#include <gpeg/private/util/map.h>
MAKE_MAP_HEADER(char*, gpege_ec_t, gpege_dbgncrs_bookmark_)
MAKE_MAP_CODE(char*, gpege_ec_t, gpege_dbgncrs_bookmark_)
static gpege_dbgncrs_bookmark_t bookmarks = { 0 };

static int ncurses_init = 0;

unsigned gpege_dbgncrs_width            = 80;
unsigned gpege_dbgncrs_height           = 25;
unsigned gpege_dbgncrs_mode             = MODE_RUNNER;
unsigned gpege_dbgncrs_noinputlines     = 0;
unsigned gpege_dbgncrs_rununtil         = 0;
int      gpege_dbgncrs_stepover         = 0;
unsigned gpege_dbgncrs_nostacklines     = 0;
unsigned gpege_dbgncrs_stacksize        = 0;
unsigned gpege_dbgncrs_nocapturelines   = 0;
int      gpege_dbgncrs_exp_input        = 0;
int      gpege_dbgncrs_exp_stack        = 1;
int      gpege_dbgncrs_exp_captures     = 1;

void gpege_debug_ncurses_exit
  ()
{
  endwin();
  ncurses_init = 0;
}

GPEG_ERR_T gpege_debug_ncurses
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode, void* arg)
{
  int lastinstruction = 0;
  (void)arg;

  if (!ncurses_init) {
    initscr(); cbreak(); noecho();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    ncurses_init = 1;
    gpege_dbgncrs_recalculate();
  }

  while (1) {

    if (gpege_dbgncrs_mode == MODE_SETTINGS) {
      gpege_dbgncrs_draw_settings(gpege);
      gpege_dbgncrs_mode = MODE_RUNNER;
      gpege_dbgncrs_recalculate();
    }

    clear();
    gpege_dbgncrs_draw_header(gpege, ec, opcode);
    gpege_dbgncrs_draw_input(ec);
    gpege_dbgncrs_draw_stack(gpege, ec);
    gpege_dbgncrs_draw_captures(gpege, ec);

    if ((ec->failed && ec->stack.count == 0) || (opcode == OPCODE_END)) {
      move(gpege_dbgncrs_height-1, 56);
      addstr("LAST INSTRUCTION");
      lastinstruction = 1;
    } else {
      if (gpege_dbgncrs_stepover) {
        refresh();
        goto OUT;
      }
      if (ec->ninstructions < gpege_dbgncrs_rununtil) {
        refresh();
        goto OUT;
      }
    }

    move(gpege_dbgncrs_height-1, 1);
    if (lastinstruction) {
      addstr("<Q>uit, <C>onfig");
    } else {
      addstr("<Q>uit, <C>onfig, <R>un to, <S>tep over, <B>ookmark");
    }
    refresh();
  
    int c = getch();
    switch (c) {
    case ERR:
      return GPEG_ERR_EXIT;
    case KEY_RESIZE:
      gpege_dbgncrs_recalculate();
      break;
    case '1':
      gpege_dbgncrs_exp_input = !(gpege_dbgncrs_exp_input);
      gpege_dbgncrs_recalculate();
      break;
    case '2':
      gpege_dbgncrs_exp_stack = !(gpege_dbgncrs_exp_stack);
      gpege_dbgncrs_recalculate();
      break;
    case '3':
      gpege_dbgncrs_exp_captures = !(gpege_dbgncrs_exp_captures);
      gpege_dbgncrs_recalculate();
      break;
    case 'q':
      return GPEG_ERR_EXIT;
    case 'n': case ' ':
      if (!lastinstruction) {
        goto OUT;
      }
      break;
    case 'r':
      {
        char myline[ 80 ] = { 0 };
        move(gpege_dbgncrs_height-2, 1);
        addstr("Run to instr#:");
        int k = ncurses_widget_input(
          gpege_dbgncrs_height-2, 16, 10, myline, sizeof(myline)
        ); (void)k;
        if (strspn(myline, "0123456789") == strlen(myline)) {
          unsigned instr = strtoul(myline, 0, 10);
          gpege_dbgncrs_rununtil = instr;
        } else {
          gpege_ec_t ec_bkmk;
          if (gpege_dbgncrs_bookmark_get(&bookmarks, myline, &ec_bkmk) == 0) {
            *ec = ec_bkmk;
            goto OUT;
          }
        }
      }
      break;
    case 's':
      if (!lastinstruction) {
        gpege_dbgncrs_stepover = 1;
        gpege_dbgncrs_stacksize = ec->stack.count;
        goto OUT;
      }
      break;
    case 'b':
      {
        char myline[ 80 ] = { 0 };
        move(gpege_dbgncrs_height-2, 1);
        addstr("Name:");
        int k = ncurses_widget_input(
          gpege_dbgncrs_height-2, 7, 10, myline, sizeof(myline)
        ); (void)k;
        gpege_ec_t state = { 0 };
        GPEG_CHECK(gpege_ec_copy(&state, ec), PROPAGATE);
        gpege_dbgncrs_bookmark_put(&bookmarks, strdup(myline), state);
      }
      break;
    case 'c':
      gpege_dbgncrs_mode = MODE_SETTINGS;
      break;
    }
  }

OUT:
  return GPEG_OK;
}

#endif
