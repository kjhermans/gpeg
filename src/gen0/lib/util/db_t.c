/**
 * Extremely simple database implementation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <util/db_t.h>
#include <util/devmacroes.h>

static
int __db_read_at
  (const int fd, const off_t offset, void* buf, const size_t size)
{
  DEBUGFUNCTION
  if (size) {
    if (lseek(fd, offset, SEEK_SET) != offset) { RETURN_ERR(DB_ERROR) }
    if (read(fd, buf, size) != (ssize_t)size) { RETURN_ERR(DB_ERROR) }
  }
  RETURN_OK
}

static
int __db_write_at
  (const int fd, const off_t offset, const void* buf, const size_t size)
{
  DEBUGFUNCTION
  if (size) {
    if (lseek(fd, offset, SEEK_SET) != offset) { RETURN_ERR(DB_ERROR) }
    if (write(fd, buf, size) != (ssize_t)size) { RETURN_ERR(DB_ERROR) }
  }
  RETURN_OK
}

static
int __db_write_at_end
  (const int fd, off_t* offset, void* buf, const size_t size)
{
  DEBUGFUNCTION
  if ((*offset = lseek(fd, 0, SEEK_END)) == -1) { RETURN_ERR(DB_ERROR) }
  if (write(fd, buf, size) != (ssize_t)size) { RETURN_ERR(DB_ERROR) }
  RETURN_OK
}

static
int __db_tuple_read
  (const db_t* db, const off_t offset, struct db_tuple* tuple)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(tuple)

  unsigned t_enc[ 2 ];

  memset(tuple, 0, sizeof(struct db_tuple));
  CHECK(__db_read_at(db->fd, offset, t_enc, sizeof(t_enc)));
  tuple->flags = t_enc[ 0 ] >> DB_KEYBITS;
  tuple->keysize = t_enc[ 0 ] & DB_KEYMASK;
  tuple->valuesize = t_enc[ 1 ];
  if (tuple->flags & DB_FLAG_DEL) { RETURN_OK }
  if (read(db->fd, tuple->key, tuple->keysize) != tuple->keysize) {
    RETURN_ERR(DB_ERROR)
  }
  tuple->key[ tuple->keysize ] = 0;

  RETURN_OK
}

static
int __db_tuple_write
  (const db_t* db, const off_t offset, const struct db_tuple* tuple)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(tuple)

  unsigned t_enc[ 2 ];
  size_t l = strlen(tuple->key);

  if (lseek(db->fd, offset, SEEK_SET) != offset) {
    RETURN_ERR(DB_ERROR)
  }
  t_enc[ 0 ] = (tuple->flags << DB_KEYBITS) | (l & DB_KEYMASK);
  t_enc[ 1 ] = tuple->valuesize;
  if (write(db->fd, t_enc, sizeof(t_enc)) != sizeof(t_enc)) {
    RETURN_ERR(DB_ERROR)
  }
  if (write(db->fd, tuple->key, l) != (ssize_t)l) {
    RETURN_ERR(DB_ERROR)
  }

  RETURN_OK
}

static
int __db_ixnode_read
  (const db_t* db, const off_t offset, struct db_index_node* node)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(node)
  ASSERT((offset % sizeof(struct db_index_node)) == 0)

  CHECK(__db_read_at(db->ix, offset, node, sizeof(struct db_index_node)));

  RETURN_OK
}

static
int __db_ixnode_write
  (const db_t* db, const off_t offset, const struct db_index_node* node)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(node)
  ASSERT((offset % sizeof(struct db_index_node)) == 0)

  CHECK(__db_write_at(db->ix, offset, node, sizeof(struct db_index_node)));

  RETURN_OK
}

static
int __db_compare
  (const char* key1, const char* key2, const int partial)
{
  DEBUGFUNCTION
  ASSERT(key1)
  ASSERT(key2)

  int c;

  DBGMSG("Comparing '%s' '%s'\n", key1, key2);
  if (partial) {
    c = strncmp(key1, key2, strlen(key1));
  } else {
    c = strcmp(key1, key2);
  }
  if (c < 0) { return -1; }
  if (c > 0) { return 1; }
  return 0;
}

#ifdef _DEBUG
static
void __db_path_debug
  (struct db_path* path)
{
  fprintf(stderr,
    "PATH (at %p, length %u, searchlevel %u, found %d, head %p):\n"
    , path, path->length, path->search_level, path->found, path->head
  );
  for (unsigned i=0; i < path->length; i++) {
    fprintf(stderr,
      "Path elt %u:\n"
      "- Offset: %lu\n"
      "- Tuple_offset: %u\n"
      "- Node level: %u\n"
      "- Tuple key: %s\n"
      "- Tuple value size: %u\n"
      , i
      , path->elts[ i ].node_offset
      , path->elts[ i ].node.tuple_offset
      , path->elts[ i ].node.level
      , path->elts[ i ].tuple.key
      , path->elts[ i ].tuple.valuesize
    );
    for (unsigned j=0; j < path->elts[ i ].node.level; j++) {
      fprintf(stderr, "- Next (%u): %u\n", j, path->elts[ i ].node.next[ j ]);
    }
  }
  fprintf(stderr, "/PATH\n");
}
#endif

static
int __db_index_traverse_initialize
  (const db_t* db, struct db_path* path)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(path)

  off_t next = 0;
  unsigned l = 0;

  memset(path, 0, sizeof(*path));
  CHECK(__db_ixnode_read(db, 0, &(path->elts[ 0 ].node)));
  ++(path->length); /* Head node loaded. */

  l = path->elts[ 0 ].node.level;
  while (l && path->elts[ 0 ].node.next[ l-1 ] == 0) { l--; }
  if (l) { path->search_level = l-1; }
  next = path->elts[ 0 ].node.next[ path->search_level ];

  if (next) {
    path->elts[ 1 ].node_offset = next;
    CHECK(__db_ixnode_read(db, next, &(path->elts[ 1 ].node)));
    CHECK(
      __db_tuple_read(
        db, path->elts[ 1 ].node.tuple_offset, &(path->elts[ 1 ].tuple)
      )
    );
    ++(path->length);
  }

  path->head = &(path->elts[ path->length-1 ]);

  RETURN_OK
}

