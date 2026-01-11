/**
 * This C file implements a table with rows of named fields.
 * It does this by using functionality from the btree library.
 */

#include <inttypes.h>

#include <util/table_t.h>

#undef ARRAY_EQUALS
#define ARRAY_EQUALS(a,b) (&a == &b)
MAKE_ARRAY_CODE(tuple_t, fields_)
MAKE_ARRAY_CODE(row_t, table_)

void row_deep_free
  (row_t* row)
{
  for (unsigned i=0; i < row->fields.count; i++) {
    free(row->fields.list[ i ].value.data);
    row->fields.list[ i ].value.data = 0;
    row->fields.list[ i ].value.size = 0;
  }
  free(row->fields.list);
  memset(row, 0, sizeof(*row));
}

void table_deep_free
  (table_t* table)
{
  for (unsigned i=0; i < table->count; i++) {
    row_deep_free(&(table->list[ i ]));
  }
  free(table->list);
  memset(table, 0, sizeof(*table));
}

char* row_get_as_string
  (row_t* row, char* key)
{
  for (unsigned i=0; i < row->fields.count; i++) {
    if (0 == strcmp(key, row->fields.list[ i ].name)) {
      return (char*)row->fields.list[ i ].value.data;
    }
  }
  return NULL;
}

static
int __table_get_id
  (db_t* db, const char* table, uint64_t* id)
{
  char keystr[ DB_KEY_SIZE ] = { 0 };
  vec_t val = { (unsigned char*)id, sizeof(*id) };

  snprintf(keystr, sizeof(keystr), "SEQ_%s", table);
  if (db_get(db, keystr, &val)) {
    *id = 1;
    return db_put(db, keystr, &val);
  } else {
    ++(*id);
    return db_put(db, keystr, &val);
  }
}

static
int __table_get_size
  (db_t* db, const char* table, unsigned* nrows)
{
  char keystr[ DB_KEY_SIZE ];
  vec_t value = { (unsigned char*)nrows, sizeof(unsigned) };

  snprintf(keystr, sizeof(keystr), "SIZ_%s", table);
  return db_get(db, keystr, &value);
}

static
int __table_set_size
  (db_t* db, const char* table, unsigned nrows)
{
  char keystr[ DB_KEY_SIZE ];
  vec_t value = { (unsigned char*)(&nrows), sizeof(unsigned) };

  snprintf(keystr, sizeof(keystr), "SIZ_%s", table);
  return db_put(db, keystr, &value);
}

/**
 * Example:
 *

__table_update_row(
  &db,
  "Users",                                  // table name
  13204,                                    // rowid
  3,                                        // 3 fields follow
  "Firstname", DB_TYPE_STRING, "Katherine", // Fieldname, type, value
  "Emailaddress", DB_TYPE_NULL,             // Note no 3rd param with NULL
  "Age", DB_TYPE_INTEGER, 32
);

 */
static
int __table_update_row
  (db_t* db, const char* table, uint64_t id, unsigned nfields, va_list ap)
{
  for (unsigned i=0; i < nfields; i++) {
    const char* fieldname = va_arg(ap, const char*);
    unsigned fieldtype = va_arg(ap, unsigned);
    char valuebuffer[ 64 ];
    char* fieldvalue_str = valuebuffer;
    int64_t fieldvalue_int = 0;
    double fieldvalue_float = 0;
    char keystr[ DB_KEY_SIZE ];
    vec_t val = { 0 };

    switch (fieldtype) {
    case DB_FIELDTYPE_NULL:
      snprintf(valuebuffer, sizeof(valuebuffer), "null");
      break;
    case DB_FIELDTYPE_BOOLEAN:
      fieldvalue_int = va_arg(ap, int64_t);
      if (fieldvalue_int) {
        snprintf(valuebuffer, sizeof(valuebuffer), "true");
      } else {
        snprintf(valuebuffer, sizeof(valuebuffer), "false");
      }
      break;
    case DB_FIELDTYPE_INTEGER:
      fieldvalue_int = va_arg(ap, int64_t);
      snprintf(valuebuffer, sizeof(valuebuffer), "%"PRId64, fieldvalue_int);
      break;
    case DB_FIELDTYPE_FLOAT:
      fieldvalue_float = va_arg(ap, double);
      snprintf(valuebuffer, sizeof(valuebuffer), "%f", fieldvalue_float);
      break;
    case DB_FIELDTYPE_STRING:
      fieldvalue_str = va_arg(ap, char*);
      break;
    }
    snprintf(keystr, sizeof(keystr),
             "TUP_%s_%.20"PRIu64"_%s", table, id, fieldname);
    val.data = (unsigned char*)fieldvalue_str;
    val.size = strlen(fieldvalue_str);
    if (db_put(db, keystr, &val)) {
      return ~0;
    }
  }
  return 0;
}

