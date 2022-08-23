#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include "buf_def.h"
#include "sqlite_loader.h"
#include "spell.h"

sqlite3      *db           = NULL; // reference to "Pathfinder.db"
sqlite3_stmt *open_res     = NULL; 
str           db_file_name = NULL; // "Pathfinder.db"

/*********************************************************************************
 * name: load_table
 * purp: loads all data in the specified table by the use of the passed callback function,
 *       usually titled as "parse_*" found in their respective c files
 * args: const str (char*) -- table_name     : the table name in "Pathfinder.db" to be read from
 *       int(*)(...) -------- callback       : the parsing function unique to each object that invokes load_table()
 *       size_t ------------- obj_size       : the byte size of the object that invokes load_table()
 *       int* --------------- out_table_size : the size of the table, this reference is a static variable in the object's c file
 * rtrn: the newly parsed data, to be cast to their respective type outside this function
 * note: this function is called by each object's "init_*" function
*/
void* load_table (const str db_table_name, int(*callback)(void*, int, str*, str*), size_t obj_size, int* out_table_size) {
  void *storage;
  sqlite3_stmt *res = NULL;
  str err_msg = NULL;
  buf sql_query = "SELECT * FROM ";
  int rc;

  strcat(sql_query, db_table_name);
  *out_table_size = get_table_size(db_table_name);
  storage = malloc((obj_size)*(*out_table_size));
  rc = sqlite3_exec(db, sql_query, callback, storage, &err_msg);
  if (rc != SQLITE_OK ) {      
    fprintf(stderr, "Failed to select data from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    db_close(err_msg);     
    exit(1);
  }
  
  sqlite3_finalize(res);
  return storage;
}

/*********************************************************************************
 * name: load_by_id
 * purp: loads data from the target table at the specified id value
 * args: const str (char*) -- table_name : the table name in "Pathfinder.db" to be read from
 *       int(*)(...) -------- callback   : the parsing function unique to each object that invokes load_table()
 *       size_t ------------- obj_size   : the byte size of the object that invokes load_table()
 *       int ---------------- id         : the id value to be searched for and loaded in the target table
 * rtrn: the newly parsed data, to be cast to their respective type outside this function
 * note: currently, this function is called by spell::load_spell() exclusively
*/
void* load_by_id (const str db_table_name, int(*callback)(void*, int, str*, str*), size_t obj_size, int id) {
  void *storage;
  sqlite3_stmt *res = NULL;
  str err_msg = NULL;
  buf sql_query;
  int rc, table_size; 

  table_size = get_table_size(db_table_name);
  if (id < 1 || id > table_size) {
    fprintf(stderr, "%s:%s() ERROR, id %d is outside the range of possible id values [1,%d]\n", __FILE__, __func__, id, table_size);
    db_close(err_msg);
    exit(1);
  }
  
  sprintf(sql_query, "SELECT * FROM %s WHERE id = %d", db_table_name, id);
  storage = malloc(obj_size);
  
  rc = sqlite3_exec(db, sql_query, callback, storage, &err_msg);
  if (rc != SQLITE_OK ) {
    fprintf(stderr, "Failed to select data from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    db_close(err_msg);
    exit(1);
  }

  sqlite3_finalize(res);
  return storage;
}

/*********************************************************************************
 * name: count_rows
 * purp: callback function to get_table_size(), gets the number of rows in a table
 * args: void* --------- ext  : "external", storage instatiated in get_table_size(), save here
 *       int ----------- argc : number of columns in the queried data
 *       str* (char**) - argv : array of strings holding string data of the current row
 *       str* (char**) - col  : array of strings holding the queried data's column names
 * rtrn: error code
*/
int count_rows (void *ext, int argc, str *argv, str *col) {
  int *size = (int*)ext;
  *size = atoi(*argv);
  return 0;
}

/*********************************************************************************
 * name: db_close
 * purp: closes the database cleanly, frees the memory of the error message if has any
 * args: str (char*) -- err_msg : the error message
 * rtrn: void
*/
void db_close (str err_msg) {
  if(err_msg) sqlite3_free(err_msg);
  free(db_file_name);
  sqlite3_close(db);
}

/*********************************************************************************
 * name: db_open
 * purp: opens the database and does error checking
 * args: const str (char*) -- arg_db_file_name : the file name of the database
 * rtrn: void
*/
void db_open (const str arg_db_file_name) {
  int ret_val = SQLITE_OK;
  str err_msg = NULL;
  db_file_name = str_clone(arg_db_file_name);
  ret_val = sqlite3_open(db_file_name, &db);
  if(ret_val != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    db_close(err_msg);
    exit(1);
  }
  ret_val = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &open_res, 0);
  if (ret_val != SQLITE_OK) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    db_close(err_msg);
    exit(1);
  }
}

/*********************************************************************************
 * name: get_table_size
 * purp: executes a query to get the number of rows in a table, uses the count_rows()
 *       callback function to do this, provides error checking on its results
 * args: str (char*) -- db_table_name : the name of the table to get the size of
 * rtrn: the number of rows in the table 
*/
int get_table_size (const str db_table_name) {
  str err_msg  = NULL;
  int out_size = 0;
  int ret_val;
  buf sql_stmt_count = "SELECT COUNT (*) FROM ";
  strcat(sql_stmt_count,  db_table_name);
  ret_val = sqlite3_exec(db, sql_stmt_count, count_rows, &out_size, &err_msg);
  if (ret_val != SQLITE_OK ) {
    fprintf(stderr, "Failed to get count from db_table: %s\n", db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    db_close(err_msg);
    exit(1);
  }
  return out_size;
}

/*********************************************************************************
 * name: str_clone
 * purp: a utility function to copy strings to char pointers that are
 *       not yet allocated any memory. Handles null cases.
 * args: str (char*) -- arg_str : the string to be cloned
 * rtrn: a newly allocated copy of the string value passed in
*/
str str_clone(str arg_str) {
  if(!arg_str)
    return NULL;
  str ret_str = malloc(strlen(arg_str) + 1);
  strcpy(ret_str, arg_str);
  return ret_str;
}
