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

#include <ncurses.h>
#include <string.h>

/**
 *
 */
int ncurses_widget_input
  (unsigned y, unsigned x, unsigned w, char* value, unsigned valuesize)
{
  unsigned off = 0, crs = 0, len;
  int c;

  value[ valuesize-1 ] = 0;
  len = strlen(value);

  while (1) {
    move(y,x);
    addch('[');
    for (unsigned i=0; i < w; i++) {
      if (off + i < len) {
        addch(value[ off + i ]);
      } else {
        addch(' ');
      }
    }
    addch(']');
    move(y, x + 1 + crs);
    refresh();
    switch (c = getch()) {
    case ERR:
    case '\n':
    case KEY_UP:
    case KEY_DOWN:
      return c;
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
            &(value[ off+crs ]),
            &(value[ off+crs+1 ]),
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
          if (len < valuesize-1) {
            memmove(
              &(value[ off+crs+1 ]),
              &(value[ off+crs ]),
              len - (off+crs)
            );
            value[ off+crs ] = c;
            ++len;
            goto DO_KEY_RIGHT;
          }
        } else if (off + crs == len) {
          if (len < valuesize-1) {
            value[ len++ ] = c;
            value[ len ] = 0;
            goto DO_KEY_RIGHT;
          }
        }
      }
    }
  }
}

#endif
