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
#include <stdlib.h>

#include <gpeg/private/util/absorb_file.h>
#include <gpeg/private/util/queryargs.h>

#include "lpeg.h"

static
char setstr[ 128 ];

static
inline char* setstring
  (unsigned char* buf)
{
  char hex[] = "0123456789abcdef";

  for (unsigned i=0; i < 32; i++) {
    setstr[ i*2 ] = hex[ buf[ i ] >> 4 ];
    setstr[ i*2 + 1 ] = hex[ buf[ i ] & 0xf ];
  }
  setstr[ 64 ] = 0;

  return setstr;
}

/**
 *
 */
int main
  (int argc, char* argv[])
{
  char* inputfile;
  unsigned char* buf = 0;
  unsigned buflen = 0;
  unsigned offset = 0;

  if (queryargs(argc, argv, 'i', "input", 0, 1, 0, &inputfile)) {
    fprintf(stderr, "No input file specified.\n");
    exit(1);
  }
  if (absorb_file(inputfile, &buf, &buflen)) {
    fprintf(stderr, "Could not absorb input file '%s'\n", inputfile);
    exit(2);
  }

  while (offset < buflen) {
    lpeg_instr_t* instr = (lpeg_instr_t*)(&(buf[ offset ]));
    fprintf(stdout, "%u: ", offset/4);
    offset += 4;
    switch (instr->instr.code) {
    case IAny:
      fprintf(stdout, "any\n");
      break;
    case IChar:
      fprintf(stdout, "char %.2x -- '%c'\n"
                      , instr->instr.aux
                      , (instr->instr.aux > 31 && instr->instr.aux < 127)
                        ? instr->instr.aux : 0x3f
      );
      break;
    case ISet:
      {
        fprintf(stdout, "set %s\n", setstring(&(buf[ offset ])));
        offset += 32;
      }
      break;
    case ITestAny:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "testany %d\n", param);
        offset += 4;
      }
      break;
    case ITestChar:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "testchar %.2x %d\n", instr->instr.aux, param);
        offset += 4;
      }
      break;
    case ITestSet:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "testset %s %d\n"
                        , setstring(&(buf[ offset + 4 ])), param);
        offset += 36;
      }
      break;
    case ISpan:
      {
        fprintf(stdout, "span %s\n", setstring(&(buf[ offset ])));
        offset += 32;
      }
      break;
    case IBehind:
      break;
    case IRet:
      fprintf(stdout, "ret\n");
      break;
    case IEnd:
      fprintf(stdout, "end\n");
      break;
    case IChoice:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "choice %d\n", param);
        offset += 4;
      }
      break;
    case IJmp:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "jmp %d\n", param);
        offset += 4;
      }
      break;
    case ICall:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "call %d\n", param);
        offset += 4;
      }
      break;
    case IOpenCall:
      break;
    case ICommit:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "commit %d\n", param);
        offset += 4;
      }
      break;
    case IPartialCommit:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "partialcommit %d\n", param);
        offset += 4;
      }
      break;
    case IBackCommit:
      {
        int32_t param = *((int32_t*)(&(buf[ offset ])));
        param = ((offset - 4) / 4) + param;
        fprintf(stdout, "backcommit %d\n", param);
        offset += 4;
      }
      break;
    case IFailTwice:
      fprintf(stdout, "failtwice\n");
      break;
    case IFail:
      fprintf(stdout, "fail\n");
      break;
    case IGiveup:
      break;
    case IFullCapture:
      break;
    case IOpenCapture:
      fprintf(stdout, "opencapture\n");
      break;
    case ICloseCapture:
      fprintf(stdout, "closecapture\n");
      break;
    case ICloseRunTime:
      break;
    default:
      fprintf(stdout, "-- unknown opcode %u\n", instr->instr.code);
    }
  }

  return 0;
}
