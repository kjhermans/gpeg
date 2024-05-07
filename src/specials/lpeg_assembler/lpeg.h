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

#ifndef _GPEG_LPEG_H_
#define _GPEG_LPEG_H_

typedef enum
{
  IAny, /* if no char, fail */
  IChar,  /* if char != aux, fail */
  ISet,  /* if char not in buff, fail */
  ITestAny,  /* in no char, jump to 'offset' */
  ITestChar,  /* if char != aux, jump to 'offset' */
  ITestSet,  /* if char not in buff, jump to 'offset' */
  ISpan,  /* read a span of chars in buff */
  IBehind,  /* walk back 'aux' characters (fail if not possible) */
  IRet,  /* return from a rule */
  IEnd,  /* end of pattern */
  IChoice,  /* stack a choice; next fail will jump to 'offset' */
  IJmp,  /* jump to 'offset' */
  ICall,  /* call rule at 'offset' */
  IOpenCall,  /* call rule number 'key' (must be closed to a ICall) */
  ICommit,  /* pop choice and jump to 'offset' */
  IPartialCommit,  /* update top choice to current position and jump */
  IBackCommit,  /* "fails" but jump to its own 'offset' */
  IFailTwice,  /* pop one choice and then fail */
  IFail,  /* go back to saved state on choice and jump to saved offset */
  IGiveup,  /* internal use */
  IFullCapture,  /* complete capture of last 'off' chars */
  IOpenCapture,  /* start a capture */
  ICloseCapture,
  ICloseRunTime
}
lpeg_opcode_t;

#define LPEG_INSTR_LENGTH_ANY           4
#define LPEG_INSTR_LENGTH_BACKCOMMIT    8
#define LPEG_INSTR_LENGTH_CALL          8
#define LPEG_INSTR_LENGTH_CHOICE        8
#define LPEG_INSTR_LENGTH_CHAR          4
#define LPEG_INSTR_LENGTH_COMMIT        8
#define LPEG_INSTR_LENGTH_END           4
#define LPEG_INSTR_LENGTH_FAIL          4
#define LPEG_INSTR_LENGTH_FAILTWICE     4
#define LPEG_INSTR_LENGTH_JUMP          8
#define LPEG_INSTR_LENGTH_PARTIALCOMMIT 8
#define LPEG_INSTR_LENGTH_RET           4
#define LPEG_INSTR_LENGTH_OPENCAPTURE   4
#define LPEG_INSTR_LENGTH_CLOSECAPTURE  4
#define LPEG_INSTR_LENGTH_SET           36
#define LPEG_INSTR_LENGTH_SPAN          36
#define LPEG_INSTR_LENGTH_TESTANY       8
#define LPEG_INSTR_LENGTH_TESTCHAR      8
#define LPEG_INSTR_LENGTH_              4

#include <inttypes.h>

typedef union
{
  struct {
    uint8_t               code;
    uint8_t               aux;
    uint16_t              key;
  }                     instr;
  uint32_t              offset;
  uint8_t               buffer[ 1 ];
}
lpeg_instr_t;

#endif
