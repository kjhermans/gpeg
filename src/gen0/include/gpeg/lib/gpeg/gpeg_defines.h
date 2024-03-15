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

#ifndef _GEN0_GPEG_GPEG_GPEG_DEFINES_H_
#define _GEN0_GPEG_GPEG_GPEG_DEFINES_H_

typedef struct {
  int code;
} GPEG_ERR_T;

#define GPEG_OK                  (GPEG_ERR_T){ .code = 0 }
#define GPEG_ERR_NOTFOUND        (GPEG_ERR_T){ .code = 1 }
#define GPEG_ERR_OVERFLOW        (GPEG_ERR_T){ .code = 2 }
#define GPEG_ERR_TRAP            (GPEG_ERR_T){ .code = 3 }
#define GPEG_ERR_INTRPCAPTURE    (GPEG_ERR_T){ .code = 4 }
#define GPEG_ERR_NOMATCH         (GPEG_ERR_T){ .code = 5 }
#define GPEG_ERR_BYTECODE        (GPEG_ERR_T){ .code = 6 }
#define GPEG_ERR_MAXINSTRUCTIONS (GPEG_ERR_T){ .code = 7 }

#define GPEG_ERR_QUANTIFIER      (GPEG_ERR_T){ .code = 16 }

#define GPEG_ERR_LABEL           (GPEG_ERR_T){ .code = 64 }

#define PROPAGATE { return __e; }

#ifdef _DEBUG
#define GPEG_CHECK(fnc,alt) { \
  GPEG_ERR_T __e = (fnc); \
  if (__e.code) { \
    fprintf(stderr, "Error %d in %s:%d\n", __e.code, __FILE__, __LINE__); \
    (alt); \
    if (__e.code < 0) { return __e; } \
  } \
}
#else
#define GPEG_CHECK(fnc,alt) { \
  GPEG_ERR_T __e = (fnc); \
  if (__e.code) { \
    (alt); \
    if (__e.code < 0) { return __e; } \
  } \
}
#endif

#endif