static
int __db_index_traverse_back
  (struct db_path* path)
{
  DEBUGFUNCTION
  ASSERT(path)

  if (path->length < 2) { RETURN_ERR(DB_ERR_UNSTABLE); }
  --(path->length);
  path->head = &(path->elts[ path->length-1 ]);
  if (path->search_level) {
    --(path->search_level);
  } else {
    path->found = 1;
    path->ends = 1;
  }

  RETURN_OK
}

static
int __db_index_traverse_step
  (struct db_path* path)
{
  DEBUGFUNCTION
  ASSERT(path)

  for (unsigned i=path->search_level+1; i > 0; i--) {
    if (path->head->node.next[ i-1 ] != 0) { break; }
    path->search_level = i-1;
  }

  RETURN_OK
}

static
int __db_index_traverse_cleanup
  (struct db_path* path)
{
/*
  unsigned l;

  if ((l = path->length) > 3) {
    if (path->elts[ l-1 ].node.level == path->elts[ l-2 ].node.level) {
      path->elts[ l-2 ] = path->elts[ l-1 ];
      --(path->length);
    }
  }
*/

  RETURN_OK
}

static
int __db_index_traverse_next
  (const db_t* db, struct db_path* path)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(path)

  off_t next = path->head->node.next[ path->search_level ];

  if (next == 0) {
    path->ends = 1;
  } else {
    ++(path->length);
    path->head = &(path->elts[ path->length-1 ]);
    path->head->node_offset = next;
    CHECK(__db_ixnode_read(db, path->head->node_offset, &(path->head->node)));
    CHECK(
      __db_tuple_read(db, path->head->node.tuple_offset, &(path->head->tuple))
    );
    CHECK(__db_index_traverse_cleanup(path));
  }

  RETURN_OK
}

