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
 * \brief General operations on a dynamic buffer.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#include <util/vec_t.h>

void vec_printf
  (vec_t* out, const char* fmt, ...)
{
  va_list ap;
  int size;

  va_start(ap, fmt);
  size = vsnprintf(0, 0, fmt, ap);
  va_end(ap);
  if (size < 0) {
    return;
  }
  ++size;
  va_start(ap, fmt);
  out->data = realloc(out->data, out->size + size);
  vsnprintf((char*)(out->data) + out->size, size, fmt, ap);
  va_end(ap);
  out->size += (size - 1);
}

void vec_printf_insert
  (vec_t* out, int offset, const char* fmt, ...)
{
  va_list ap;
  int size;

  if (offset < 0 || offset > (int)out->size) {
    offset = out->size;
  }

  va_start(ap, fmt);
  size = vsnprintf(0, 0, fmt, ap);
  va_end(ap);
  if (size < 0) {
    return;
  }
  va_start(ap, fmt);
  out->data = realloc(out->data, out->size + size + 1);
  int remainder = out->size - offset;
  memmove(out->data + offset + size, out->data + offset, remainder + 1);
  unsigned char replace = out->data[ offset + size ];
  vsnprintf((char*)(out->data) + offset, size+1, fmt, ap);
  out->data[ offset + size ] = replace;
  va_end(ap);
  out->size += size;
}

void vec_append
  (vec_t* out, void* mem, unsigned size)
{
  out->data = realloc(out->data, out->size + size + 1);
  if (mem) {
    memcpy(out->data + out->size, mem, size);
  }
  out->size += size;
  ((char*)(out->data))[ out->size ] = 0;
}

void vec_appendchr
  (vec_t* out, unsigned char c)
{
  vec_append(out, &c, 1);
}

void vec_appendc
  (vec_t* out, unsigned char c, unsigned size)
{
  for (unsigned i=0; i < size; i++) {
    vec_append(out, &c, 1);
  }
}

void vec_appendstr
  (vec_t* out, char* str)
{
  if (str) {
    vec_append(out, str, strlen(str));
  }
}

void vec_prepend
  (vec_t* out, void* mem, unsigned size)
{
  out->data = realloc(out->data, out->size + size + 1);
  memmove(out->data + size, out->data, out->size + 1);
  memcpy(out->data, mem, size);
  out->size += size;
}

void vec_insert
  (vec_t* out, int offset, void* mem, unsigned size)
{
  if (offset == -1) {
    vec_append(out, mem, size);
  } else {
    unsigned remainder;
    if (out->size) { offset %= out->size; }
    out->data = realloc(out->data, out->size + size + 1);
    remainder = out->size - offset;
    if (remainder) {
      memmove(out->data + offset + size, out->data + offset, remainder + 1);
    }
    memcpy(out->data + offset, mem, size);
    out->size += size;
  }
}

void vec_reserve
  (vec_t* out, int offset, unsigned size)
{
  if (offset == -1) {
    out->data = realloc(out->data, out->size + size + 1);
    memset(out->data + out->size, 0, size + 1);
    out->size += size;
  } else {
    unsigned remainder;
    if (out->size) { offset %= out->size; }
    out->data = realloc(out->data, out->size + size + 1);
    remainder = out->size - offset;
    if (remainder) {
      memmove(out->data + offset + size, out->data + offset, remainder + 1);
    }
    memset(out->data + offset, 0, size);
    out->size += size;
  }
}

void vec_copy
  (vec_t* out, vec_t* in)
{
  unsigned char* copy = malloc(in->size + 1);

  memcpy(copy, in->data, in->size);
  copy[ in->size ] = 0;
  out->data = copy;
  out->size = in->size;
}

void vec_shift
  (vec_t* out, unsigned offset, unsigned whereto, int size)
{
  if (offset == out->size) {
    out->size = whereto;
    return;
  }
  if (offset > out->size) { return; } // don't know how to do that
  if (size == -1 || offset + size > out->size) {
    size = out->size - offset;
  }
  if (offset < whereto) {
    unsigned diff = whereto - offset;
    out->data = realloc(out->data, out->size + diff + 1);
    memmove(out->data + whereto, out->data + offset, size + 1);
    memset(out->data + offset, 0, diff);
    out->size += diff;
  } else if (offset > whereto) {
    memmove(out->data + whereto, out->data + offset, size + 1);
    out->size -= (offset - whereto);
  }
}

void vec_delete
  (vec_t* vec, unsigned offset, int size)
{
  if (offset >= vec->size) {
    return;
  }
  if (size == -1) {
    size = vec->size - offset;
  }
  if (offset + size >= vec->size) {
    size = vec->size - offset;
  }
  if (offset + size < vec->size) {
    memmove(
      vec->data + offset,
      vec->data + offset + size,
      vec->size - (offset + size)
    );
  }
  vec->size -= size;
  vec->data[ vec->size ] = 0;
}

