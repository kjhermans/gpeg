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
#include <andy/queryargs.h>
#include <andy/absorb_file.h>
#include <andy/vec_t.h>

static
char* usage =
  "Usage: %s [options]\n"
  "Where options are:\n"
  "-? or -h   Display this text and exit.\n"
  "-i <path>  Specify input path.\n"
  "-o <path>  Speficy output path.\n"
  "-C         Treat every rule as an automatic capture regio.\n"
  "-M <path>  Specify slotmap header file.\n"
;

/**
 *
 */
int main
  (int argc, char* argv[])
{
  char defaultinput[] = "-";
  char defaultoutput[] = "-";
  char* inputfile = defaultinput;
  char* outputfile = defaultoutput;
  char* value;
  vec_t input = { 0 };
  vec_t output = { 0 };
  int fdout = 1;
  unsigned flags = 0;

  if (queryargs(argc, argv, '?', "help", 0, 0, 0, 0) == 0
      || queryargs(argc, argv, 'h', "help", 0, 0, 0, 0) == 0)
  {
    printf(usage, argv[ 0 ]);
    exit(0);
  }
  if (queryargs(argc, argv, 'i', "input", 0, 1, 0, &value) == 0) {
    inputfile = value;
  }
  if (queryargs(argc, argv, 'o', "output", 0, 1, 0, &value) == 0) {
    outputfile = value;
  }
  if (queryargs(argc, argv, 'C', "autocapture", 0, 0, 0, 0) == 0) {
    flags |= GPEGC_FLG_AUTOCAPTURE;
  }
  if (absorb_file(inputfile, &(input.data), &(input.size))) {
    fprintf(stderr, "Could not absorb file '%s'\n", inputfile);
    return ~0;
  }

  if (gpeg_compile(&input, &output, flags)) {
    fprintf(stderr, "Compilation error.\n");
    return ~0;
  }
  if (0 != strcmp(outputfile, "-")) {
    fdout = open(outputfile, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fdout == -1) {
      return ~0;
    }
  }
  if (write_insistent(fdout, output.data, output.size, 0)) {
    fprintf(stderr, "Assembly writing error: %d\n", errno);
  }
  close(fdout);

  return 0;
}
