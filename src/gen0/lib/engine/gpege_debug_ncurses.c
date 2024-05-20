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
#include <gpeg/lib/gpeg/gpeg_instructions.h>

static int ncurses_init = 0;

static struct
{
  unsigned          mode;
  unsigned          noinputlines;
  unsigned          rununtil;
  int               stepover;
  unsigned          nostacklines;
  unsigned          stacksize;
  int               exp_input;
  int               exp_stack;
  int               exp_captures;
}
gpege_dbgncrs_state =
{
#define MODE_RUNNER   0
#define MODE_SETTINGS 1
  MODE_RUNNER,
  8,
  0,
  0,
  8,
  0,
  1,
  1,
  0
};

void gpege_debug_ncurses_exit
  ()
{
  endwin();
  ncurses_init = 0;
}

static
char inputbuf[ 80 ];

static
char* gpege_dbgncrs_input
  (unsigned y, unsigned x, unsigned w, char* value)
{
  unsigned off = 0, crs = 0, len;
  int c;

  strncpy(inputbuf, value, sizeof(inputbuf));
  inputbuf[ sizeof(inputbuf)-1 ] = 0;
  len = strlen(inputbuf);

  while (1) {
    move(y,x);
    addch('[');
    for (unsigned i=0; i < w; i++) {
      if (off + i < len) {
        addch(inputbuf[ off + i ]);
      } else {
        addch(' ');
      }
    }
    addch(']');
    move(y, x + 1 + crs);
    refresh();
    switch (c = getch()) {
    case ERR:
      return NULL;
    case '\n':
      return inputbuf;
    case KEY_UP:
    case KEY_DOWN:
      return NULL;
    case KEY_LEFT:
      if (crs > 0) {
        --crs;
      } else if (off > 0) {
        --off;
      }
      break;
    case KEY_RIGHT:
DO_KEY_RIGHT:
      if (crs < w && off + crs < len) {
        ++crs;
      } else if (off + w < len) {
        ++off;
      }
      break;
    case KEY_BACKSPACE:
      if (len && (off + crs)) {
        if (off + crs < len) {
          memmove(
            &(inputbuf[ off+crs ]),
            &(inputbuf[ off+crs+1 ]),
            len - (off+crs+1)
          );
        }
        --len;
        if (crs) {
          --crs;
        } else {
          --off;
        }
      }
      break;
    default:
      if (c >= 32 && c < 127) {
        if (off + crs < len) {
          if (len < sizeof(inputbuf)-1) {
            memmove(
              &(inputbuf[ off+crs+1 ]),
              &(inputbuf[ off+crs ]),
              len - (off+crs)
            );
            inputbuf[ off+crs ] = c;
            ++len;
            goto DO_KEY_RIGHT;
          }
        } else if (off + crs == len) {
          if (len < sizeof(inputbuf)-1) {
            inputbuf[ len++ ] = c;
            inputbuf[ len ] = 0;
            goto DO_KEY_RIGHT;
          }
        }
      }
    }
  }
}

static
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
      if (gpege_dbgncrs_state.stepover
          && ec->stack.count < gpege_dbgncrs_state.stacksize)
      {
        gpege_dbgncrs_state.stepover = 0;
      }
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
    case OPCODE_ENDISOLATE:
    case OPCODE_ENDREPLACE:
    case OPCODE_ISOLATE:
    case OPCODE_BITMASK:
    case OPCODE_REPLACE:
    case OPCODE_SET:
    case OPCODE_SPAN:
    case OPCODE_TESTQUAD:
    case OPCODE_TESTSET:
      myline[ 0 ] = 0;
      break;
    }
    move(2, 1); addstr(myline);
  }
}

static
void gpege_dbgncrs_draw_input
  (gpege_ec_t* ec)
{
  move(3, 0);
  addstr(
"===================================================================== Input =="
  );

  {
    unsigned x = 0, y = 4;
    move(y, x);
    for (unsigned i = ec->input_offset; i < ec->input->size; i++) {
      if (ec->input->data[ i ] == '\n') {
        x = 0; y++;
        if (y > 3 + gpege_dbgncrs_state.noinputlines) {
          break;
        }
        move(y, x);
      } else if (ec->input->data[ i ] > 31 && ec->input->data[ i ] < 127) {
        addch(ec->input->data[ i ]);
        x++;
        if (x > 80) {
          x = 0;
          y++;
          if (y > 3 + gpege_dbgncrs_state.noinputlines) {
            break;
          }
          move(y, x);
        }
      } else {
        char myesc[ 8 ];
        snprintf(myesc, sizeof(myesc), "\\x%.2x", ec->input->data[ i ]);
        if (x < 76) {
          x = 0; y++;
          if (y > 3 + gpege_dbgncrs_state.noinputlines) {
            break;
          }
          move(y, x);
          addstr(myesc);
        } else {
          addstr(myesc);
        }
        x += 4;
      }
    }
  }
}

