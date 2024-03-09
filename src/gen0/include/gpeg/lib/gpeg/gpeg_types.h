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

#ifndef _GPEG_GPEG_TYPES_H_
#define _GPEG_GPEG_TYPES_H_

#include "gpeg_capturelist.h"

typedef struct gpeg_resobj gpeg_resobj_t;

struct gpeg_resobj
{
  unsigned                              type;
  unsigned                              origoffset;
  char*                                 string;
  unsigned                              stringlen;
  gpeg_resobj_t*                        parent;
  gpeg_resobj_t**                       children;
  unsigned                              nchildren;
};

typedef struct
{
  unsigned                              flags;
#define GPEG_RESOBJ_FLAG_SLOT           (1<<0)
#define GPEG_RESOBJ_FLAG_RELINDEX       (1<<1)
#define GPEG_RESOBJ_FLAG_ABSINDEX       (1<<2)
#define GPEG_RESOBJ_FLAG_STRING         (1<<3)
#define GPEG_RESOBJ_FLAG_MEM            (1<<4)
#define GPEG_RESOBJ_FLAG_UPONSUCCESS    (1<<5)
  struct {
    unsigned                              slot;
    unsigned                              relindex;
    unsigned                              absindex;
    char*                                 string;
    struct {
      void*                                 ptr;
      unsigned                              size;
    }                                     mem;
  }                                     query;
  gpeg_resobj_t*                        object;
  unsigned                              uponsuccess;
}
gpeg_resobj_itelt_t;

#endif
