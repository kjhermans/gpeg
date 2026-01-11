/**
 * This file is part of GPEG, a parser engine.

Copyright (c) 2020, Kees-Jan Hermans <kees.jan.hermans@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Kees-Jan Hermans BE LIABLE FOR ANY
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
#include <ctype.h>

/**
 * Writes the contents of a piece of memory to a file, hexdump-style.
 * If the given file is NULL, stderr will be used.
 */
void flogmem_colwidth
  (FILE* file, unsigned colwidth, const void* _mem, unsigned size)
{
  const char* mem = _mem;
  char print[colwidth];
  unsigned int c = 0;
  *print = 0;
  if (file == 0) {
    file = stderr;
  }
  if (size == 0) {
    return;
  }
  fprintf(file, "%.8x  ", c);
  while (size--) {
    unsigned char byte = *mem++;
    fprintf(file, "%.2x ", byte);
    print[c % colwidth] = (isprint(byte) ? byte : '.');
    if ((++c % colwidth) == 0) {
      fprintf(file, "     %-.*s\n%.8x  ", colwidth, print, c);
      *print = 0;
    }
  }
  while (c % colwidth) {
    print[c % colwidth] = ' ';
    c++;
    fprintf(file, "   ");
  }
  fprintf(file, "     %-.*s\n", colwidth, print);
  fflush(file);
}

void flogmem
  (FILE* file, const void* mem, unsigned size)
{
  flogmem_colwidth(file, 16, mem, size);
}

void logmem
  (const void* mem, unsigned size)
{
  flogmem(stderr, mem, size);
}
