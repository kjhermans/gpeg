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

/**
 * Counts the number of lines in [string], until [pos] is reached.
 * Calculates the x,y position inside [string], of [pos].
 * Returns the x,y position of a position in a string.
 *
 * \param string  Zero-terminated string, preferably longer than [pos] bytes.
 * \param pos     Position inside the string.
 * \param vector  Contains the line (off-by-one) [0], and position on that
 *                line (off-by-one) [1], on successful return.
 *
 * \returns       Zero on success (pos is inside string), or non-zero on error.
 *
 * Note: badly named function. Should be stryxpos().
 */
int strxypos
  (char* string, unsigned pos, unsigned vector[ 2 ])
{
  unsigned i = 0;

  vector[ 0 ] = 1;
  vector[ 1 ] = 1;
  while (i < pos) {
    switch (string[ i++ ]) {
    case '\n':
      ++(vector[ 0 ]);
      vector[ 1 ] = 0;
      break;
    case 0:
      return ~0;
    }
    ++(vector[ 1 ]);
  }
  return 0;
}
