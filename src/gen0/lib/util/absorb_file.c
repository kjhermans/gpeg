/**
 * This file is part of GPEG, a parsing environment

Copyright (c) 2023, Kees-Jan Hermans <kees.jan.hermans@gmail.com>
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

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

/**
 * Reads the contents of a file into a dynamically allocated memory buffer.
 * The caller has to free this memory.
 * The function returns zero on success, non zero on failure.
 */
int absorb_file
  (char* path, unsigned char** buf, unsigned* buflen)
{
  unsigned char tmp[ 1024 ];
  int fd;

  if (0 == strcmp(path, "-")) {
    fd = 0;
  } else if ((fd = open(path, O_RDONLY, 0)) < 0) {
    return -1;
  }
  *buf = malloc(1); (*buf)[0] = 0;
  *buflen = 0;
  while (1) {
    int r = read(fd, tmp, sizeof(tmp));
    if (r <= 0) {
      (*buf)[ *buflen ] = 0;
      return 0;
    } else {
      *buf = (unsigned char*)realloc(*buf, (*buflen) + r + 1);
      memcpy((*buf) + (*buflen), tmp, r);
      (*buflen) += r;
    }
  }
}
