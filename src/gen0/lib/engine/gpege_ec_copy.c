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

#include "gpege_private.h"

/**
 * Copies the highly dynamic elements of an engine state to a copy.
 * Note: This is a deep-copy, but not of all malloced elements of the struct.
 */
GPEG_ERR_T gpege_ec_copy
  (gpege_ec_t* dst, gpege_ec_t* src)
{
  *dst = *src;

  dst->stack.list = malloc(sizeof(gpege_stackelt_t) * src->stack.allocated);
  memcpy(
    dst->stack.list,
    src->stack.list,
    sizeof(gpege_stackelt_t) * src->stack.allocated
  );

  dst->actions.list = malloc(sizeof(gpege_action_t) * src->actions.allocated);
  memcpy(
    dst->actions.list,
    src->actions.list,
    sizeof(gpege_action_t) * src->actions.allocated
  );

  dst->reg.list = malloc(sizeof(gpege_regelt_t) * src->reg.allocated);
  memcpy(
    dst->reg.list,
    src->reg.list,
    sizeof(gpege_regelt_t) * src->reg.allocated
  );

  return GPEG_OK;
}
