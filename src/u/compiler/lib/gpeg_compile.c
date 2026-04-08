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

#include <gpeg/compiler/lib.h>
#include <gpeg/engine/gpeg_engine.h>

static
#include <gpeg/compiler/grammar_bytecode.h>

static
int gpeg_compile_p1_rule
  (
    gpege_caplist_t* captures,
    unsigned ci,
    unsigned flags,
    vec_t* assembly
  )
{
  char rulename[ 128 ] = { 0 };

  snprintf(rulename, sizeof(rulename),
    "%-.*s", captures->list[ ci+1 ].vec.size, captures->list[ ci+1 ].vec.data
  );
  return 0;
}

static
int gpeg_compile_p1_rules
  (
    gpege_caplist_t* captures,
    unsigned flags,
    vec_t* assembly
  )
{
  for (unsigned i=0; i < captures->count; i++) {
    gpege_capture_t* capture = &(captures->list[ i ]);
    if (capture->reg == SLOT_RULE) {
      CHECK(gpeg_compile_p1_rule(captures, i, flags, assembly));
    }
  }
  return 0;
}

/**
 *
 */
int gpeg_compile
  (
    const vec_t* grammar,
    vec_t* assembly,
    unsigned flags
  )
{
  DEBUGFUNCTION
  ASSERT(grammar)
  ASSERT(assembly)

  vec_t bytecode = { (unsigned char*)grammar_byc, grammar_byc_len };
  gpege_result_t result = { 0 };

  CHECK(gpeg_engine_run(&bytecode, grammar, 0, &result));
  if (!(result.success)) {
    fprintf(stderr, "Parser error at.\n");
    RETURN_ERR(GPEGC_ERR_PARSER);
  }
  CHECK(gpeg_compile_p1_rules(&(result.captures), flags, assembly));
  //.. free stuff

  RETURN_OK;
}