static
int __db_index_traverse_testloop
  (const db_t* db, const char* key, const int partial, struct db_path* path)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(key)
  ASSERT(path)

  while (!(path->ends)) {
    char* testkey = path->head->tuple.key;

#ifdef _DEBUG
__db_path_debug(path);
#endif

    switch (path->found = __db_compare(key, testkey, partial)) {
    case 0:
      RETURN_OK
    case -1:
      CHECK(__db_index_traverse_back(path));
      break;
    case 1:
      CHECK(__db_index_traverse_step(path));
      break;
    }
    if (path->ends) {
      break;
    }
    CHECK(__db_index_traverse_next(db, path));
  }

  RETURN_OK
}

/**
 * Traverses the index to the (tuple with closest proximity to the) key,
 * leaving the path used to do that traversal to the caller.
 *
 * Check the value of path->found for how to proceed with the result:
 * - If it is zero, then the search key has been found exactly
 *   (even if partially).
 * - If it is one, then the path is positioned at a node just before
 *   the required place in the database.
 *
 * \param db       [IN]  Database.
 * \param key      [IN]  Search key (C string, zero terminated).
 * \param partial  [IN]  Allow for partial matches (database key is equal to,
 *                       but bigger than search key).
 * \param path    [OUT]  Path used to locate the key, or its closest proximity.
 *
 * \returns              Zero on success, non zero on error.
 *                       Note that 'key not found' is not an error: check
 *                       path->found value being non zero for this condition.
 */
static
int __db_index_traverse
  (const db_t* db, const char* key, const int partial, struct db_path* path)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(key)
  ASSERT(path)

  CHECK(__db_index_traverse_initialize(db, path));
  if (path->length == 1) {
    path->found = 1;
    RETURN_OK
  }
  CHECK(__db_index_traverse_testloop(db, key, partial, path));

  RETURN_OK
}

static
unsigned rands[] = { 1, 2, 3, 2, 1, 2, 1, 1 };
static
int randsi = 0;

static
unsigned __db_random
  (unsigned max)
{
  unsigned r = rands[ randsi++ ];
  randsi %= 8;
  return r;
}

/*
static inline
unsigned __db_random
  (unsigned max)
{
  DEBUGFUNCTION

  unsigned result = 1;
  while (result < max) {
    int r = rand() % (1 << DB_LOGFACTOR);
    if (r == 0) {
      ++result;
    } else {
      break;
    }
  }
  return result;
}
*/

static
int __db_index_tuple
  (const db_t* db, const off_t tuple_offset, const struct db_tuple* tuple)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(tuple)

  struct db_path path = { 0 };

  CHECK(__db_index_traverse(db, tuple->key, 0, &path));
#ifdef _DEBUG
  __db_path_debug(&path);
#endif

  switch (path.found) {
  case 0: /* found exact match; replace tuple */
    {
      off_t node_offset = path.elts[ path.length-1 ].node_offset;
      struct db_index_node* node = &(path.elts[ path.length-1 ].node);
      node->tuple_offset = tuple_offset;
      CHECK(__db_ixnode_write(db, node_offset, node));
    }
    break;

  case -1: /* undershoot; insert in between last and one before */
    --(path.length);
    __attribute__ ((fallthrough));

  case 1: /* overshoot; insert after last */
    {
      off_t node_offset;
      unsigned n = 0;
      struct db_index_node node = {
        .tuple_offset = tuple_offset,
        .level = __db_random(DB_IXTUPSIZE-1),
        .next = { 0 }
      };

      for (unsigned i=path.length; i; i--) {
        struct db_index_node* prevnode = &(path.elts[ i-1 ].node);
        if (n >= node.level) { break; }
        while (n < prevnode->level) {
          node.next[ n ] = prevnode->next[ n ];
          ++n;
          if (n >= node.level) { break; }
        }
      }
      CHECK(__db_write_at_end(db->ix, &node_offset, &node, sizeof(node)));

      n = 0;
      for (unsigned i=path.length; i; i--) {
        off_t prevoffset = path.elts[ i-1 ].node_offset;
        struct db_index_node* prevnode = &(path.elts[ i-1 ].node);
        if (n >= node.level) { break; }
        while (n < prevnode->level) {
          prevnode->next[ n ] = node_offset;
          ++n;
          if (n >= node.level) { break; }
        }
        CHECK(__db_write_at(db->ix, prevoffset, prevnode, sizeof(*prevnode)));
      }
    }
    break;
  }
  RETURN_OK
}

