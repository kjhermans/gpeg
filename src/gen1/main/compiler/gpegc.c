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

#include <gpeg/lib/gpeg/gpeg.h>
#include <gpeg/lib/compiler/gpegc.h>

#include <gpeg/private/util/queryargs.h>
#include <gpeg/private/util/absorb_file.h>
#include <gpeg/private/util/strxypos.h>

/**
 * Compiler main function.
 * Interprets command line arguments,
 * calls the compiler library main function (gpegc_compile),
 * and processes its results.
 */
int main
  (int argc, char* argv[])
{
  char* inputfile = "-";
  char* outputfile = "-";
  gpegc_compiler_t compiler = { 0 };
  FILE* out;
  GPEG_ERR_T e;
  int rulecapture = 0;

  if (queryargs(argc, argv, '?', "help", 0, 0, 0, 0) == 0) {
    fprintf(stderr,
"%s [options]\n"
"Options:\n"
"-i <path>  Take path as input (default '-' or stdin).\n"
"-o <path>  Take path as output (default '-' or stdout).\n"
"-b         Incorporate the assembler and emit bytecode at -o <path>.\n"
"-a <path>  Emit bytecode at -o <path>, assembly at -a <path> (implies -b).\n"
"-C         Generate default captures for each rule.\n"
"-t         Generate traps around rules.\n"
"-G <path>  Generate C code for the parse tree.\n"
"-m <path>  Output slotmap file.\n"
"-M <path>  Output slotmap.h file.\n"
"-I <path>  Add a directory path for inclusion when using imports.\n"
"-?         Print this help and exit.\n"
      , argv[ 0 ]
    );
    return 0;
  }
  queryargs(argc, argv, 'i', "input", 0, 1, 0, &inputfile);
  queryargs(argc, argv, 'o', "output", 0, 1, 0, &outputfile);
  queryargs(argc, argv, 'm', "slotmap", 0, 1, 0, &(compiler.slotmap));
  queryargs(argc, argv, 'M', "slotmaph", 0, 1, 0, &(compiler.slotmaph));
  if (queryargs(argc, argv, 'C', "defaultcaptures", 0, 0, 0, 0) == 0) {
    rulecapture = 1;
  }

  if (absorb_file(inputfile, &(compiler.input.data), &(compiler.input.size))) {
    fprintf(stderr, "Could not absorb input file '%s'\n", inputfile);
    return -1;
  }
  compiler.flags = (rulecapture ? GPEGC_FLAG_GENCAPTURES : 0);
  e = gpegc_compile(&compiler);
  if (e.code) {
    fprintf(stderr, "Compiler error code %d: %s", e.code, (char*)(compiler.error.data));
    return e.code;
  }

  if (0 == strcmp(outputfile, "-")) {
    out = stdout;
  } else {
    if ((out = fopen(outputfile, "w+")) == NULL) {
      fprintf(stderr, "Could not open output file '%s'\n", outputfile);
      return -1;
    }
  }
  fprintf(out, "%s", (char*)(compiler.output.data));

  if (compiler.error.data) {
    free(compiler.error.data);
  }
  free(compiler.output.data);
  free(compiler.input.data);

  return 0;
}
