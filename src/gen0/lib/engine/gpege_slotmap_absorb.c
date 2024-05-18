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

static
unsigned char bytecode[] = {
  #include "simap.h"
};

/**
 *
 */
int gpege_slotmap_absorb
  (gpege_t* gpege, char* slotmaptext)
{
  gpege_t simape = { 0 };
  gpege_ec_t simapec = { 0 };
  gpeg_capturelist_t captures = { 0 };
  vec_t input = { slotmaptext, strlen(slotmaptext) };

  simape.bytecode.data = bytecode;
  simape.bytecode.size = sizeof(bytecode);
  simapec.input = &input;

  gpege_run(&simape, &simapec);
  simap_grammar_process_node(&(captures.list[ 0 ]), gpege);

  return 0;
}

/**
 *
 */
int gpege_slotmap_absorb_file
  (gpege_t* gpege, char* path)
{
  char* slotmaptext = 0;
  unsigned l = 0;

  if (absorb_file(path, (unsigned char**)&slotmaptext, &l)) {
    return ~0; // TODO: Return relevant error code.
  }
  if (gpege_slotmap_absorb(gpege, slotmaptext)) {
    free(slotmaptext);
    return ~0; // TODO: Return relevant error code.
  }
  free(slotmaptext);

  return 0;
}
