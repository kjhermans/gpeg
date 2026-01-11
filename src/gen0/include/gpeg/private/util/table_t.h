#ifndef _TABLE_T_H_
#define _TABLE_T_H_

#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include <util/vec_t.h>
#include <util/array.h>
#include <util/db_t.h>

#define DB_KEY_SIZE             256

typedef struct
{
  char          name[ DB_KEY_SIZE ];
  vec_t         value;
}
tuple_t;

MAKE_ARRAY_HEADER(tuple_t, fields_)

typedef struct
{
  fields_t      fields;
  uint64_t      rowid;
}
row_t;

MAKE_ARRAY_HEADER(row_t, table_)

typedef struct
{
  table_t       table;
  uint64_t      rowid;
  unsigned      offset;
  unsigned      length;
}
cache_t;

#define DB_FIELDTYPE_NULL       0
#define DB_FIELDTYPE_BOOLEAN    1
#define DB_FIELDTYPE_INTEGER    2
#define DB_FIELDTYPE_FLOAT      3
#define DB_FIELDTYPE_STRING     4

#define DB_ITERATE_STOP         1
#define DB_ITERATE_STOPNOFREE   2
#define DB_ITERATE_CONTNOFREE   3

extern
void row_deep_free
  (row_t* row);

extern
void table_deep_free
  (table_t* table);

extern
char* row_get_as_string
  (row_t* row, char* key);

extern
int table_insert_row
  (db_t* db, const char* table, unsigned nfields, ...);

extern
int table_update_row
  (db_t* db, const char* table, uint64_t rowid, unsigned nfields, ...);

extern
int table_delete_row
  (db_t* db, const char* table, uint64_t rowid);

extern
int table_get_row
  (db_t* db, const char* table, uint64_t rowid, row_t* row);

extern
int table_get_block
  (
    db_t* db,
    const char* table,
    table_t* result,
    uint64_t start,
    unsigned length
  );

extern
int table_iterate_rows
  (db_t* db, const char* table, int(*fnc)(uint64_t,row_t*,void*), void* arg);

extern
int table_get_size
  (db_t* db, const char* table, unsigned* nrows);

#endif