static
void gpege_dbgncrs_draw_stack
  (gpege_t* gpege, gpege_ec_t* ec)
{
  unsigned start = 0;
  char line[ 80 ];
  char* label;

  move(4 + gpege_dbgncrs_state.noinputlines, 0);
    addstr(
"===================================================================== Stack =="
  );
  if (ec->stack.count > gpege_dbgncrs_state.nostacklines) {
    start = ec->stack.count - gpege_dbgncrs_state.nostacklines;
  }
  for (unsigned i=start; i < ec->stack.count; i++) {
    move(5 + gpege_dbgncrs_state.noinputlines + i - start, 0);
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

static
void gpege_dbgncrs_toggle
  (
    unsigned y,
    unsigned x,
    int* value,
    int* retkey
  )
{
  while (1) {
    move(y, x);
    if (*value) {
      addstr("Enabled ");
    } else {
      addstr("Disabled");
    }
    *retkey = getch();
    switch (*retkey) {
    case KEY_UP: case KEY_DOWN: case 'q':
      return;
    default:
      (*value) = !(*value);
    }
  }
}

static
void gpege_dbgncrs_draw_settings
  ()
{
  unsigned field = 0;
  int k;

  clear();
  move(0, 0);
  addstr(
"============================================ GPEG Ncurses Debugger Settings =="
  );
  move(3,3); addstr("Expand Input");
  move(4,3); addstr("Expand Stack");
  move(5,3); addstr("Expand Captures");

  move(3, 24);
  if (gpege_dbgncrs_state.exp_input) {
    addstr("Enabled");
  } else {
    addstr("Disabled");
  }
  move(4, 24);
  if (gpege_dbgncrs_state.exp_stack) {
    addstr("Enabled");
  } else {
    addstr("Disabled");
  }
  move(5, 24);
  if (gpege_dbgncrs_state.exp_captures) {
    addstr("Enabled");
  } else {
    addstr("Disabled");
  }

  move(10,3); addstr("<Q>uit Settings");

  while (1) {
    switch (field) {
    case 0:
      gpege_dbgncrs_toggle(
        3, 24, &(gpege_dbgncrs_state.exp_input), &k
      );
      break;
    case 1:
      gpege_dbgncrs_toggle(
        4, 24, &(gpege_dbgncrs_state.exp_stack), &k
      );
      break;
    case 2:
      gpege_dbgncrs_toggle(
        5, 24, &(gpege_dbgncrs_state.exp_captures), &k
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

static
int gpege_dbgncrs_recalculate
  ()
{
  unsigned w = COLS, h = LINES;
  unsigned nsections;
  unsigned sectionheight = 1;

  if (w < 40) {
    return ~0;
  }
  if (h < 16) {
    return ~0;
  }
  if (w > 128) {
    w = 128;
  }
  if (h > 50) {
    h = 50;
  }
  //.. if (w != COLS || h != LINES) { resizeterm(h, w); }
  nsections =
    gpege_dbgncrs_state.exp_input +
    gpege_dbgncrs_state.exp_stack +
    gpege_dbgncrs_state.exp_captures;
  if (nsections) {
    sectionheight = ((h-4) / nsections) - 2;
  }
  move(1,70); printw("ns: %u, sh: %u\n", nsections, sectionheight);
  if (gpege_dbgncrs_state.exp_input) {
    gpege_dbgncrs_state.noinputlines = sectionheight;
  } else {
    gpege_dbgncrs_state.noinputlines = 1;
  }
  if (gpege_dbgncrs_state.exp_stack) {
    gpege_dbgncrs_state.nostacklines = sectionheight;
  } else {
    gpege_dbgncrs_state.nostacklines = 1;
  }
  if (gpege_dbgncrs_state.exp_captures) {
//..
  } else {
//..
  }
}

GPEG_ERR_T gpege_debug_ncurses
  (gpege_t* gpege, gpege_ec_t* ec, uint32_t opcode, void* arg)
{
  (void)arg;

  if (!ncurses_init) {
    initscr(); cbreak(); noecho();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    ncurses_init = 1;
  }

  while (1) {

    if (gpege_dbgncrs_state.mode == MODE_SETTINGS) {
      gpege_dbgncrs_draw_settings();
      gpege_dbgncrs_state.mode = MODE_RUNNER;
      gpege_dbgncrs_recalculate();
    }

    clear();
    gpege_dbgncrs_draw_header(gpege, ec, opcode);
    gpege_dbgncrs_draw_input(ec);
    gpege_dbgncrs_draw_stack(gpege, ec);

    move(24, 1);
    addstr("<N>ext <Q>uit <R>unto <S>tepover <C>onfig");
    refresh();
  
    if (gpege_dbgncrs_state.stepover) {
      goto OUT;
    }
    if (ec->ninstructions < gpege_dbgncrs_state.rununtil) {
      goto OUT;
    }
    int c = getch();
    switch (c) {
    case ERR:
      return GPEG_ERR_EXIT;
    case 'q':
      return GPEG_ERR_EXIT;
    case 'n': case ' ':
      goto OUT;
    case 'r':
      move(23, 1);
      addstr("Run to instr#:");
      char* instrstr = gpege_dbgncrs_input(23, 16, 10, "");
      if (instrstr) {
        unsigned instr = strtoul(instrstr, 0, 10);
        gpege_dbgncrs_state.rununtil = instr;
      }
      break;
    case 's':
      gpege_dbgncrs_state.stepover = 1;
      gpege_dbgncrs_state.stacksize = ec->stack.count;
      goto OUT;
      break;
    case 'c':
      gpege_dbgncrs_state.mode = MODE_SETTINGS;
      break;
    }
  }

OUT:
  return GPEG_OK;
}

#endif
