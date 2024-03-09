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

#include <gpeg/lib/gpeg/gpeg_capturelist.h>

#undef ARRAY_EQUALS
#define ARRAY_EQUALS(a,b) (&a == &b)
MAKE_ARRAY_CODE(gpeg_capture_t, gpeg_capturelist_)

static
void gpeg_capturelist_debug_
  (gpeg_capturelist_t* list, unsigned level);

static
void gpeg_capture_debug_
  (gpeg_capture_t* capture, unsigned level)
{
  for (unsigned i=0; i < level; i++) {
    fprintf(stderr, "  ");
  }
  fprintf(stderr, "@%.6u '", capture->offset);
  for (unsigned i=0; i < capture->data.size; i++) {
    unsigned char c = capture->data.data[ i ];
    if (c >= 32 && c < 127) {
      fprintf(stderr, "%c", c);
    } else {
      fprintf(stderr, "\\x%.2x", c);
    }
  }
  fprintf(stderr, "', len=%u, type=%u\n", capture->data.size, capture->type);
  gpeg_capturelist_debug_(&(capture->children), level+1);
}

static
void gpeg_capturelist_debug_
  (gpeg_capturelist_t* list, unsigned level)
{
  for (unsigned i=0; i < list->count; i++) {
    gpeg_capture_debug_(&(list->list[ i ]), level);
  }
}

void gpeg_capturelist_debug
  (gpeg_capturelist_t* list)
{
  gpeg_capturelist_debug_(list, 0);
}

void gpeg_capture_debug
  (gpeg_capture_t* capture)
{
  gpeg_capture_debug_(capture, 0);
}

void gpeg_capturelist_remove
  (gpeg_capturelist_t* list, unsigned type)
{
  for (unsigned i=0; i < list->count; i++) {
    gpeg_capture_t* child = gpeg_capturelist_getptr(list, i);
    if (child->type == type && child->children.count == 0) {
      gpeg_capturelist_rem(list, i--, 0);
    } else if (child->children.count != 0) {
      gpeg_capturelist_remove(&(child->children), type);
    }
  }
}
