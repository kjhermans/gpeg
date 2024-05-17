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
#include <gpeg/lib/engine/gpege.h>

#include <gpeg/private/util/queryargs.h>
#include <gpeg/private/util/absorb_file.h>
#include <gpeg/private/util/strxypos.h>

/**
 *
 */
int main
  (int argc, char* argv[])
{
  char* inputfile = "-";
  char* bytecodefile = "-";
  char* slotmapfile = 0;
  char* labelmapfile = 0;
  char* arg;
  int displayactions = 0;
  vec_t input = { 0 };
  vec_t bytecode = { 0 };
  gpege_t gpege = { 0 };
  gpege_ec_t ec = { 0 };
  GPEG_ERR_T e = { 0 };

  if (queryargs(argc, argv, '?', "help", 0, 0, 0, 0) == 0) {
    fprintf(stderr,
"%s [options]\n"
"-? / -h     Display this message\n"
"-c <path>   Bytecode file\n"
"-i <path>   Data input file\n"
"-l <path>   Labelmap file\n"
"-m <path>   Slotmap file\n"
"-d          Start debugger\n"
"-v          Verbose (prepare for a lot of data on stderr)\n"
"-V          Super verbose (see above)\n"
"-t          Provide capture tree at the end\n"
"-x          Diligent (gather stats while running)\n"
"-f <path>   Fuzzer; produce fuzzed inputs in directory <path>\n"
"-I          Input is a string. Text position is displayed on error\n"
"-s <size>   Stack size\n"
"-e          Toggle endless loop checking (default on)\n"
"-M <n>      Set maximum number of executed instructions.\n"
      , argv[ 0 ]
    );
    return 0;
  }

  queryargs(argc, argv, 'i', "input", 0, 1, 0, &inputfile);
  queryargs(argc, argv, 'c', "bytecode", 0, 1, 0, &bytecodefile);
  if (queryargs(argc, argv, 't', "actions", 0, 0, 0, 0) == 0) {
    displayactions = 1;
  }
  if (queryargs(argc, argv, 'm', "slotmap", 0, 1, 0, &slotmapfile) == 0) {
  }
  if (queryargs(argc, argv, 'l', "labelmap", 0, 1, 0, &labelmapfile) == 0) {
  }

  if (absorb_file(inputfile, &(input.data), &(input.size))) {
    fprintf(stderr, "Could not absorb input file '%s'\n", inputfile);
    return -1;
  }
  if (absorb_file(bytecodefile, &(bytecode.data), &(bytecode.size))) {
    fprintf(stderr, "Could not absorb bytecode file '%s'\n", bytecodefile);
    return -2;
  }
  if (queryargs(argc, argv, 'v', "verbose", 0, 0, 0, 0) == 0) {
    gpege.debugger = gpege_debug_verbose;
  }
  if (queryargs(argc, argv, 'M', "maxinstructions", 0, 1, 0, &arg) == 0) {
    gpege.maxinstructions = strtoul(arg, 0, 10);
  }

  gpege.bytecode = bytecode;
  ec.input = &input;

  e = gpege_run(&gpege, &ec);
  if (e.code) {
    unsigned yx0[ 2 ];
    unsigned yx1[ 2 ];
    strxypos((char*)(ec.input->data), ec.input_offset, yx0);
    strxypos((char*)(ec.input->data), ec.input_offset_max, yx1);
    fprintf(stderr,
      "Engine running error %d, at line %u, pos %u; max line %u, pos %u\n"
      , e.code, yx0[ 0 ], yx0[ 1 ], yx1[ 0 ], yx1[ 1 ]
    );
    return e.code;
  }

  if (displayactions) {
    gpege_actionlist_output(&(ec.actions));
  }

  return 0;
}