int table_update_row
  (db_t* db, const char* table, uint64_t rowid, unsigned nfields, ...)
{
  va_list ap = { 0 };
  int r;

  va_start(ap, nfields);
  if ((r = __table_update_row(db, table, rowid, nfields, ap)) != 0) {
    return ~0;
  }
  va_end(ap);

  return 0;
}

int table_insert_row
  (db_t* db, const char* table, unsigned nfields, ...)
{
  uint64_t id = 0;
  va_list ap = { 0 };
  int r;

  if (__table_get_id(db, table, &id)) {
    return ~0;
  }
  va_start(ap, nfields);
  if ((r = __table_update_row(db, table, id, nfields, ap)) != 0) {
    return ~0;
  }
  va_end(ap);

  {
    unsigned nrows = 0;
    if (__table_get_size(db, table, &nrows) == 0) {
      ++nrows;
      return __table_set_size(db, table, nrows);
    } else {
      return __table_set_size(db, table, (unsigned)1);
    }
  }

  return 0;
}

int table_delete_row
  (db_t* db, const char* table, uint64_t rowid)
{
  char skeystr[ DB_KEY_SIZE ];
  unsigned n = 0;

  snprintf(skeystr, sizeof(skeystr), "TUP_%s_%.20"PRIu64, table, rowid);

  while (db_del2(db, skeystr, DB_FLAG_PARTIAL|DB_FLAG_EXACT) == 0) {
    ++n;
  }
  if (n) {
    unsigned nrows = 0;
    if (__table_get_size(db, table, &nrows) == 0) {
      if (nrows == 0) {
        return ~0;
      }
      --nrows; 
      return __table_set_size(db, table, nrows);
    } else {
      return __table_set_size(db, table, (unsigned)1);
    }
  }
  return ~0;
}

