/*************************************************************************************************
 * Title   : file_format.h
 * Purpose : Header file for file format structure and related functions
 * Author  : Jordan Breen
 * Version : 09/30/2021
 */

#ifndef _H_FILE_FORMAT
#define _H_FILE_FORMAT

typedef enum edge_format {
  NOT_EDGE_FORMAT = -1,
  COLL, // Collapsed
  TRAV, // Traveled
  SIMP, // Simple
  NUM_EDGE_FORMATS
} edge_format;

typedef struct file_format {
  char       *fe; // file extension
  float       vn; // version number
  edge_format ef; // edge format
} file_format;

extern file_format* create_file_format (
		    char*       fe,
		    float       vn,
  		    edge_format ef);

extern file_format* parse_file_format (
		    char* str);

extern edge_format  parse_edge_format (
		    char* str);	       

extern const char*  edge_format_to_string (
                    edge_format ef);

extern void         print_file_format (
		    file_format* ff);

//extern char*        remove_newline(char* str);
#endif