int __db_reindex
  (const db_t* db)
{
  DEBUGFUNCTION
  ASSERT(db)

  off_t off_db = 0;
  struct db_index_node node0 = {
    .tuple_offset = 0,
    .level = DB_IXTUPSIZE,
    .next = { 0 }
  };

  if (ftruncate(db->ix, 0)) { RETURN_ERR(DB_ERROR) }
  CHECK(__db_write_at(db->ix, 0, &node0, sizeof(node0)));
  if (lseek(db->fd, 0, SEEK_SET) != 0) { RETURN_ERR(DB_ERROR) }
  while (1) {
    struct db_tuple tuple = { 0 };
    if (__db_tuple_read(db, off_db, &tuple)) { break; }
    off_db += (2 * sizeof(unsigned)) + tuple.keysize + tuple.valuesize;
    if (tuple.flags & DB_FLAG_DEL) { continue; }
    CHECK(__db_index_tuple(db, off_db, &tuple));
  }
  RETURN_OK
}

/***************************** Public API starts ****************************/

#ifdef _DEBUG
void db_set_debug(int d) { devmacro_debug = d; }
#endif

/**
 * Simple cursor iteration function.
 */
int db_cursor_next
  (struct db_cursor* cursor)
{
  DEBUGFUNCTION
  ASSERT(cursor)

  while (1) {
    cursor->offset =
      cursor->offset +
      (2 * sizeof(unsigned)) + cursor->tuple.keysize + cursor->tuple.valuesize;
    if (__db_tuple_read(cursor->db, cursor->offset, &(cursor->tuple))) {
      RETURN_ERR(DB_ERROR)
    }
    if (!(cursor->tuple.flags & DB_FLAG_DEL)) {
      break;
    }
  }

  RETURN_OK
}

/**
 * Simple cursor get function.
 */
int db_cursor_get
  (struct db_cursor* cursor, char** key, vec_t* value)
{
  DEBUGFUNCTION
  ASSERT(cursor)
  ASSERT(key)
  ASSERT(value)

  off_t value_offset = cursor->offset +
      (2 * sizeof(unsigned)) + cursor->tuple.keysize;

  *key = cursor->tuple.key;
  value->size = cursor->tuple.valuesize;
  value->data = calloc(value->size + 1, 1);
  CHECK(__db_read_at(cursor->db->fd, value_offset, value->data, value->size));

  RETURN_OK
}

int db_cursor_init
  (const db_t* db, struct db_cursor* cursor)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(cursor)

  memset(cursor, 0, sizeof(struct db_cursor));
  cursor->db = db;
  if (__db_tuple_read(cursor->db, 0, &(cursor->tuple))) {
    RETURN_ERR(DB_ERROR)
  }
  if (cursor->tuple.flags & DB_FLAG_DEL) {
    return db_cursor_next(cursor);
  }

  RETURN_OK
}

int db_open
  (db_t* db, const char* path, const int openflags)
{
  DEBUGFUNCTION
  char index_path[ 1024 ];

  if ((db->fd = open(path, openflags, 0644)) == -1) {
    RETURN_ERR(DB_ERROR)
  }
  snprintf(index_path, sizeof(index_path), "%s.index", path);
  if ((db->ix = open(index_path, O_RDWR|O_CREAT, 0644)) == -1) {
    close(db->fd);
    RETURN_ERR(DB_ERROR)
  }
  return __db_reindex(db);
}

void db_close
  (db_t* db)
{
  DEBUGFUNCTION
  ASSERT(db)

  close(db->fd);
  close(db->ix);
}