int vec_find_at
  (vec_t* vec, unsigned offset, const void* mem, unsigned size)
{
  if (size == 0) {
    return -1;
  }
  if (offset >= vec->size) {
    return -1;
  }
  if (size > vec->size) {
    return -1;
  }
  for (unsigned i=offset; i <= vec->size - size; i++) {
    if (0 == memcmp(vec->data + i, mem, size)) {
      return (int)i;
    }
  }
  return -1;
}

int vec_find
  (vec_t* vec, const void* mem, unsigned size)
{
  return vec_find_at(vec, 0, mem, size);
}

/** Reduces size (from the back) **/
void vec_reduce
  (vec_t* vec, unsigned size)
{
  if (0 == vec->size) {
    return;
  }
  if (size > vec->size) {
    size = vec->size;
  }
  vec->size -= size;
  vec->data[ vec->size ] = 0;
}

int vec_compare
  (vec_t* v1, vec_t* v2)
{
  if (v1->size != v2->size) {
    return (v2->size - v1->size);
  }
  for (unsigned i=0; i < v1->size; i++) {
    if (v1->data[ i ] != v2->data[ i ]) {
      return (v2->data[ i ] - v1->data[ i ]);
    }
  }
  return 0;
}

int vec_endswith
  (vec_t* vec, char* str)
{
  unsigned l;

  if (str && ((l = strlen(str)) <= vec->size) && l) {
    if (0 == memcmp(vec->data + vec->size - l, str, l)) {
      return 1;
    }
  }
  return 0;
}

static
unsigned hexdecode
  (char c)
{
  if (c >= '0' && c <= '9') { return (c - '0'); }
  if (c >= 'a' && c <= 'f') { return (c + 10 - 'a'); }
  if (c >= 'A' && c <= 'F') { return (c + 10 - 'A'); }
  return 0;
}

int vec_hex_decode
  (vec_t* vec)
{
  unsigned l = 0, c = 0;
  char codon[ 2 ] = { 0 };
  char* hexchars = "0123456789abcdefABCDEF";

  for (unsigned i=0; i < vec->size; i++) {
    if (vec->data[ i ] == ' '
        || vec->data[ i ] == '\r'
        || vec->data[ i ] == '\n'
        || vec->data[ i ] == '\t')
    {
      continue;
    }
    if (strchr(hexchars, vec->data[ i ])) {
      codon[ c ] = vec->data[ i ];
      ++c;
      if (c == 2) {
        vec->data[ l++ ] = ((hexdecode(codon[ 0 ]) << 4)
                           | hexdecode(codon[ 1 ]));
        c = 0;
      }
    } else {
      return ~0;
    }
  }
  vec->size = l;
  if (vec->data) { vec->data[ vec->size ] = 0; }
  return 0;
}

void vec_hex_encode
  (vec_t* vec)
{
  char* hexchars = "0123456789abcdef";
  unsigned origlen = vec->size;
  unsigned m;
  unsigned d;

  for (unsigned i=0; i < origlen; i += 1024) {
    m = (origlen - i);
    if (m > 1024) {
      m = 1024;
    }
    for (d=0; d < m; d++) {
      char c = vec->data[ d ];
      vec_appendchr(vec, hexchars[ c >> 4 ]);
      vec_appendchr(vec, hexchars[ c & 0x0f ]);
    }
    vec_delete(vec, 0, d);
  }
}

static
int vec_base64_decode_triplet
  (vec_t* vec, uint8_t b[ 4 ], unsigned c)
{
  unsigned l = vec->size;

  for (unsigned i=c; i < 4; i++) { b[i] = 64; }

  vec->data[ l++ ] = (((b[0] & 0x3f) << 2) | ((b[1] & 0x3f) >> 4));
  vec->data[ l++ ] = (((b[1] & 0x3f) << 4) | ((b[2] & 0x3f) >> 2));
  vec->data[ l++ ] = (((b[2] & 0x3f) << 6) | (b[3] & 0x3f));

  if (b[ 0 ] == 64) { return ~0; }
  if (b[ 1 ] == 64) { return ~0; }
  if (b[ 2 ] == 64) { vec->size += 1; return 0; }
  if (b[ 3 ] == 64) { vec->size += 2; return 0; }
  vec->size += 3; return 0;
}

int vec_base64_decode
  (vec_t* vec)
{
  uint8_t b[ 4 ] = { 0 };
  unsigned c = 0;
  unsigned origsize = vec->size;
  char* b64chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "+/=";

  vec->size = 0;
  for (unsigned i=0; i < origsize; i++) {
    if (vec->data[ i ] == ' '
        || vec->data[ i ] == '\r'
        || vec->data[ i ] == '\n'
        || vec->data[ i ] == '\t')
    {
      continue;
    }

    char* f = strchr(b64chars, vec->data[ i ]);
    if (f) {
      b[ c++ ] = (f - b64chars);
      if (c == 4) {
        if (vec_base64_decode_triplet(vec, b, c)) { return ~0; }
        c = 0;
      }
    } else {
      return ~0;
    }
  }
  if (c) {
    if (vec_base64_decode_triplet(vec, b, c)) { return ~0; }
  }
  if (vec->data) { vec->data[ vec->size ] = 0; }
  return 0;
}

