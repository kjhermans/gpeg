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

#include "gpegc_private.h"

/**
 * Sends a matcher's content to stderr,
 * potentially recursively (if it has children matchers).
 */
void gpegc_matcher_debug
  (gpegc_matcher_t* m, unsigned level)
{
  for (unsigned i=0; i < level; i++) {
    fprintf(stderr, "  ");
  }
  if (m->modifier) {
    if (m->modifier == 1) {
      fprintf(stderr, "not ");
    } else {
      fprintf(stderr, "and ");
    }
  }
  if (m->quantifier[ 0 ] || m->quantifier[ 1 ]) {
    fprintf(stderr, "^%d/%d: ", m->quantifier[ 0 ], m->quantifier[ 1 ]);
  }
  switch (m->type) {
  case GPEGC_MATCH_ANY:
    fprintf(stderr, "any\n"); break;
  case GPEGC_MATCH_CHAR:
    fprintf(stderr, "char %.2x\n", m->value.chr); break;
  case GPEGC_MATCH_SET:
    fprintf(stderr, "set\n"); break;
  case GPEGC_MATCH_REFERENCE:
    fprintf(stderr, "reference %s\n", m->value.string.value); break;
  case GPEGC_MATCH_STRING:
    fprintf(stderr, "string %s\n", m->value.string.value); break;
  case GPEGC_MATCH_ENDFORCE:
    fprintf(stderr, "end\n"); break;
  case GPEGC_MATCH_CAPTURE:
    fprintf(stderr, "capture\n");
    gpegc_matcherlist_debug(&(m->group), level+1);
    break;
  case GPEGC_MATCH_GROUP:
    fprintf(stderr, "group\n");
    gpegc_matcherlist_debug(&(m->group), level+1);
    break;
  case GPEGC_MATCH_CHOICE:
    fprintf(stderr, "choice\n");
    gpegc_matcherlist_debug(&(m->group), level+1);
    gpegc_matcherlist_debug(&(m->altgroup), level+1);
    break;
  }
}