int db_put
  (const db_t* db, const char* key, const vec_t* value)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(key)
  ASSERT(value)

  off_t eof = 0;
  struct db_tuple tuple = {
    .flags = 0,
    .keysize = strlen(key),
    .valuesize = value->size
  };

  snprintf(tuple.key, sizeof(tuple.key), "%s", key);
  if ((eof = lseek(db->fd, 0, SEEK_END)) == -1) {
    RETURN_ERR(DB_ERROR)
  }
  CHECK(__db_tuple_write(db, eof, &tuple));
  if (write(db->fd, value->data, value->size) != value->size) {
    if (ftruncate(db->fd, eof)) { }
    RETURN_ERR(DB_ERROR)
  }
  CHECK(__db_index_tuple(db, eof, &tuple));
  RETURN_OK
}

int db_get2
  (const db_t* db, const char* key, vec_t* value, const unsigned flags)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(key)
  ASSERT(value)

  struct db_path path = { 0 };
  off_t value_offset;
  unsigned value_size;

  CHECK(__db_index_traverse(db, key, (flags & DB_FLAG_PARTIAL), &path));
#ifdef _DEBUG
  __db_path_debug(&path);
#endif
  if ((flags & DB_FLAG_EXACT) && (path.found != 0)) {
    RETURN_ERR(DB_ERR_NOTFOUND)
  }

  value_offset =
    path.elts[ path.length-1 ].node.tuple_offset +
    (2 * sizeof(unsigned)) +
    path.elts[ path.length-1 ].tuple.keysize;
  value_size = path.elts[ path.length-1 ].tuple.valuesize;
fprintf(stderr, "VALUE SIZE IS %u\n", value_size);

  if (value->size == 0 && value->data == 0) {
    value->size = value_size;
    value->data = calloc(value->size + 1, 1);
  } else if (value->size > value_size) {
    value->size = value_size;
fprintf(stderr, "Forcing to %u\n", value->size);
  }
  CHECK(__db_read_at(db->fd, value_offset, value->data, value->size));
fprintf(stderr, "db_get2 (%u):\n", value->size);
//logmem(value->data, value->size);

  RETURN_OK
}

int db_get
  (const db_t* db, const char* key, vec_t* value)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(key)
  ASSERT(value)

  CHECK(db_get2(db, key, value, DB_FLAG_EXACT));

  RETURN_OK
}

int db_del2
  (const db_t* db, const char* key, const unsigned flags)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(key)

  struct db_path path = { 0 };

  CHECK(__db_index_traverse(db, key, (flags & DB_FLAG_PARTIAL), &path));
  if ((flags & DB_FLAG_EXACT) && (path.found != 0)) {
    RETURN_ERR(DB_ERR_NOTFOUND)
  }

  path.elts[ path.length-1 ].tuple.flags |= DB_FLAG_DEL;

  CHECK(
    __db_tuple_write(
      db,
      path.elts[ path.length-1 ].node.tuple_offset,
      &(path.elts[ path.length-1 ].tuple)
    )
  );

  RETURN_OK
}

int db_del
  (const db_t* db, const char* key)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(key)

  CHECK(db_del2(db, key, DB_FLAG_EXACT));

  RETURN_OK
}

int db_xcursor_move
  (struct db_xcursor* cursor, char* key, const unsigned flags)
{
  DEBUGFUNCTION
  ASSERT(cursor)

  struct db_path path = { 0 };

  CHECK(__db_index_traverse(cursor->db, key, flags & DB_FLAG_PARTIAL, &path));
  switch (path.found) {
  case 0:
    cursor->node_offset = path.elts[ path.length-1 ].node_offset;
    cursor->node = path.elts[ path.length-1 ].node;
    cursor->tuple = path.elts[ path.length-1 ].tuple;
    break;
  case 1:
    if (path.length == 1) {
      return db_xcursor_first(cursor);
    } else {
      --(path.length);
    }
    __attribute__ ((fallthrough));
  case -1:
    if (flags & DB_FLAG_EXACT) {
      RETURN_ERR(DB_ERR_NOTFOUND);
    } else {
      cursor->node_offset = path.elts[ path.length-1 ].node_offset;
      cursor->node = path.elts[ path.length-1 ].node;
      cursor->tuple = path.elts[ path.length-1 ].tuple;
    }
    break;
  }

  RETURN_OK
}

