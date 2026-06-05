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
#include <andy/util_functions.h>

extern int gpeg_debugger_off;

static
char* usage =
  "Usage: %s [options]\n"
  "Where options are:\n"
  "-? or -h   Display this text and exit.\n"
  "-i <path>  Specify input path.\n"
  "-c <path>  Specify output bytecode path.\n"
  "-o <path>  Specify output (captures) path.\n"
  "-H         Specify input is in hexadecimal.\n"
  "-L <path>  Specify input labelmap path.\n"
;

extern int gpeg_labelmap_load
  (vec_t* input, str2int_map_t* labelmap, vec_t* error);

extern str2int_map_t* gpeg_labelmap;

/**
 *
 */
int main
  (int argc, char* argv[])
{
  char defaultinput[] = "-";
  char* inputfile = defaultinput;
  char* bytecodefile = NULL;
  char* value = NULL;
  vec_t input = { 0 };
  vec_t bytecode = { 0 };
  gpege_result_t result = { 0 };
  str2int_map_t lm = { 0 };
  unsigned flags = 0;
  int e = 0;

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
  if (queryargs(argc, argv, 'H', "hex", 0, 0, 0, 0) == 0) {
    if (vec_hex_decode(&input)) {
      fprintf(stderr, "Hex decode error in input.\n");
      return ~0;
    }
  }
  if (queryargs(argc, argv, 'L', "labelmap", 0, 1, 0, &value) == 0) {
    vec_t lmdata = { 0 };
    if (absorb_file(value, &(lmdata.data), &(lmdata.size))) {
      fprintf(stderr, "Could not absorb labelmap file '%s'.\n", value);
      return ~0;
    }
    if (gpeg_labelmap_load(&lmdata, &lm, NULL)) {
      free(lmdata.data);
      fprintf(stderr, "Could not parse labelfile '%s.\n", value);
      return ~0;
    }
    free(lmdata.data);
    gpeg_labelmap = &lm;
  }
  flags |= GPEGE_FLG_DEBUG;
  flags |= GPEGE_FLG_DEBUGGER;
  gpeg_debugger_off = 0;
  if ((e = gpeg_engine_run(&bytecode, &input, flags, &result)) != 0) {
    char* errs[] = GPEGE_ERR_STRINGS;
    fprintf(stderr, "GPEG engine ended in error; %s.\n", errs[ e ]);
    return ~0;
  } else if (0 == result.success) {
    unsigned yx[ 2 ] = { 0 };
    e = strxypos((char*)(input.data), result.maxinputptr, yx);
    fprintf(stderr,
      "GPEG engine ended in no match.\n"
      "Furthest input position reached: %u, which is line %u, character %u.\n"
      , result.maxinputptr
      , yx[ 0 ]
      , yx[ 1 ]
    );
    return ~0;
  } else {
    if (queryargs(argc, argv, 'o', "output", 0, 1, 0, &value) == 0) {
      FILE* file;
      if (0 == strcmp(value, "-")) {
        file = stdout;
      } else {
        file = fopen(value, "w");
      }
      if (file) {
        for (unsigned i=0; i < result.captures.count; i++) {
          fprintf(file, "%u,%u,\""
                        , result.captures.list[ i ].reg
                        , result.captures.list[ i ].offset
          );
          for (unsigned j=0; j < result.captures.list[ i ].vec.size; j++) {
            unsigned char c = result.captures.list[ i ].vec.data[ j ];
            if (c >= 32 && c < 127) {
              if (c == '\"' || c == '\\') {
                fprintf(file, "\\%c", c);
              } else {
                fprintf(file, "%c", c);
              }
            } else {
              switch (c) {
              case '\n': fprintf(file, "\\n"); break;
              case '\r': fprintf(file, "\\r"); break;
              case '\t': fprintf(file, "\\t"); break;
              case '\v': fprintf(file, "\\v"); break;
              default: fprintf(file, "\\x%.2x", c); break;
              }
            }
          }
          fprintf(file, "\"\n");
        }
        fclose(file);
      } else {
        fprintf(stderr, "Couldn't open output file '%s' for writing.\n", value);
        return ~0;
      }
    }
    return 0;
  }
}
