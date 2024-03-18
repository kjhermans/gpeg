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

#include "gpegd_private.h"
#include "gpegd_instructions.h"

#define COMBINE(a, b) a##b
#define IGNOREPOSTHANDLER(ident) \
int COMBINE(handle_post_,ident)  \
  (                              \
    gpeg_capture_t* parent,      \
    unsigned index,              \
    gpeg_capture_t* capture,     \
    void* arg                    \
  )                              \
{                                \
  (void)parent;                  \
  (void)index;                   \
  (void)capture;                 \
  (void)arg;                     \
  return 0;                      \
}

int handle_any
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;

  vec_printf(gpegd->output, "%u: any\n", gpegd->offset);
  gpegd->offset += INSTR_LENGTH_ANY;

  return 0;
}

IGNOREPOSTHANDLER(any)

int handle_backcommit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned offset = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: backcommit %u\n", gpegd->offset, offset);
  gpegd->offset += INSTR_LENGTH_BACKCOMMIT;

  return 0;
}

IGNOREPOSTHANDLER(backcommit)

int handle_call
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned offset = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: call %u\n", gpegd->offset, offset);
  gpegd->offset += INSTR_LENGTH_CALL;

  return 0;
}

IGNOREPOSTHANDLER(call)

int handle_catch
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned offset = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: catch %u\n", gpegd->offset, offset);
  gpegd->offset += INSTR_LENGTH_CATCH;

  return 0;
}

IGNOREPOSTHANDLER(catch)

int handle_char
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned chr = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: char %.2x\n", gpegd->offset, chr);
  gpegd->offset += INSTR_LENGTH_CHAR;

  return 0;
}

IGNOREPOSTHANDLER(char)

int handle_closecapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned slot = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: closecapture %u\n", gpegd->offset, slot);
  gpegd->offset += INSTR_LENGTH_CLOSECAPTURE;

  return 0;
}

IGNOREPOSTHANDLER(closecapture)

int handle_commit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned offset = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: commit %u\n", gpegd->offset, offset);
  gpegd->offset += INSTR_LENGTH_COMMIT;

  return 0;
}

IGNOREPOSTHANDLER(commit)

int handle_condjump
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned p1 = ntohl(*((uint32_t*)(capture->data.data)));
  unsigned p2 = ntohl(*((uint32_t*)(capture->data.data + 4)));

  vec_printf(gpegd->output, "%u: condjump %u %u\n", gpegd->offset, p1, p2);
  gpegd->offset += INSTR_LENGTH_CONDJUMP;

  return 0;
}

IGNOREPOSTHANDLER(condjump)

int handle_counter
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned p1 = ntohl(*((uint32_t*)(capture->data.data)));
  unsigned p2 = ntohl(*((uint32_t*)(capture->data.data + 4)));

  vec_printf(gpegd->output, "%u: counter %u %u\n", gpegd->offset, p1, p2);
  gpegd->offset += INSTR_LENGTH_COUNTER;

  return 0;
}

IGNOREPOSTHANDLER(counter)

int handle_end
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned code = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: end %u\n", gpegd->offset, code);
  gpegd->offset += INSTR_LENGTH_END;

  return 0;
}

IGNOREPOSTHANDLER(end)

int handle_endisolate
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(endisolate)

int handle_endreplace
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(endreplace)

int handle_fail
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;

  vec_printf(gpegd->output, "%u: fail\n", gpegd->offset);
  gpegd->offset += INSTR_LENGTH_FAIL;

  return 0;
}

IGNOREPOSTHANDLER(fail)

int handle_failtwice
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;

  vec_printf(gpegd->output, "%u: failtwice\n", gpegd->offset);
  gpegd->offset += INSTR_LENGTH_FAILTWICE;

  return 0;
}

IGNOREPOSTHANDLER(failtwice)

int handle_intrpcapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(intrpcapture)

int handle_isolate
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(isolate)

int handle_jump
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned offset = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: jump %u\n", gpegd->offset, offset);
  gpegd->offset += INSTR_LENGTH_JUMP;

  return 0;
}

IGNOREPOSTHANDLER(jump)

int handle_maskedchar
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(maskedchar)

int handle_noop
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  
  gpegd_t* gpegd = arg;
  
  vec_printf(gpegd->output, "%u: noop\n", gpegd->offset);
  gpegd->offset += INSTR_LENGTH_NOOP;
  
  return 0;
}

IGNOREPOSTHANDLER(noop)

int handle_opencapture
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned slot = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: opencapture %u\n", gpegd->offset, slot);
  gpegd->offset += INSTR_LENGTH_OPENCAPTURE;

  return 0;
}

IGNOREPOSTHANDLER(opencapture)

int handle_partialcommit
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned offset = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: partialcommit %u\n", gpegd->offset, offset);
  gpegd->offset += INSTR_LENGTH_PARTIALCOMMIT;

  return 0;
}

IGNOREPOSTHANDLER(partialcommit)

int handle_quad
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned char* quad = capture->data.data;

  vec_printf(gpegd->output,
    "%u: quad %.2x%.2x%.2x%.2x\n"
    , gpegd->offset
    , quad[ 0 ], quad[ 1 ], quad[ 2 ], quad[ 3 ]
  );
  gpegd->offset += INSTR_LENGTH_QUAD;

  return 0;
}

IGNOREPOSTHANDLER(quad)

int handle_range
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(range)

int handle_replace
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(replace)

int handle_ret
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;

  vec_printf(gpegd->output, "%u: ret\n", gpegd->offset);
  gpegd->offset += INSTR_LENGTH_RET;

  return 0;
}

IGNOREPOSTHANDLER(ret)

int handle_set
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned char* set = capture->data.data;

  vec_printf(gpegd->output, "%u: set ", gpegd->offset);
  for (unsigned i=0; i < 32; i++) {
    vec_printf(gpegd->output, "%.2x", set[ i ]);
  }
  vec_printf(gpegd->output, "\n");
  gpegd->offset += INSTR_LENGTH_SET;
  return 0;
}

IGNOREPOSTHANDLER(set)

int handle_skip
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned length = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: skip %u\n", gpegd->offset, length);
  gpegd->offset += INSTR_LENGTH_SKIP;

  return 0;
}

IGNOREPOSTHANDLER(skip)

int handle_span
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(span)

int handle_testany
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(testany)

int handle_testchar
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(testchar)

int handle_testquad
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(testquad)

int handle_testset
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;
  return 0;
}

IGNOREPOSTHANDLER(testset)

int handle_trap
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;

  vec_printf(gpegd->output, "%u: trap\n", gpegd->offset);
  gpegd->offset += INSTR_LENGTH_TRAP;

  return 0;
}

IGNOREPOSTHANDLER(trap)

int handle_var
  (
    gpeg_capture_t* parent,
    unsigned index,
    gpeg_capture_t* capture,
    void* arg
  )
{
  (void)parent;
  (void)index;
  (void)capture;
  (void)arg;

  gpegd_t* gpegd = arg;
  unsigned varno = ntohl(*((uint32_t*)(capture->data.data)));

  vec_printf(gpegd->output, "%u: var %u\n", gpegd->offset, varno);
  gpegd->offset += INSTR_LENGTH_VAR;

  return 0;
}

IGNOREPOSTHANDLER(var)