int db_xcursor_next
  (struct db_xcursor* cursor)
{
  DEBUGFUNCTION
  ASSERT(cursor)

  cursor->node_offset = cursor->node.next[ 0 ];
  if (cursor->node_offset == 0) {
    RETURN_ERR(DB_ERR_EOF);
  }
  CHECK(__db_ixnode_read(cursor->db, cursor->node_offset, &(cursor->node)));
  CHECK(__db_tuple_read(cursor->db, cursor->node.tuple_offset, &(cursor->tuple)));
  if (cursor->tuple.flags & DB_FLAG_DEL) {
    return db_xcursor_next(cursor);
  }

  RETURN_OK
}

int db_xcursor_first
  (struct db_xcursor* cursor)
{
  cursor->node_offset = 0;
  CHECK(__db_ixnode_read(cursor->db, 0, &(cursor->node)));
  return db_xcursor_next(cursor);
}

int db_xcursor_init
  (const db_t* db, struct db_xcursor* cursor)
{
  DEBUGFUNCTION
  ASSERT(db)
  ASSERT(cursor)

  memset(cursor, 0, sizeof(*cursor));
  cursor->db = db;
  return db_xcursor_first(cursor);
}

int db_xcursor_get
  (struct db_xcursor* cursor, char** key, vec_t* value)
{
  DEBUGFUNCTION
  ASSERT(cursor)

  off_t value_offset
          = cursor->node.tuple_offset +
            (2 * sizeof(unsigned)) + cursor->tuple.keysize;

  if (key) {
    *key = cursor->tuple.key;
  }
  if (value) {
    value->size = cursor->tuple.valuesize;
    value->data = calloc(value->size + 1, 1);
    CHECK(__db_read_at(cursor->db->fd, value_offset, value->data, value->size));
  }

  RETURN_OK
}

int db_xcursor_del
  (struct db_xcursor* cursor, char** key, vec_t* value)
{
  CHECK(db_xcursor_get(cursor, key, value));
  cursor->tuple.flags |= DB_FLAG_DEL;
  CHECK(__db_tuple_write(cursor->db, cursor->node.tuple_offset, &(cursor->tuple)));

  RETURN_OK
}

void db_debug
  (const db_t* db)
{
  off_t off_db = lseek(db->fd, 0, SEEK_SET);
  devmacro_debug=0;
  while (1) {
    struct db_tuple tuple = { 0 };
    off_t value_offset;
    char value[ 1024 ] = { 0 };

    if (__db_tuple_read(db, off_db, &tuple)) { break; }
    value_offset = off_db + (2 * sizeof(unsigned)) + tuple.keysize;
    if (__db_read_at(db->fd, value_offset, value, sizeof(value)-1)) {
    }
    if (tuple.valuesize < sizeof(value)) {
      value[ tuple.valuesize ] = 0;
    }
    fprintf(stderr,
      "Tuple @ %lu:\n"
      "- key '%s'\n"
      "- value size %u\n"
      "- value '%s'\n"
      , off_db
      , tuple.key
      , tuple.valuesize
      , value
    );
    if (tuple.flags & DB_FLAG_DEL) { fprintf(stderr, "  - Deleted\n"); }
    off_db += (2 * sizeof(unsigned)) + tuple.keysize + tuple.valuesize;
  }
  off_t off_ix = lseek(db->ix, 0, SEEK_SET);
  while (1) {
    struct db_index_node node = { 0 };
    if (__db_ixnode_read(db, off_ix, &node)) { break; }
    fprintf(stderr,
      "Index node @ %lu:\n"
      "- tuple offset: %u\n"
      "- level: %u\n"
      , off_ix
      , node.tuple_offset
      , node.level
    );
    for (unsigned i=0; i < node.level; i++) {
      fprintf(stderr, "- Next (%u): %u\n", i, node.next[ i ]);
    }
    off_ix += sizeof(node);
  }
  devmacro_debug=1;
}
