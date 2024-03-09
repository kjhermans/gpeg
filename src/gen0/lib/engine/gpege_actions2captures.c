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

#include "gpege_private.h"

static
GPEG_ERR_T gpege_actions2captures_
  (
    vec_t* input,
    gpege_actionlist_t* actions,
    unsigned start,
    unsigned end,
    gpeg_capturelist_t* captures
  )
{
  DEBUGFUNCTION
  ASSERT(input)
  ASSERT(actions)
  ASSERT(captures)

  for (unsigned i = start; i < end; i++) {
    gpege_action_t* action = gpege_actionlist_getptr(actions, i);
    if (action->type == GPEGE_ACTION_OPENCAPTURE) {
      unsigned substart = i;
      unsigned level = 1;
      for (++i; i < end; i++) {
        gpege_action_t* action2 = gpege_actionlist_getptr(actions, i);
        if (action2->type == GPEGE_ACTION_OPENCAPTURE) {
          ++level;
        } else if (action2->type == GPEGE_ACTION_CLOSECAPTURE) {
          if (--level == 0) {
            gpeg_capture_t capture = { 0 }, * captureptr;
            capture.type = action->slot;
            capture.offset = action->input_offset;
            capture.data.size = action2->input_offset - action->input_offset;
            capture.data.data = malloc(capture.data.size + 1);
            memcpy(
              capture.data.data,
              input->data + capture.offset,
              capture.data.size
            );
            capture.data.data[ capture.data.size ] = 0;
            captureptr = gpeg_capturelist_push(captures, capture);
            GPEG_CHECK(
              gpege_actions2captures_(
                input,
                actions,
                substart + 1,
                i,
                &(captureptr->children)
              ),
              PROPAGATE
            );
            break;
          }
        }
      }
    }
  }
  return GPEG_OK;
}

/**
 * Converts the action list of an engine to a list of captures.
 */
GPEG_ERR_T gpege_actions2captures
  (vec_t* input, gpege_actionlist_t* actions, gpeg_capturelist_t* captures)
{
  DEBUGFUNCTION
  ASSERT(input)
  ASSERT(actions)
  ASSERT(captures)

  GPEG_CHECK(gpege_actions2captures_(input, actions, 0, actions->count, captures), PROPAGATE);

  return GPEG_OK;
}
