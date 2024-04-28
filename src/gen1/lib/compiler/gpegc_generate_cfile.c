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

#include <stdio.h>

#include "gpegc_private.h"

/**
 *
 */
GPEG_ERR_T gpegc_generate_cfile
  (gpegc_t* gpegc, char* path)
{
  FILE* file = fopen(path, "w+");

  fprintf(file,
    "#include <gpeg/lib/gpeg/gpeg_capturelist.h>\n"
    "\n"
    "#ifdef _DEBUG\n"
    "#include <stdio.h>\n"
    "#endif\n"
    "\n"
    "extern int grammar_process_node(gpeg_capture_t*, void*);\n"
    "static int do_node(gpeg_capture_t*, unsigned, gpeg_capture_t*, void*);\n"
    "\n"
  );
  for (unsigned i=0; i < gpegc->slotmap.count; i++) {
    char* slotname = gpegc->slotmap.keys[ i ];
    //unsigned slot = gpegc->slotmap.values[ i ];
    fprintf(file,
      "extern int handle_%s(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);\n"
      "extern int handle_post_%s(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);\n"
      , slotname
      , slotname
    );
  }
  fprintf(file,
    "\n"
    "int grammar_process_node\n"
    "  (\n"
    "    gpeg_capture_t* capture,\n"
    "    void* ptr\n"
    "  )\n"
    "{\n"
    "  return do_node(0, 0, capture, ptr);\n"
    "}\n"
    "\n"
    "static\n"
    "int do_node\n"
    "  (\n"
    "    gpeg_capture_t* parent,\n"
    "    unsigned index,\n"
    "    gpeg_capture_t* capture,\n"
    "    void* ptr\n"
    "  )\n"
    "{\n"
    "  int e;\n"
    "  unsigned indices[ %u ] = { 0 };\n"
    "\n"
    "  switch (capture->type) {\n"
    , gpegc->slotmap.count
  );
  for (unsigned i=0; i < gpegc->slotmap.count; i++) {
    char* slotname = gpegc->slotmap.keys[ i ];
    unsigned slot = gpegc->slotmap.values[ i ];
    fprintf(file,
      "  case %u:\n"
      "    {\n"
      "      ++indices[ %u ];\n"
      "      if ((e = handle_%s(parent, index, capture, ptr)) != 0) {\n"
      "        return e;\n"
      "      }\n"
      "      for (unsigned i=0; i < capture->children.count; i++) {\n"
      "        if ((e = do_node(capture, indices[ %u ], &(capture->children.list[ i ]), ptr)) != 0) {\n"
      "          return e;\n"
      "        }\n"
      "      }\n"
      "      if ((e = handle_post_%s(parent, index, capture, ptr)) != 0) {\n"
      "        return e;\n"
      "      }\n"
      "    }\n"
      "    break;\n"
      , slot
      , slot
      , slotname
      , slot
      , slotname
    );
  }
  fprintf(file,
    "  }\n"
    "  return 0;\n"
    "}\n"
  );
  fclose(file);
  return GPEG_OK;
}
