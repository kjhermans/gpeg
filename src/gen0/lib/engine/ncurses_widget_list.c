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
#  endif
#endif

#ifdef _HAS_NCURSES_

#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

static int list_init = 0;

/**
 *
 */
int ncurses_widget_list
  (
    unsigned y,
    unsigned x,
    unsigned h,
    unsigned w,
    char*  (*iterator)(void*),
    void*    arg
  )
{
  unsigned offset = 0;
  unsigned selected = 0;
  char** list = { 0 };
  unsigned size = 0;

  if (!list_init) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
  }

  while (1) {
    char* item = iterator(arg);
    if (NULL == item) {
      break;
    }
    list = (char**)realloc(list, sizeof(char*) * (++size));
    list[ size-1 ] = strdup(item);
  }
  if (!size) {
    return ERR;
  }

  while (1) {
    for (unsigned i=0; i < w; i++) {
      move(y, x+i); addch('-');
      move(y+h+2, x+i); addch('-');
    }
    for (unsigned i=0; i < h; i++) {
      move(y+i, x); addch('|');
      if (offset+i < size) {
        if (offset+i == selected) {
          attron(COLOR_PAIR(1));
          printw("%-.*s", w, list[ offset+i ]);
          attroff(COLOR_PAIR(1));
        } else {
          printw("%-.*s", w, list[ offset+i ]);
        }
      }
      move(y+i, x+w+2); addch('|');
    }

    int k = getch();
    switch (k) {
    case ERR:
    case '\n':
    case ' ':
      for (unsigned i=0; i < size; i++) {
        free(list[ i ]);
      }
      free(list);
      return k;
    case KEY_UP:
      if (selected) {
        --selected;
        if (offset >= selected) {
          offset = selected;
        }
      }
      break;
    case KEY_DOWN:
      if (selected < size-1) {
        ++selected;
        if (offset + h <= selected) {
          offset = selected - h;
        }
      }
      break;
    }
  }
}

#endif
