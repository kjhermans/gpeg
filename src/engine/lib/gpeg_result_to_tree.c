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

MAKE_ARRAY_CODE(gpege_node_t*, gpege_nodelist_);

/**
 * Simple bubble sort
 */
static
void gpege_nodelist_sort
  (gpege_nodelist_t* list)
{
  int sorted = 0;
  while (!sorted) {
    sorted = 1;
//    for (unsigned i=0; i < list->count-1; i++) {
    for (unsigned i=list->count-2; i != (unsigned)-1; i--) {
      gpege_node_t* node0 = list->list[ i ];
      gpege_node_t* node1 = list->list[ i+1 ];
      if (
           (node0->offset > node1->offset) || (
             node0->offset == node1->offset && (
               node0->vec.size < node1->vec.size || (
                 node0->vec.size == node1->vec.size &&
                 node0->type > node1->type
               )
             )
           )
         )
      {
        gpege_node_t* tmp = list->list[ i ];
        list->list[ i ] = list->list[ i+1 ];
        list->list[ i+1 ] = tmp;
        sorted = 0;
      }
    }
  }
}

static
void gpege_nodelist_tree
  (gpege_nodelist_t* list)
{
  int sorted = 0;
  while (!sorted) {
    sorted = 1;
    for (unsigned i=0; i < list->count-1; i++) {
      gpege_node_t* node0 = list->list[ i ];
      gpege_node_t* node1 = list->list[ i+1 ];
      if (node1->offset >= node0->offset &&
          node1->offset + node1->vec.size <= node0->offset + node0->vec.size)
      {
        gpege_nodelist_rem(list, i+1, NULL);
        gpege_nodelist_push(&(node0->children), node1);
        gpege_nodelist_tree(&(node0->children));
        sorted = 0;
        break;
      }
    }
  }
}

gpege_node_t* gpeg_result_to_tree
  (const gpege_result_t* captures)
{
  gpege_node_t* result = calloc(1, sizeof(gpege_node_t));

//  result->vec.size = (1<<20); // #define some constant please
  for (unsigned i=0; i < captures->captures.count; i++) {
    gpege_capture_t* cap = &(captures->captures.list[ i ]);
    gpege_node_t* node = calloc(1, sizeof(gpege_node_t));

    node->vec = vec_copy_(cap->vec);
    node->offset = cap->offset;
    node->type = cap->reg;
    gpege_nodelist_push(&(result->children), node);
  }
  gpege_nodelist_sort(&(result->children));
  gpege_nodelist_tree(&(result->children));
//  result->vec.size = 0;
  return result;
}

void gpeg_result_free
  (gpege_result_t* result)
{
  if (result->flags & GPEGE_FLG_COPYCAPTURES) {
    for (unsigned i=0; i < result->captures.count; i++) {
      free(result->captures.list[ i ].vec.data);
    }
  }
  free(result->captures.list);
  result->captures.list = 0;
  result->captures.count = 0;
}

static
void gpeg_node_debug_
  (const gpege_node_t* node, unsigned indent)
{
  for (unsigned i=0; i < indent; i++) { fprintf(stderr, " "); }
  fprintf(stderr, "%u: %u: %u: ", node->type, node->offset, node->vec.size);
  if (node->vec.data) {
    for (unsigned i=0; i < node->vec.size; i++) {
      char c = node->vec.data[ i ];
      if (c >= 32 && c < 127) {
        fprintf(stderr, "%c", c);
      } else {
        fprintf(stderr, ".");
      }
    }
  } else {
    fprintf(stderr, "null");
  }
  fprintf(stderr, "\n");
  for (unsigned i=0; i < node->children.count; i++) {
    gpeg_node_debug_(node->children.list[ i ], indent + 1);
  }
}

/**
 * Logs the contents of a parse (sub) tree to stderr.
 */
void gpeg_node_debug
  (const gpege_node_t* node)
{
  gpeg_node_debug_(node, 0);
}

/**
 *
 */
void gpeg_node_remove
  (gpege_node_t* node, unsigned type, int recursive, int force)
{
  for (unsigned i=0; i < node->children.count; i++) {
    gpege_node_t* child = node->children.list[ i ];
    if (recursive) {
      gpeg_node_remove(child, type, recursive, force);
    }
    if (child->type == type) {
      if (force || child->children.count == 0) {
        gpeg_node_free(child);
        if (i == node->children.count - 1) {
          --(node->children.count);
          return;
        } else {
          memmove(
            &(node->children.list[i]),
            &(node->children.list[i+1]),
            sizeof(gpege_node_t*) * (node->children.count - (i + 1))
          );
          --(node->children.count);
          --i;
        }
      }
    }
  }
}

void gpeg_result_remove_slot
  (gpege_result_t* result, unsigned type)
{
  for (unsigned i=0; i < result->captures.count; i++) {
    if (result->captures.list[ i ].reg == type) {
      if (result->flags & GPEGE_FLG_COPYCAPTURES) {
        free(result->captures.list[ i ].vec.data);
      }
      gpege_caplist_rem(&(result->captures), i, NULL);
      --i;
    }
  }
}

void gpeg_node_callback
  (
    gpege_node_t* node,
    unsigned type,
    int(*fnc)(gpege_node_t*,unsigned,unsigned,vec_t*,void*),
    void* arg
  )
{
  for (unsigned i=0; i < node->children.count; i++) {
    gpege_node_t* child = node->children.list[ i ];
    if (child->type == type) {
      child->fnc = fnc;
      child->arg = arg;
    }
    gpeg_node_callback(child, type, fnc, arg);
  }
}

static
int gpeg_node_run_
  (gpege_node_t* parent, vec_t* parentvec)
{
  for (unsigned i=0; i < parent->children.count; i++) {
    gpege_node_t* child = parent->children.list[ i ];
    vec_t vec = { 0 };
    int r;

    if (child->fnc) {
      switch (r = child->fnc(child, GPEG_FNC_PRENODE, i, &vec, child->arg)) {
      case 0:
        break;
      case GPEGE_ERR_NOFURTHERPROC:
        if (vec.data) { free(vec.data); }
        continue;
      default:
        return r;
      }
    }
    if (parent->fnc) {
      CHECK(parent->fnc(parent, GPEG_FNC_PRECHILD, i, parentvec, parent->arg));
    }
    CHECK(gpeg_node_run_(child, &vec));
    if (parent->fnc) {
      CHECK(parent->fnc(parent, GPEG_FNC_POSTCHILD, i, parentvec, parent->arg));
    }
    if (child->fnc) {
      CHECK(child->fnc(child, GPEG_FNC_POSTNODE, i, &vec, child->arg));
    }
    if (vec.data) { free(vec.data); }
  }
  return 0;
}

/**
 *
 */
int gpeg_node_run
  (gpege_node_t* parent)
{
  return gpeg_node_run_(parent, NULL);
}

/**
 *
 */
void gpeg_node_free
  (gpege_node_t* node)
{
  for (unsigned i=0; i < node->children.count; i++) {
    gpeg_node_free(node->children.list[ i ]);
  }
  free(node->children.list);
  memset(&(node->children), 0, sizeof(node->children));
  if (node->vec.data) { free(node->vec.data); }
  free(node);
}
