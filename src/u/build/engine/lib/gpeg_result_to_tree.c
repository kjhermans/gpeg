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

#include <gpeg/engine/lib.h>

static
void gpeg_captures2nodes
  (const gpege_caplist_t* captures, unsigned i, gpege_node_t* parent)
{
  unsigned lastoff = parent->offset;

  for (; i < captures->count && captures->list[ i ].offset
           < parent->offset + parent->vec.size; i++)
  {
    gpege_capture_t* cap = &(captures->list[ i ]);
    if (cap->offset >= lastoff) {
      gpege_node_t* child = calloc(1, sizeof(gpege_node_t));
      parent->children = realloc(
                           parent->children,
                           sizeof(gpege_node_t*) * (parent->nchildren + 1));
      child->type = cap->reg;
      child->offset = cap->offset;
      vec_appendv(&(child->vec), &(cap->vec));
      gpeg_captures2nodes(captures, i+1, child);
      parent->children[ (parent->nchildren)++ ] = child;
      lastoff = cap->offset + cap->vec.size;
    }
  }
}

/**
 * Transforms a result list with captures to a tree based structure,
 * which may be easier to use.
 */
gpege_node_t* gpeg_result_to_tree
  (const gpege_result_t* result)
{
  gpege_node_t* tree = calloc(1, sizeof(gpege_node_t));
  tree->vec.size = (1<<20); // TODO: Replace with some defined constant

  gpeg_captures2nodes(&(result->captures), 0, tree);
  tree->vec.size = 0;
  return tree;
}

static
void gpeg_result_debug_
  (const gpege_node_t* node, unsigned indent)
{
  for (unsigned i=0; i < indent; i++) { fprintf(stderr, " "); }
  fprintf(stderr, "%u: %u: %u: ", node->type, node->offset, node->vec.size);
  for (unsigned i=0; i < node->vec.size; i++) {
    char c = node->vec.data[ i ];
    if (c >= 32 && c < 127) {
      fprintf(stderr, "%c", c);
    } else {
      fprintf(stderr, ".");
    }
  }
  fprintf(stderr, "\n");
  for (unsigned i=0; i < node->nchildren; i++) {
    gpeg_result_debug_(node->children[ i ], indent + 1);
  }
}

/**
 * Logs the contents of a parse (sub) tree to stderr.
 */
void gpeg_result_debug
  (const gpege_node_t* node)
{
  gpeg_result_debug_(node, 0);
}

/**
 *
 */
void gpeg_result_remove
  (gpege_node_t* node, unsigned type, int recursive, int force)
{
  for (unsigned i=0; i < node->nchildren; i++) {
    gpege_node_t* child = node->children[ i ];
    if (recursive) {
      gpeg_result_remove(child, type, recursive, force);
    }
    if (child->type == type) {
      if (force || child->nchildren == 0) {
        gpeg_result_free(child);
        if (i == node->nchildren - 1) {
          --(node->nchildren);
          return;
        } else {
          memmove(
            &(node->children[i]),
            &(node->children[i+1]),
            sizeof(gpege_node_t*) * (node->nchildren - (i + 1))
          );
          --(node->nchildren);
          --i;
        }
      }
    }
  }
}

void gpeg_result_prefunc
  (
    gpege_node_t* node,
    unsigned type,
    int(*fn)(gpege_node_t*,vec_t*,void*),
    void* arg
  )
{
  for (unsigned i=0; i < node->nchildren; i++) {
    gpege_node_t* child = node->children[ i ];
    if (child->type == type) {
      child->prefunc = fn;
      child->prearg = arg;
    }
    gpeg_result_prefunc(child, type, fn, arg);
  }
}

void gpeg_result_postfunc
  (
    gpege_node_t* node,
    unsigned type,
    int(*fn)(gpege_node_t*,vec_t*,void*),
    void* arg
  )
{
  for (unsigned i=0; i < node->nchildren; i++) {
    gpege_node_t* child = node->children[ i ];
    if (child->type == type) {
      child->postfunc = fn;
      child->postarg = arg;
    }
    gpeg_result_postfunc(child, type, fn, arg);
  }
}

int gpeg_result_run
  (gpege_node_t* node)
{
  for (unsigned i=0; i < node->nchildren; i++) {
    gpege_node_t* child = node->children[ i ];
    vec_t vec = { 0 };
    if (child->prefunc) {
      CHECK(child->prefunc(child, &vec, child->prearg));
    }
    CHECK(gpeg_result_run(child));
    if (child->postfunc) {
      CHECK(child->postfunc(child, &vec, child->postarg));
    }
    if (vec.data) { free(vec.data); }
  }
  return 0;
}

/**
 *
 */
void gpeg_result_free
  (gpege_node_t* node)
{
  for (unsigned i=0; i < node->nchildren; i++) {
    gpeg_result_free(node->children[ i ]);
  }
  free(node->children);
  if (node->vec.data) { free(node->vec.data); }
  free(node);
}
