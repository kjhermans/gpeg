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

#ifndef _GEN0_GPEG_ENGINE_TYPES_H_
#define _GEN0_GPEG_ENGINE_TYPES_H_

#include <stdint.h>

#include <gpeg/private/util/vec_t.h>
#include <gpeg/private/util/str2int_map.h>

#include <gpeg/lib/gpeg/gpeg_defines.h>

#include <gpeg/lib/engine/gpege_stack.h>
#include <gpeg/lib/engine/gpege_actions.h>
#include <gpeg/lib/engine/gpege_register.h>

#include "gpege_actions.h"

typedef struct gpege gpege_t;
typedef struct gpege_ec gpege_ec_t;

struct gpege
{
  vec_t                         bytecode;
  GPEG_ERR_T                  (*debugger)(gpege_t*,gpege_ec_t*,uint32_t,void*);
  void*                         debugarg;
  unsigned                      maxinstructions;
  str2int_map_t                 slotmap;
  str2int_map_t                 labelmap;
};

struct gpege_ec
{
  vec_t*                        input;
  vec_t*                        errorstr;
  unsigned                      input_offset;
  unsigned                      input_offset_max;
  unsigned                      bytecode_offset;
  unsigned                      ninstructions;
  int                           failed;
  int                           endcode;
  gpege_stack_t                 stack;
  unsigned                      stack_max;
  unsigned                      reg_ilen;
  int                           reg_ilen_set;
  unsigned                      callcounter;
  unsigned                      currentcall;
  gpege_actionlist_t            actions;
  gpege_register_t              reg;
};

#endif
