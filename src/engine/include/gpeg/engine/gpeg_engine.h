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

#ifndef _GPEGU_ENGINE_H_
#define _GPEGU_ENGINE_H_

#include <andy/vec_list_t.h>

/**
 * END
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 0 0 0|  zero |             endcode                           |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * RANGE
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 0 0 1|  zero |    bitmask    |     from      |     until     |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * LIMIT
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 0 1 0|         |O|E|    S    |           register            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * O : 1 = set limit, 0, unset limit (pop limit stack).
 * E : 1 = big endian interpretation, 0 = little endian.
 * S : +1 = size of integer being interpreted in bits.
 *
 * CALL
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 0 1 1|  zero         |             offset                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * RET
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 1 0 0|                      zero                             |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * CATCH
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 1 0 1|  zero         |             offset                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * COMMIT
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 1 1 0|  zero         |             offset                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * BACKCOMMIT
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |0 1 1 1|  zero         |             offset                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * PARTIALCOMMIT
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 0 0 0|  zero         |             offset                    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * FAIL
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 0 0 1|                      zero                             |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * FAILTWICE
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 0 1 0|                      zero                             |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * VAR
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 0 1 1|                       |           register            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * OPENCAPTURE
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 1 0 0|                       |           register            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * CLOSECAPTURE
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 1 0 1|                       |           register            |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * COUNTER
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 1 1 0|    counter    |                value                  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 * CONDJUMP
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |1 1 1 1|     counter   |               offset                  |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */

#define GPEG_INSTR_SIZE 4

typedef enum
{
  OP_END = 0,
  OP_RANGE,
  OP_LIMIT,
  OP_CALL,
  OP_RET,
  OP_CATCH,
  OP_COMMIT,
  OP_BACKCOMMIT,
  OP_PARTIALCOMMIT,
  OP_FAIL,
  OP_FAILTWICE,
  OP_VAR,
  OP_OPENCAPTURE,
  OP_CLOSECAPTURE,
  OP_COUNTER,
  OP_CONDJUMP
}
gpege_opcode_t;

typedef struct
{
  unsigned          offset;
  uint16_t          reg;
  vec_t             vec;
}
gpege_capture_t;

MAKE_ARRAY_HEADER(gpege_capture_t, gpege_caplist_)

typedef struct
{
  int               success;
  uint32_t          endcode;
  uint32_t          maxinputptr;
  gpege_caplist_t   captures;
}
gpege_result_t;

#define GPEGE_ERR_OVERFLOW      1
#define GPEGE_ERR_STACKEMPTY    2
#define GPEGE_ERR_STACKELT      3
#define GPEGE_ERR_CAPREG        4
#define GPEGE_ERR_VARIABLE      5
#define GPEGE_ERR_MAXINSTR      6
#define GPEGE_ERR_COUNTER       7
#define GPEGE_ERR_LIMIT         8

#define GPEGE_FLG_COPYCAPTURES  (1<<0)
#define GPEGE_FLG_DEBUG         (1<<1)
#define GPEGE_FLG_DEBUGGER      (1<<2)

/**
 * Runs the GPEG engine on \p input, using \p bytecode, and fills \p result.
 * Returns zero on success, non zero on error.
 *
 * Notice that a non-match returns zero, but leaves result->success zero.
 * A match returns zero, and leaves result->success non-zero, fills
 * result->endcode, and - if captures have been defined in the grammar -
 * fills result->captures.
 *
 * Depending on whether \p flags have the GPEGE_FLG_COPYCAPTURES bit set,
 * the vectors inside captures->list[ i ].vec will be malloc()'d or not,
 * and it is up to the caller in that case to free() them.
 * If any regions have been captured, then the caller must always free()
 * the result->captures.list member variable.
 *
 * \param bytecode The bytecode, for example as produced by the GPEG assembler.
 * \param input    The input to match the bytecode, or not.
 * \param flags    Any of the GPEGE_FLG_* bits.
 * \param result   On success (when zero is returned), contains relevant
 *                 data to the caller. Note that a non-match is also considered
 *                 a success.
 * \returns        Zero on success, or non-zero on error.
 *
 * Errors are:
 *
 * - GPEGE_ERR_STACKEMPTY  When the stack shouldn't be empty, but is.
 * - GPEGE_ERR_STACKELT    When the expected type isn't on top of the stack.
 * - GPEGE_ERR_VARIABLE    Referenced variable cannot be found.
 * - GPEGE_ERR_OVERFLOW    Instruction pointer outside of bytecode buffer.
 * - GPEGE_ERR_CAPREG      Capture region not found.
 * - GPEGE_ERR_MAXINSTR    Too many instructions executed.
 * - GPEGE_ERR_COUNTER     Too many counters required.
 */
extern
int gpeg_engine_run
  (
    const vec_t* bytecode,
    const vec_t* input,
    const unsigned flags,
    gpege_result_t* result
  )
  __attribute__ ((warn_unused_result));

#define GPEGE_MAX_INSTRUCTIONS    (1<<24)
#define GPEGE_MAX_STACKSIZE       (1<<16)
#define GPEGE_MAX_COUNTERS        (1<<16)

typedef struct gpege_node gpege_node_t;

struct gpege_node
{
  vec_t            vec;
  unsigned         offset;
  unsigned         type;
  gpege_node_t**   children;
  unsigned         nchildren;
  int            (*fnc)(gpege_node_t*,unsigned,unsigned,vec_t*,void*);
  void*            arg;
  uint8_t          aux[ 32 ]; // this one is for you
};

extern
gpege_node_t* gpeg_result_to_tree
  (
    const gpege_result_t* result
  )
  __attribute__ ((warn_unused_result));

extern
void gpeg_result_debug
  (const gpege_node_t* node);

extern
void gpeg_result_remove
  (gpege_node_t* node, unsigned type, int recursive, int force);

#define GPEG_FNC_PRENODE      1
#define GPEG_FNC_PRECHILD     2
#define GPEG_FNC_POSTCHILD    3
#define GPEG_FNC_POSTNODE     4

extern
void gpeg_result_callback
  (
    gpege_node_t* node,
    unsigned type,
    int(*fnc)(gpege_node_t*,unsigned,unsigned,vec_t*,void*),
    void* arg
  );

extern
int gpeg_result_run
  (gpege_node_t* node);

extern
void gpeg_result_free
  (gpege_node_t* node);

#endif
