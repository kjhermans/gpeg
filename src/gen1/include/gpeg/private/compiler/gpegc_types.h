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

#ifndef _GPEG_GEN1_GPEG_PRIVATE_COMPILER_TYPES_H_
#define _GPEG_GEN1_GPEG_PRIVATE_COMPILER_TYPES_H_

#include <gpeg/private/util/stringlist.h>
#include <gpeg/private/util/vec_t.h>



typedef struct gpegc_matcher gpegc_matcher_t;

MAKE_ARRAY_HEADER(gpegc_matcher_t, gpegc_matcherlist_)

struct gpegc_matcher
{

#define GPEGC_MATCH_ANY         1
#define GPEGC_MATCH_CHAR        2
#define GPEGC_MATCH_SET         3
#define GPEGC_MATCH_REFERENCE   4
#define GPEGC_MATCH_STRING      5
#define GPEGC_MATCH_ENDFORCE    6
#define GPEGC_MATCH_CAPTURE     7
#define GPEGC_MATCH_GROUP       8
#define GPEGC_MATCH_CHOICE      9
  unsigned                      type;

  union {
    unsigned char                 chr;
    struct {
      char*                         value;
      unsigned char                 quad[ 4 ];
      unsigned                      quadoffset;
    }                             string;
    unsigned                      capture;
    unsigned                      number;
    struct {
      int                           inverted;
      unsigned                      from;
      unsigned char                 bitmask[ 32 ];
    }                             set;
  }                             value;
  gpegc_matcherlist_t           group;
  gpegc_matcherlist_t           altgroup;

#define GPEGC_QUANT_INFINITE    -1
  int                           quantifier[ 2 ];

#define GPEGC_MODI_AND          1
#define GPEGC_MODI_NOT          2
  unsigned                      modifier;

  int                           caseinsensitive;
};



typedef struct
{
  stringlist_t          namespace;
  struct {
    char*                 name;
    gpegc_matcherlist_t   matchers;
  }                     currentrule;
  gpegc_matcher_t*      currentmatcher;
  gpegc_matcherlist_t*  currentmatcherlist;
  vec_t*                output;
  vec_t*                error;
  unsigned              ccount;
  unsigned              clabel;
  unsigned              cslot;
  int                   prefixgiven;
  int                   rulecapture;
  char*                 startrule;
}
gpegc_t;

#endif
