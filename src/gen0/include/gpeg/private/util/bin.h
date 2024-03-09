/**
 * This file is part of Oroszlan, a parsing and scripting environment

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
DISCLAIMED. IN NO EVENT SHALL Kees-Jan Hermans BE LIABLE FOR ANY
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

#ifndef _GPEGG_GEN4_UTIL_H_
#define _GPEGG_GEN4_UTIL_H_

#ifdef __unix__
#include <arpa/inet.h>
#else
#define ntohl(x) x
#define htonl(x) x
#endif


#define GET_32BIT_VALUE(mem,off) \
({ \
  const unsigned char* _mem = mem; \
  uint32_t _vl = \
    (_mem[ off   ] << 24) | \
    (_mem[ off+1 ] << 16) | \
    (_mem[ off+2 ] << 8) | \
     _mem[ off+3 ]; \
  _vl; \
})

#define SET_32BIT_VALUE(val) \
({ \
  uint32_t _vl, _og = val; \
  unsigned char* _mem = (unsigned char*)(&_vl); \
  _mem[ 0 ] = ( _og >>24 ) & 0xff; \
  _mem[ 1 ] = ( _og >>16 ) & 0xff; \
  _mem[ 2 ] = ( _og >>8 ) & 0xff; \
  _mem[ 3 ] = _og & 0xff; \
  _vl; \
})


#ifdef GET_32BIT_NWO
#undef GET_32BIT_NWO
#endif
#define GET_32BIT_NWO(mem,off) ({ uint32_t _vl; memcpy(&_vl,(mem)+(off),4); _vl=ntohl(_vl); _vl; })

#ifdef SET_32BIT_NWO
#undef SET_32BIT_NWO
#endif
#define SET_32BIT_NWO(mem,off,val) { uint32_t _vl = htonl(val); memcpy(((char*)mem) + off, &_vl, 4); }

#endif // defined _GPEGG_GEN4_UTIL_H_ ?
