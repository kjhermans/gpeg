/**
 * This file is part of GPEG, a parsing environment

Copyright (c) 2026, Kees-Jan Hermans <kees.jan.hermans@gmail.com>
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

#ifndef _GPEGU_LIB_H_
#define _GPEGU_LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <andy/vec_t.h>
#include <andy/devmacroes.h>
#include <andy/array.h>
#include <andy/uint32list.h>

#include <gpeg/engine/gpeg_engine.h>

#define ACT_OPEN  1
#define ACT_CLOSE 2

typedef struct
{
  int      action;
  uint16_t reg;
  uint32_t offset;
  unsigned stacklen;
}
gpege_action_t;

MAKE_ARRAY_HEADER(gpege_action_t, gpege_actionlist_);

#define GPEGU_INSTR_OFFSET(_ptr8) \
  (uint32_t)(((_ptr8[1]&0x0f)<<16)|(_ptr8[2]<<8)|_ptr8[3])

typedef struct
{
  uint8_t       type;
  uint32_t      instrptr;
  uint32_t      inputptr;
  unsigned      actioncount;
  unsigned      countercount;
  unsigned      inputsizescount;
}
gpege_stackelt_t;

#undef ARRAY_EQUALS
#define ARRAY_EQUALS(a,b) (&a == &b)
MAKE_ARRAY_HEADER(gpege_stackelt_t, gpege_stack_);

typedef struct gpege_state
{
  const vec_t*          bytecode;
  const vec_t*          input;
  unsigned              inputsiz;
  int                   ended;
  int                   failed;
  int                   eof;
  unsigned              instrptr;
  unsigned              inputptr;
  unsigned              inputbit;
  gpege_stack_t         stack;
  gpege_actionlist_t    actions;
  uint32list_t          inputsizes;
  unsigned              instrctr;
  unsigned              counters[ GPEGE_MAX_COUNTERS ][ 2 ];
  unsigned              countercount;
}
gpege_state_t;

#ifdef _DEBUGGER
extern
void gpeg_debug_instruction
  (gpege_state_t* state, int* dontstep);
#endif

#endif
