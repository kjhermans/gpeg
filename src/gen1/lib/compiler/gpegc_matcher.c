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

static
void gpegc_matcher_char
  (gpegc_t* gpegc, gpegc_matcher_t* matcher, char c)
{
  if (matcher->caseinsensitive
      && ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
  {
    //..
  } else {
    if (matcher->value.string.quadoffset == 4) {
      vec_printf(&(gpegc->compiler->output), "  quad %.2x%.2x%.2x%.2x\n"
                                , matcher->value.string.quad[ 0 ]
                                , matcher->value.string.quad[ 1 ]
                                , matcher->value.string.quad[ 2 ]
                                , matcher->value.string.quad[ 3 ]
      );
      matcher->value.string.quadoffset = 0;
    }
    matcher->value.string.quad[ matcher->value.string.quadoffset ] = c;
    ++(matcher->value.string.quadoffset);
  }
}

static
void gpegc_matcher_string
  (gpegc_t* gpegc, gpegc_matcher_t* matcher)
{
  matcher->value.string.quadoffset = 0;
  for (unsigned i=0; i < strlen(matcher->value.string.value); i++) {
    char c = matcher->value.string.value[ i ];
    switch (c) {
    case '\\':
      switch (matcher->value.string.value[ ++i ]) {
      case 'a': gpegc_matcher_char(gpegc, matcher, 7); break;
      case 'b': gpegc_matcher_char(gpegc, matcher, 8); break;
      case 't': gpegc_matcher_char(gpegc, matcher, 9); break;
      case 'n': gpegc_matcher_char(gpegc, matcher, 10); break;
      case 'v': gpegc_matcher_char(gpegc, matcher, 11); break;
      case 'f': gpegc_matcher_char(gpegc, matcher, 12); break;
      case 'r': gpegc_matcher_char(gpegc, matcher, 13); break;
      case 'x':
        gpegc_matcher_char(gpegc, matcher, hexcodon(
          matcher->value.string.value[ i+1 ],
          matcher->value.string.value[ i+2 ]
        ));
        i += 2;
        break;
      default:
        gpegc_matcher_char(gpegc, matcher, matcher->value.string.value[ ++i ]);
        break;
      }
      break;
    default:
      gpegc_matcher_char(gpegc, matcher, c);
    }
  }
  if (matcher->value.string.quadoffset) {
    if (matcher->value.string.quadoffset == 4) {
      vec_printf(&(gpegc->compiler->output), "  quad %.2x%.2x%.2x%.2x\n"
                                , matcher->value.string.quad[ 0 ]
                                , matcher->value.string.quad[ 1 ]
                                , matcher->value.string.quad[ 2 ]
                                , matcher->value.string.quad[ 3 ]
      );
    } else {
      for (unsigned i=0; i < matcher->value.string.quadoffset; i++) {
        vec_printf(&(gpegc->compiler->output), "  char %.2x\n"
                                  , matcher->value.string.quad[ i ]
        );
      }
    }
  }
}

static
GPEG_ERR_T gpegc_matcher_
  (gpegc_t* gpegc, gpegc_matcher_t* matcher)
{
  switch (matcher->type) {
  case GPEGC_MATCH_ANY:
    vec_printf(&(gpegc->compiler->output), "  any\n");
    break;
  case GPEGC_MATCH_CHAR:
    vec_printf(&(gpegc->compiler->output), "  char %.2x\n", matcher->value.chr);
    break;
  case GPEGC_MATCH_REFERENCE:
    vec_printf(&(gpegc->compiler->output), "  call %s\n", matcher->value.string.value);
    break;
  case GPEGC_MATCH_VARIABLE:
    {
      unsigned slot;
      if (str2int_map_get(
            &(gpegc->slotmap),
            &(matcher->value.string.value[1]),
            &slot) == 0)
      {
        vec_printf(&(gpegc->compiler->output), "  var %u\n", slot);
      } else {
        vec_printf(&(gpegc->compiler->error),
          "Could not resolve reference '%s'\n"
          , matcher->value.string.value
        );
        return GPEG_ERR_REFERENCE;
      }
    }
    break;
  case GPEGC_MATCH_STRING:
    gpegc_matcher_string(gpegc, matcher);
    break;
  case GPEGC_MATCH_SET:
    vec_printf(&(gpegc->compiler->output), "  set ");
    for (unsigned i=0; i < 32; i++) {
      unsigned char byt = matcher->value.set.bitmask[ i ];
      if (matcher->value.set.inverted) {
        byt = ~byt;
      }
      vec_printf(&(gpegc->compiler->output), "%.2x", byt);
    }
    vec_printf(&(gpegc->compiler->output), "\n");
    break;
  case GPEGC_MATCH_ENDFORCE:
    vec_printf(&(gpegc->compiler->output), "  end %u\n", matcher->value.number);
    break;
  case GPEGC_MATCH_CAPTURE:
    vec_printf(&(gpegc->compiler->output), "  opencapture %u\n"
                              , matcher->value.capture
    );
    GPEG_CHECK(gpegc_matcherlist(gpegc, &(matcher->group)), PROPAGATE);
    vec_printf(&(gpegc->compiler->output), "  closecapture %u\n"
                              , matcher->value.capture
    );
    break;
  case GPEGC_MATCH_GROUP:
    GPEG_CHECK(gpegc_matcherlist(gpegc, &(matcher->group)), PROPAGATE);
    break;
  case GPEGC_MATCH_CHOICE:
    {
      unsigned label1 = ++(gpegc->clabel);
      unsigned label2 = ++(gpegc->clabel);
      vec_printf(&(gpegc->compiler->output), "  catch __L%u\n"
                                , label1
      );
      GPEG_CHECK(gpegc_matcherlist(gpegc, &(matcher->group)), PROPAGATE);
      vec_printf(&(gpegc->compiler->output), "  commit __L%u\n"
                                "__L%u:\n"
                                , label2
                                , label1
      );
      GPEG_CHECK(gpegc_matcherlist(gpegc, &(matcher->altgroup)), PROPAGATE);
      vec_printf(&(gpegc->compiler->output), "__L%u:\n"
                                , label2
      );
    }
    break;
  }
  return GPEG_OK;
}

static
GPEG_ERR_T gpegc_matcher_to_endless
  (gpegc_t* gpegc, gpegc_matcher_t* matcher)
{
  unsigned label1 = ++(gpegc->clabel);
  unsigned label2 = ++(gpegc->clabel);

  vec_printf(&(gpegc->compiler->output), "  catch __L%u\n"
                            "__L%u:\n"
                            , label1
                            , label2
  );
  GPEG_CHECK(gpegc_matcher_(gpegc, matcher), PROPAGATE);
  vec_printf(&(gpegc->compiler->output), "  partialcommit __L%u\n"
                            "__L%u:\n"
                            , label2
                            , label1
  );
  return GPEG_OK;
}

static
GPEG_ERR_T gpegc_matcher_to_count
  (gpegc_t* gpegc, gpegc_matcher_t* matcher, int count)
{
  unsigned label1 = ++(gpegc->clabel);
  unsigned counter = ++(gpegc->ccount);

  vec_printf(&(gpegc->compiler->output), "  counter %u %d\n"
                            "__L%u:\n"
                            , counter
                            , count
                            , label1
  );
  GPEG_CHECK(gpegc_matcher_(gpegc, matcher), PROPAGATE);
  vec_printf(&(gpegc->compiler->output), "  condjump %u __L%u\n"
                            , counter
                            , label1
  );
  return GPEG_OK;
}

static
GPEG_ERR_T gpegc_matcher_optional
  (gpegc_t* gpegc, gpegc_matcher_t* matcher, int count)
{
  if (count == 1) {
    unsigned label1 = ++(gpegc->clabel);
  
    vec_printf(&(gpegc->compiler->output), "  catch __L%u\n"
                              , label1
    );
    GPEG_CHECK(gpegc_matcher_(gpegc, matcher), PROPAGATE);
    vec_printf(&(gpegc->compiler->output), "  commit __NEXT__\n"
                              "__L%u:\n"
                              , label1
    );
  } else {
    unsigned label1 = ++(gpegc->clabel);
    unsigned label2 = ++(gpegc->clabel);
    unsigned counter = ++(gpegc->ccount);
  
    vec_printf(&(gpegc->compiler->output), "  catch __L%u\n"
                              "  counter %u %d\n"
                              "__L%u:\n"
                              , label1
                              , counter
                              , count
                              , label2
    );
    GPEG_CHECK(gpegc_matcher_(gpegc, matcher), PROPAGATE);
    vec_printf(&(gpegc->compiler->output), "  partialcommit __NEXT__\n"
                              "  condjump %u __L%u\n"
                              "  commit __NEXT__\n"
                              "__L%u:\n"
                              , counter
                              , label2
                              , label1
    );
  }
  return GPEG_OK;
}

static
GPEG_ERR_T gpegc_matcher_modified
  (gpegc_t* gpegc, gpegc_matcher_t* matcher)
{
  unsigned label1 = ++(gpegc->clabel);
  unsigned label2 = ++(gpegc->clabel);

  switch (matcher->modifier) {
  case GPEGC_MODI_AND:
    vec_printf(&(gpegc->compiler->output), "  catch __L%u\n"
                              , label1
    );
    GPEG_CHECK(gpegc_matcher_(gpegc, matcher), PROPAGATE);
    vec_printf(&(gpegc->compiler->output), "  backcommit __L%u\n"
                              "__L%u:\n"
                              "  fail\n"
                              "__L%u:\n"
                              , label2
                              , label1
                              , label2
    );
    break;
  case GPEGC_MODI_NOT:
    vec_printf(&(gpegc->compiler->output), "  catch __L%u\n"
                              , label1
    );
    GPEG_CHECK(gpegc_matcher_(gpegc, matcher), PROPAGATE);
    vec_printf(&(gpegc->compiler->output), "  failtwice\n"
                              "__L%u:\n"
                              , label1
    );
    break;
  }
  return GPEG_OK;
}

static
GPEG_ERR_T gpegc_matcher_quantified
  (gpegc_t* gpegc, gpegc_matcher_t* matcher)
{
  int* q = matcher->quantifier;

  switch (q[ 0 ]) {
  case 0:
    switch (q[ 1 ]) {
    case -1:
      return gpegc_matcher_to_endless(gpegc, matcher);
    case 0:
      return gpegc_matcher_(gpegc, matcher);
    default:
      return gpegc_matcher_optional(gpegc, matcher, q[ 1 ]);
    }
    break;
  case 1:
    GPEG_CHECK(gpegc_matcher_(gpegc, matcher), PROPAGATE);
    switch (q[ 1 ]) {
    case -1:
      return gpegc_matcher_to_endless(gpegc, matcher);
    default:
      if (q[ 0 ] < q[ 1 ]) {
        return gpegc_matcher_optional(gpegc, matcher, q[ 1 ] - 1);
      }
    }
    break;
  default:
    GPEG_CHECK(gpegc_matcher_to_count(gpegc, matcher, q[ 0 ]), PROPAGATE);
    switch (q[ 1 ]) {
    case -1:
      return gpegc_matcher_to_endless(gpegc, matcher);
    default:
      if (q[ 0 ] > q[ 1 ]) {
        vec_printf(&(gpegc->compiler->error),
          "Quantifier range error %d > %d.\n", q[ 0 ], q[ 1 ]
        );
        return GPEG_ERR_QUANTIFIER;
      } else if (q[ 0 ] < q[ 1 ]) {
        int diff = q[ 1 ] - q[ 0 ];
        return gpegc_matcher_optional(gpegc, matcher, diff);
      }
    }
  }
  return GPEG_OK;
}

/**
 * Main access function to render a matcher structure into
 * gpeg assembly.
 *
 * \param gpegc    Compilation data structure.
 * \param matcher  Matcher to be translated into assembly.
 *
 */
GPEG_ERR_T gpegc_matcher
  (gpegc_t* gpegc, gpegc_matcher_t* matcher)
{
  if (matcher->modifier) {
    return gpegc_matcher_modified(gpegc, matcher);
  } else {
    return gpegc_matcher_quantified(gpegc, matcher);
  }
}