static
int __table_iterate_rows
  (
    db_t* db,
    const char* table,
    uint64_t start,
    int(*fnc)(uint64_t,row_t*,void*),
    void* arg
  )
{
  struct db_xcursor cursor = { 0 };
  char skeystr[ DB_KEY_SIZE ];
  uint64_t id = 0;
  row_t row = { 0 };
  unsigned off_num = strlen(table) + 5;

  snprintf(skeystr, sizeof(skeystr), "TUP_%s_%.20"PRIu64, table, start);
  db_xcursor_init(db, &cursor);
  if (db_xcursor_move(&cursor, skeystr, DB_FLAG_PARTIAL|DB_FLAG_EXACT)) {
    return ~0;
  }
  while (1) {
    char* key = 0;
    vec_t val = { 0 };
    if (db_xcursor_get(&cursor, &key, &val) == 0) {
      char* numstr = key + off_num;
      uint64_t foundid;
      if (0 != memcmp(key, skeystr, off_num)) {
        break;
      }
      numstr[ 20 ] = 0;
      foundid = strtoull(numstr, 0, 10);
//fprintf(stderr, "ROWID %"PRIu64"; key '%s' (%u) value '%s' (%u)\n", foundid, (char*)key.data, key.size, (char*)val.data, val.size);
      if (foundid != id) {
        id = foundid;
        if (row.fields.count) {
          int r = fnc(id, &row, arg);
          switch (r) {
          case 0:
            row_deep_free(&row);
            break;
          case DB_ITERATE_STOP:
            row_deep_free(&row);
            return 0;
          case DB_ITERATE_STOPNOFREE:
            return 0;
          case DB_ITERATE_CONTNOFREE:
            break;
          default:
            row_deep_free(&row);
            return r;
          }
        }
        row.rowid = id;
      }
      tuple_t tuple = { .value.data = val.data, .value.size = val.size };
      snprintf(tuple.name, sizeof(tuple.name), "%s", &(numstr[ 21 ]));
      fields_push(&(row.fields), tuple);
    }
    if (db_xcursor_next(&cursor)) {
      break;
    }
  }
  if (row.fields.count) {
    int r = fnc(id, &row, arg);
    switch (r) {
    case 0:
      row_deep_free(&row);
      break;
    case DB_ITERATE_STOP:
      row_deep_free(&row);
      return 0;
    case DB_ITERATE_STOPNOFREE:
      return 0;
    case DB_ITERATE_CONTNOFREE:
      break;
    default:
      row_deep_free(&row);
      return r;
    }
  }
  return 0;
}

int table_iterate_rows
  (db_t* db, const char* table, int(*fnc)(uint64_t,row_t*,void*), void* arg)
{
  return __table_iterate_rows(db, table, (uint64_t)0, fnc, arg);
}

static
int __table_fill_block
  (uint64_t rowid, row_t* row, void* arg)
{
  table_t* table = arg;
  (void)rowid;

  if (table->count == table->allocated) {
    return DB_ITERATE_STOPNOFREE;
  } else {
    table_push(table, *row);
    return DB_ITERATE_CONTNOFREE;
  }
}

int table_get_block
  (
    db_t* db,
    const char* table,
    table_t* result,
    uint64_t start,
    unsigned length
  )
{
  if (length == 0) {
    return 0;
  }
  result->allocated = result->count + length;
  result->list = realloc(result->list, sizeof(row_t) * result->allocated);
  return __table_iterate_rows(db, table, start, __table_fill_block, result);
}

static
int  __table_get_row
  (uint64_t rowid, row_t* row, void* arg)
{
  row_t** result = arg;
  (void)rowid;
  **result = *row;
  return DB_ITERATE_STOPNOFREE;
}

int table_get_row
  (db_t* db, const char* table, uint64_t rowid, row_t* row)
{
  return __table_iterate_rows(db, table, rowid, __table_get_row, &row);
}

int table_get_size
  (db_t* db, const char* table, unsigned* nrows)
{
  struct db_xcursor cursor = { 0 };
  char skey[ DB_KEY_SIZE ];
  uint64_t id = 0;

  if (__table_get_size(db, table, nrows) == 0) {
    return 0;
  }

  snprintf(skey, sizeof(skey), "TUP_%s_", table);
  db_xcursor_init(db, &cursor);
  if (db_xcursor_move(&cursor, skey, DB_FLAG_PARTIAL|DB_FLAG_EXACT)) {
    return ~0;
  }
  *nrows = 0;
  while (1) {
    char* key;
    if (db_xcursor_get(&cursor, &key, 0) == 0) {
      char* numstr = key + strlen(skey); /* cache strlen(skey) ? */
      uint64_t foundid;
      numstr[ 20 ] = 0;
      foundid = strtoull(numstr, 0, 10);
      if (foundid != id) {
        id = foundid;
        ++(*nrows);
      }
    }
    if (db_xcursor_next(&cursor)) {
      break;
    }
  }
  return __table_set_size(db, table, *nrows);
}
