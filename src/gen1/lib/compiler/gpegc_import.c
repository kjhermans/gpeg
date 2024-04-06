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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "gpegc_private.h"

static
int gpegc_import_trypath
  (char* foundpath, unsigned size, char* search, char* path)
{
  struct stat s;

  snprintf(foundpath, size, "%s%s%s", (search ? search : ""), (search ? "/" : ""), path);
  if (stat(foundpath, &s) == 0 && (s.st_mode & S_IFMT) == S_IFREG) {
    return 0;
  }
  return ~0;
}

/**
 *
 */
GPEG_ERR_T gpegc_import
  (gpegc_t* gpegc, char* path)
{
  char foundpath[ 256 ] = { 0 };
  gpegc_compiler_t compiler = { 0 };

  if (gpegc_import_trypath(foundpath, sizeof(foundpath), 0, path)) {
    for (unsigned i=0; i < gpegc->compiler->import.count; i++) {
      if (gpegc_import_trypath(foundpath, sizeof(foundpath), gpegc->compiler->import.path[ i ], path) == 0) {
        break;
      }
    }
  }

  if (foundpath[ 0 ] == 0) {
    return GPEG_ERR_PATHNOTFOUND;
  }

  if (absorb_file(path, &(compiler.input.data), &(compiler.input.size))) {
    fprintf(stderr, "Could not absorb input file '%s'\n", path);
    return GPEG_ERR_PATHOPEN;
  }

  compiler.flags = gpegc->compiler->flags;
  GPEG_CHECK(gpegc_compile(&compiler), PROPAGATE);

  vec_append(&(gpegc->compiler->output), compiler.output.data, compiler.output.size);

  return GPEG_OK;
}
