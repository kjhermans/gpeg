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

#include "gpega_private.h"
#include "assembly.slotmap.h"
#include <gpeg/previous/lib/engine/gpege.h>

static
unsigned char bytecode[] = {
  #include "assembly.h"
};

#define GENCALL(f) JOIN(PREVGEN, f)
#define JOIN(a, b) JOIN_AGAIN(a, b)
#define JOIN_AGAIN(a,b) a ## b

/**
 * Library main access function.
 * Parses the assembly given in input,
 * and emits the corresponing bytecode in output.
 */
GPEG_ERR_T gpega_assemble
  (vec_t* input, vec_t* output, vec_t* error, char* labelmap, unsigned flags)
{
  DEBUGFUNCTION
  ASSERT(input)
  ASSERT(output)
  ASSERT(error)

  (void)flags;

  gpege_t gpege = { 0 };
  gpege_ec_t ec = { 0 };
  gpeg_capturelist_t captures = { 0 };
  int e;

  gpege.bytecode.data = bytecode;
  gpege.bytecode.size = sizeof(bytecode);

  ec.input = input;

#ifdef _DEBUG
  gpege.debugger = gpege_debug_verbose;
#endif

  GPEG_CHECK(
    GENCALL(gpege_run(&gpege, &ec)),
    PROPAGATE
  );
  GPEG_CHECK(
    gpege_actions2captures(
      ec.input,
      &(ec.actions),
      &captures
    ),
    PROPAGATE
  );
  gpeg_capturelist_remove(&captures, SLOT_S);
  gpeg_capturelist_remove(&captures, SLOT_MULTILINECOMMENT);
  gpeg_capturelist_remove(&captures, SLOT_COMMENT);

  gpega_t gpega = { 0 };
  gpega.output = output;
  if ((e = gpega_grammar_process_node(&(captures.list[ 0 ]), &gpega)) != 0) {
    vec_printf(error, "Assembly error code %d in round zero.", e);
    return (GPEG_ERR_T){ .code = e };
  }
  ++(gpega.round);
  gpega.offset = 0;
  if ((e = gpega_grammar_process_node(&(captures.list[ 0 ]), &gpega)) != 0) {
    vec_printf(error, "Assembly error code %d in round one.", e);
    return (GPEG_ERR_T){ .code = e };
  }

  if (labelmap) {
    GPEG_CHECK(gpega_labelmap_write(&gpega, labelmap), PROPAGATE);
  }

  str2int_map_free(&(gpega.labelmap));
  gpege_ec_free(&ec);
  gpeg_capturelist_free(&captures);

  return GPEG_OK;
}