void vec_base64_encode
  (vec_t* vec, int space)
{
  unsigned x = 0;
  unsigned m, d;
  unsigned origlen = vec->size;
  char* b64chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "+/";

  for (unsigned i=0; i < origlen; i += 999) {
    m = (origlen - i);
    if (m > 999) {
      m = 999;
    }
    for (d=0; d < m; d += 3) {
      if (space && x > 60) {
        x = 0;
        vec_appendchr(vec, '\n');
      }
      if (d == m-1) {
        vec_appendchr(vec, b64chars[ vec->data[ d ] >> 2 ]);
        vec_appendchr(vec, b64chars[ ((vec->data[ d ] & 0x03) << 4) ]);
        vec_appendstr(vec, "==");
        vec_delete(vec, 0, d+1);
        return;
      } else if (d == m-2) {
        vec_appendchr(vec, b64chars[ vec->data[ d ] >> 2 ]);
        vec_appendchr(vec, 
          b64chars[ ((vec->data[ d ] & 0x03) << 4) | (vec->data[ d+1 ] >> 4) ]
        );
        vec_appendchr(vec, b64chars[ ((vec->data[ d+1 ] & 0x0f) << 2) ]);
        vec_appendchr(vec, '=');
        vec_delete(vec, 0, d+2);
        return;
      } else {
        vec_appendchr(vec, b64chars[ vec->data[ d ] >> 2 ]);
        vec_appendchr(vec, 
          b64chars[ ((vec->data[ d ] & 0x03) << 4) | (vec->data[ d+1 ] >> 4) ]
        );
        vec_appendchr(vec, 
          b64chars[ ((vec->data[ d+1 ] & 0x0f) << 2)
                     | (vec->data[ d+2 ] >> 6) ]
        );
        vec_appendchr(vec, b64chars[ vec->data[ d+2 ] & 0x3f ]);
      }
    }
    vec_delete(vec, 0, d);
  }
}

// Single-byte error correction for messages <255 bytes long
//  using two check bytes. Based on "CA-based byte error-correcting code"
//  by Chowdhury et al.
//
// rmmh 2013

static
uint8_t lfsr(uint8_t x) {
  return (x >> 1) ^ (-(x&1) & 0x8E);
}

static
void eccComputeChecks
  (uint8_t *data, int data_len, uint8_t *out_c0, uint8_t *out_c1)
{
  uint8_t c0 = 0; // parity: m_0 ^ m_1 ^ ... ^ m_n-1
  uint8_t c1 = 0; // lfsr: f^n-1(m_0) ^ f^n(m_1) ^ ... ^ f^0(m_n-1)
  for (int i = 0; i < data_len; ++i) {
    c0 ^= data[i];
    c1 = lfsr(c1 ^ data[i]);
  }
  *out_c0 = c0;
  *out_c1 = c1;
}

static
void eccEncode
  (uint8_t *data, int data_len, uint8_t check[2])
{
  eccComputeChecks(data, data_len, &check[0], &check[1]);
}

static
int eccDecode
  (uint8_t *data, int data_len, uint8_t check[2])
{
  uint8_t s0, s1;
  eccComputeChecks(data, data_len, &s0, &s1);
  s0 ^= check[0];
  s1 ^= check[1];
  if (s0 && s1) {
    int error_index = data_len - 255;
    while (s1 != s0) {  // find i st s1 = lfsr^i(s0) 
      s1 = lfsr(s1);
      error_index++;
    }
    if (error_index < 0 || error_index >= data_len) {
      // multi-byte error?
      return 1;
    }
    data[error_index] ^= s0;
  } else if (s0 || s1) {
    // parity error
  }
  return 0;
}

void vec_ca_encode
  (vec_t* vec)
{
  unsigned l;
  uint8_t check[ 2 ];

  for (unsigned i=0; i < vec->size; i += 254) {
    if ((l = vec->size - i) > 254) {
      l = 254;
    }
    eccEncode(vec->data + i, l, check);
    vec_insert(vec, i, check, 2);
    i += 2;
  }
}

int vec_ca_decode
  (vec_t* vec)
{
  unsigned l;

  for (unsigned i=0; i < vec->size; i += 256) {
    if ((l = vec->size - i) > 256) {
      l = 256;
    }
    if (l < 2) {
      return ~0;
    }
    if (eccDecode(vec->data + i + 2, l - 2, vec->data + i)) {
      return ~0;
    }
    vec_delete(vec, i, 2);
    i -= 2;
  }
  return 0;
}
