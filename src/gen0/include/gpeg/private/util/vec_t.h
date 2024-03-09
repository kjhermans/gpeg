/**
 * This file is part of Varman, a replicating JSON database

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

#ifndef _GPEG_GEN0_GPEG_UTIL_VEC_T_H_
#define _GPEG_GEN0_GPEG_UTIL_VEC_T_H_

typedef struct
{
  unsigned char* data;
  unsigned size;
}
vec_t;

void vec_printf
  (vec_t* out, char* fmt, ...);

void vec_printf_insert
  (vec_t* out, int offset, char* fmt, ...);

void vec_append
  (vec_t* out, void* mem, unsigned size);

void vec_appendchr
  (vec_t* out, unsigned char c);

void vec_appendstr
  (vec_t* out, char* str);

void vec_prepend
  (vec_t* out, void* mem, unsigned size);

void vec_insert
  (vec_t* out, int offset, void* mem, unsigned size);

void vec_reserve
  (vec_t* out, int offset, unsigned size);

void vec_copy
  (vec_t* out, vec_t* in);

void vec_shift
  (vec_t* out, unsigned offset, unsigned whereto, int size);

#endif
