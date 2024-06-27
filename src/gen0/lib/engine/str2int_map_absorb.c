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
#include "simap.slotmap.h"

static
unsigned char bytecode[] = {
  #include "simap.h"
};

/**
 *
 */
int str2int_map_absorb
  (str2int_map_t* map, char* maptext)
{
  gpege_t simape = { 0 };
  gpege_ec_t simapec = { 0 };
  gpeg_capturelist_t captures = { 0 };
  vec_t input = { (unsigned char*)maptext, strlen(maptext) };

  simape.bytecode.data = bytecode;
  simape.bytecode.size = sizeof(bytecode);
  simapec.input = &input;

  GPEG_ERR_T e = gpege_run(&simape, &simapec);
  e = gpege_actions2captures(
    simapec.input,
    &(simapec.actions),
    &captures
  );

  if (e.code) {
    fprintf(stderr, "Error loading map.\n");
    return ~0;
  }

  gpeg_capturelist_remove(&captures, SLOT_S);
  gpeg_capturelist_remove(&captures, SLOT_MULTILINECOMMENT);
  gpeg_capturelist_remove(&captures, SLOT_COMMENT);

  int ee = simap_grammar_process_node(&(captures.list[ 0 ]), map);

  return ee;
}

/**
 *
 */
int str2int_map_absorb_file
  (str2int_map_t* str2int_map, char* path)
{
  char* maptext = 0;
  unsigned l = 0;

  if (absorb_file(path, (unsigned char**)&maptext, &l)) {
    return ~0; // TODO: Return relevant error code.
  }
  if (str2int_map_absorb(str2int_map, maptext)) {
    free(maptext);
    return ~0; // TODO: Return relevant error code.
  }
  free(maptext);

  return 0;
}
