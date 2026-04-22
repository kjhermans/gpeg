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
#include <gpeg/engine/release.h>
#include <andy/queryargs.h>
#include <andy/absorb_file.h>
#include <andy/vec_t.h>

static
char* usage =
  "Usage: %s [options]\n"
  "Where options are:\n"
  "-? or -h   Display this text and exit.\n"
  "-i <path>  Specify input path.\n"
  "-c <path>  Specify bytecode path.\n"
#ifdef _DEBUG
  "-v         Verbose mode (debug version only).\n"
  "-d         Start debugger (debug version only).\n"
#endif
;

/**
 *
 */
int main
  (int argc, char* argv[])
{
  char defaultinput[] = "-";
  char* inputfile = defaultinput;
  char* bytecodefile = 0;
  char* value = 0;
  vec_t input = { 0 };
  vec_t bytecode = { 0 };
  gpege_result_t result = { 0 };
  unsigned flags = 0;

#ifdef _DEBUG
  fprintf(stderr, "gpege DEBUG version, release %-.*s\n", release_len, release);
#endif

  if (queryargs(argc, argv, '?', "help", 0, 0, 0, 0) == 0
      || queryargs(argc, argv, 'h', "help", 0, 0, 0, 0) == 0)
  {
    printf(usage, argv[ 0 ]);
    exit(0);
  }
  if (queryargs(argc, argv, 'i', "input", 0, 1, 0, &value) == 0) {
    inputfile = value;
  }
  if (absorb_file(inputfile, &(input.data), &(input.size))) {
    fprintf(stderr, "Could not absorb file '%s'\n", inputfile);
    return ~0;
  }
  if (queryargs(argc, argv, 'c', "bytecode", 0, 1, 0, &value) == 0) {
    bytecodefile = value;
  }
  if (NULL == bytecodefile) {
    fprintf(stderr, "No bytecode file specified.\n");
    return ~0;
  }
  if (absorb_file(bytecodefile, &(bytecode.data), &(bytecode.size))) {
    fprintf(stderr, "Could not absorb file '%s'\n", bytecodefile);
    return ~0;
  }
#ifdef _DEBUG
  if (queryargs(argc, argv, 'v', "verbose", 0, 0, 0, 0) == 0) {
    flags |= GPEGE_FLG_DEBUG;
  }
  if (queryargs(argc, argv, 'd', "debug", 0, 0, 0, 0) == 0) {
    flags |= GPEGE_FLG_DEBUGGER;
  }
#endif
  if (gpeg_engine_run(&bytecode, &input, flags, &result)) {
    fprintf(stderr, "GPEG engine ended in error.\n");
    return ~0;
  } else if (0 == result.success) {
    fprintf(stderr, "GPEG engine ended in no match.\n");
    return ~0;
  } else {
    return 0;
  }
}
