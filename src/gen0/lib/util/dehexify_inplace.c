/**
 * This file is part of the C2 project.

Copyright (c) 2025, Kees-Jan Hermans <kees.jan.hermans@gmail.com>
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

#include <string.h>

static
unsigned hexdecode
  (char c)
{ 
  if (c >= '0' && c <= '9') { return (c - '0'); }
  if (c >= 'a' && c <= 'f') { return (c + 10 - 'a'); }
  if (c >= 'A' && c <= 'F') { return (c + 10 - 'A'); }
  return 0;
} 

/**
 * Decodes hexadecimal content in place. Since the decoded content is
 * always the same in length or less, this should always fit.
 * This function knows no error conditions: it only processes hexadecimal
 * bytes and ignores all others.
 */
void dehexify_inplace
  (char* str, unsigned* resultlength)
{
  char* write = str;
  char codon[ 2 ] = { 0 };
  unsigned c = 0;
  unsigned l = 0;
  char* hexchars = "0123456789abcdefABCDEF";

  while (*str) {
    if (strchr(hexchars, *str)) {
      codon[ c ] = *str;
      ++c;
      if (c == 2) {
        *write = ((hexdecode(codon[ 0 ]) << 4) | hexdecode(codon[ 1 ]));
        ++write;
        ++l;
        c = 0;
      }
    }
    ++str;
  }
  *resultlength = l;
}
