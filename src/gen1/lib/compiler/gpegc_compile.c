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

#include "gpegc_private.h"
#include <gpeg/previous/lib/engine/gpege.h>

#undef ARRAY_FREE_ITEM
#define ARRAY_FREE_ITEM(itm) { \
  gpegc_matcherlist_free(&(itm.group)); \
  gpegc_matcherlist_free(&(itm.altgroup)); \
}
#undef ARRAY_EQUALS
#define ARRAY_EQUALS(a,b) (&a == &b)
MAKE_ARRAY_CODE(gpegc_matcher_t, gpegc_matcherlist_)

/*
#undef ARRAY_EQUALS
#define ARRAY_EQUALS(a,b) \
  (a.size == b.size && 0 == memcmp(a.data, b.data, b.size))
MAKE_ARRAY_CODE(vec_t, veclist_)
*/

static
unsigned char bytecode[] = {
  #include "grammar.h"
};

#define GENCALL(f) JOIN(PREVGEN, f)
#define JOIN(a, b) JOIN_AGAIN(a, b)
#define JOIN_AGAIN(a,b) a ## b

/**
 *
 */
GPEG_ERR_T gpegc_compile
  (
    vec_t* input,
    vec_t* output,
    vec_t* error,
    unsigned flags,
    char* slotmapfile
  )
{
  DEBUGFUNCTION
  ASSERT(input)
  ASSERT(output)

  gpege_t gpege = { 0 };
  gpege_ec_t ec = { 0 };
  gpeg_capturelist_t captures = { 0 };

  gpege.bytecode.data = bytecode;
  gpege.bytecode.size = sizeof(bytecode);

  ec.input = *input;

#ifdef _DEBUG
  gpege.debugger = gpege_debug_verbose;
#endif

  GPEG_CHECK(
    GENCALL(gpege_run)(&gpege, &ec),
    PROPAGATE
  );
  GPEG_CHECK(
    gpege_actions2captures(
      &(ec.input),
      &(ec.actions),
      &captures
    ),
    PROPAGATE
  );

  gpegc_t gpegc = { 0 };
  gpegc.output = output;
  gpegc.error = error;
  gpegc.rulecapture = (flags & GPEG_COMPILE_FLAG_RULECAPTURE);

  int e = grammar_process_node(&(captures.list[ 0 ]), &gpegc);

  if (gpegc.startrule) {
    vec_printf_insert(output, 0, "  call %s\n  end 0\n\n", gpegc.startrule);
  }

  if (e) {
    unsigned yx0[ 2 ];
    unsigned yx1[ 2 ];
    strxypos((char*)(ec.input.data), ec.input_offset, yx0);
    strxypos((char*)(ec.input.data), ec.input_offset_max, yx1);
    vec_printf(error,
      "Engine running error %d, at line %u, pos %u; max line %u, pos %u\n"
      , e, yx0[ 0 ], yx0[ 1 ], yx1[ 0 ], yx1[ 1 ]
    );
    return (GPEG_ERR_T){ .code = e };
  }

  if (slotmapfile) {
    FILE* slotmap = fopen(slotmapfile, "w+");
    for (unsigned i=0; i < gpegc.slotmap.count; i++) {
      fprintf(slotmap, "%s %u\n", gpegc.slotmap.keys[ i ], gpegc.slotmap.values[ i ]);
    }
    fclose(slotmap);
  }

  gpege_ec_free(&ec);
  gpeg_capturelist_free(&captures);

  return GPEG_OK;
}
