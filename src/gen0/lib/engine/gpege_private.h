/**
 * This file is part of GPEG, a parsing environment

Copyright (c) 2023, Kees-Jan Hermans <kees.jan.hermans@gmail.com>
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

#ifndef _GEN0_GPEGE_PRIVATE_H_
#define _GEN0_GPEGE_PRIVATE_H_

#include <gpeg/lib/engine/gpege_types.h>

#include <gpeg/private/engine/lib.h>
#include <gpeg/private/util/util.h>

#define OPCODE_FAILURE          0xffffff

#define GPEGE_STACK_CATCH       6
#define GPEGE_STACK_CALL        9

#define GPEGE_DATA_IN_SET(set,chr) (set[chr/8]&(1<<(chr%8)))

#define MODE_RUNNING            0
#define MODE_SETTINGS           1
extern unsigned gpege_dbgncrs_width;
extern unsigned gpege_dbgncrs_height;
extern unsigned gpege_dbgncrs_mode;
extern unsigned gpege_dbgncrs_noinputlines;
extern unsigned gpege_dbgncrs_rununtil;
extern int      gpege_dbgncrs_stepover;
extern unsigned gpege_dbgncrs_nostacklines;
extern unsigned gpege_dbgncrs_stacksize;
extern unsigned gpege_dbgncrs_nocapturelines;
extern int      gpege_dbgncrs_exp_input;
extern int      gpege_dbgncrs_exp_stack;
extern int      gpege_dbgncrs_exp_captures;

#endif
