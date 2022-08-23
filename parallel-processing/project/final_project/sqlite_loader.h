#ifndef SQL_LOADER_H
#define SQL_LOADER_H
#include <sqlite3.h>
#include "str_def.h"
#include "index.h"
extern void  db_open         (const str); 
extern int   count_rows      (void*, int, str*, str*);
extern void* load_table      (const str, int(*)(void*, int, str*, str*), size_t, int*);
extern void* load_by_id      (const str, int(*)(void*, int, str*, str*), size_t, int);
extern int   peek_table_size (const str, const str);
extern int   get_table_size  (const str);
extern void  db_close        (str);
extern str   str_clone       (str);
#endif
