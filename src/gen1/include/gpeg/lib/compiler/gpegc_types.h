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

#ifndef _GPEG_GEN1_GPEG_COMPILER_GPEGC_TYPES_H_
#define _GPEG_GEN1_GPEG_COMPILER_GPEGC_TYPES_H_

typedef struct
{
  vec_t             input;
  vec_t             output;
  vec_t             error;
  char*             slotmap;
  char*             slotmaph;
  char*             parserc;
  char*             parserc_ident;
  struct {
#define GPEGC_MAX_PATHS 32
    char*             path[ GPEGC_MAX_PATHS ];
    unsigned          count;
  }                 import;

#define GPEGC_FLAG_GENTRAPS            (1<<0)
#define GPEGC_FLAG_GENCAPTURES         (1<<1)
#define GPEGC_FLAG_GENRANGES           (1<<2)
#define GPEGC_FLAG_GENRAWQUANTIFIERS   (1<<3)
#define GPEGC_FLAG_GENNOQUADS          (1<<4)
  unsigned          flags;
}
gpegc_compiler_t;

#endif
