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

#include <gpeg/engine/lib.h>

#include "labelmap_bytecode.h"
#include "labelmap_slotmap.h"

extern int gpeg_debugger_off;

static
int gpeg_labelmap_label
  (gpege_node_t* node, unsigned phase, unsigned i, vec_t* vec, void* arg)
{
  (void)i;
  (void)vec;
  str2int_map_t* labelmap = arg;

  if (phase == GPEG_FNC_PRENODE) {
    char* label = (char*)(node->children[ 0 ]->vec.data);
    unsigned offset = strtoul((char*)(node->children[ 1 ]->vec.data), 0, 10);
    str2int_map_put(labelmap, label, offset);
  }
  return 0;
}

int gpeg_labelmap_load
  (vec_t* input, str2int_map_t* labelmap, vec_t* error)
{
  DEBUGFUNCTION
  ASSERT(input)
  ASSERT(labelmap)

  vec_t bytecode = { (unsigned char*)labelmap_byc, labelmap_byc_len };
  gpege_result_t result = { 0 };
  int e = 0;

  gpeg_debugger_off = 1;
  if ((e = gpeg_engine_run(&bytecode, input, 0, &result)) != 0) {
    if (error) {
      char* errs[] = GPEGE_ERR_STRINGS;
      vec_printf(error,
        "Labelmap parser engine ended in error; %s.\n", errs[ e ]
      );
    }
    RETURN_ERR(GPEGE_ERR_PARSER);
  } else if (!(result.success)) {
    if (error) {
      unsigned yx[ 2 ] = { 0 };
      e = strxypos((char*)(input->data), result.maxinputptr, yx);
      vec_printf(error,
        "Labelmap parser engine ended in no match;\n"
        "Furthest input position reached: %u, which is line %u, character %u.\n"
        , result.maxinputptr
        , yx[ 0 ]
        , yx[ 1 ]
      );
    }
    RETURN_ERR(GPEGE_ERR_PARSER);
  }

  gpege_node_t* tree = gpeg_result_to_tree(&result);
  gpeg_node_callback(tree, SLOT_LABEL, gpeg_labelmap_label, labelmap);
  CHECK(gpeg_node_run(tree));

  return 0;
}
