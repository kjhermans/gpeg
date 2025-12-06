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

#include "gpegt_private.h"
#include <gpeg/previous/lib/engine/gpege.h>

static
unsigned char bytecode[] = {
  #include "transform.h"
};

#define GENCALL(f) JOIN(PREVGEN, f)
#define JOIN(a, b) JOIN_AGAIN(a, b)
#define JOIN_AGAIN(a,b) a ## b

/**
 * Main entry function to the transform library.
 * Takes a bytecode, an input, and a transformation
 * definition, and transforms the input based on the capture list
 * of the GPEG engine's run on the input.
 *
 * \param t Which must have the following members set:
 *          - .in
 *          - .out
 *          - .err
 *          - .grammar
 *          - .rules
 *          - .flags
 *
 * \returns GPEG_OK on success, or a GPEG_ERR_* value on error.
 */
GPEG_ERR_T gpegt_transform
  (gpegt_transform_t* t)
{
  DEBUGFUNCTION

  gpege_t gpege = { 0 };
  gpege_ec_t ec = { 0 };
  gpeg_capturelist_t captures = { 0 }; (void)captures;

  gpege.bytecode.data = bytecode;
  gpege.bytecode.size = sizeof(bytecode);

  ec.input = &(t->rules);

  GPEG_CHECK(
    GENCALL(gpege_run)(&gpege, &ec),
    PROPAGATE
  );

  vec_copy(&(t->out), &(t->in));
  
  return GPEG_OK;
}
