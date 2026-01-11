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
  (vec_t* out, const char* fmt, ...);

void vec_printf_insert
  (vec_t* out, int offset, const char* fmt, ...);

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

void vec_delete
  (vec_t* out, unsigned offset, int size);

void vec_appendc
  (vec_t* out, unsigned char c, unsigned size);

int vec_find
  (vec_t* vec, const void* mem, unsigned size);

int vec_find_at
  (vec_t* vec, unsigned offset, const void* mem, unsigned size);

void vec_reduce
  (vec_t* vec, unsigned size);

int vec_compare
  (vec_t* v1, vec_t* v2);

int vec_endswith
  (vec_t* vec, char* str);

/** Relatively standard encoders / decoders, in place **/

int vec_hex_decode
  (vec_t* vec);

void vec_hex_encode
  (vec_t* vec);

int vec_base64_decode
  (vec_t* vec);

void vec_base64_encode
  (vec_t* vec, int spaced);

/** Error correction codes **/

void vec_ca_encode
  (vec_t* vec);

int vec_ca_decode
  (vec_t* vec);

#endif
