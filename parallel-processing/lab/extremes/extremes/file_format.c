/*************************************************************************************************
 * Title   : file_format.c
 * Purpose : Source file for definitions of file_format related functions
 * Author  : Jordan Breen
 * Version : 09/30/2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_format.h"

static const char* edge_format_names[] = {
  "collapsed", "traveled", "simple"
};

static const edge_format edge_format_values[] = {
  COLL,
  TRAV,
  SIMP
};

file_format* create_file_format (char* fe, float vn, edge_format ef)
{ // Allocate Memory
  file_format* ff = (file_format *)malloc(sizeof(file_format));
  // Assign Values
  ff->fe = fe;
  ff->vn = vn;
  ff->ef = ef;
  // Return
  return ff;
}

file_format* parse_file_format (char* str)
{ // Expected Format: "[fe] [vn] [ef]", space seperated values
  const char delim[2] = " ";
  char *fe_str = strtok(str,  delim);
  char *vn_str = strtok(NULL, delim);
  char *ef_str = strtok(NULL, delim);
  return create_file_format(fe_str, atof(vn_str), parse_edge_format(ef_str));
}

edge_format parse_edge_format (char* str)
{
  int i;
  for(i = 0; i < NUM_EDGE_FORMATS; i++)
    // if: the input string matches an edge_format
    if(strcmp(str, edge_format_names[i]) == 0)
      return edge_format_values[i];
  return NOT_EDGE_FORMAT;
}

const char* edge_format_to_string (edge_format ef)
{
  return edge_format_names[(int)ef];
}

void print_file_format (file_format* ff)
{ // Print neatly formatted file_format data
  printf("__________ File Format __________\n");
  printf("- File Extension : %s\n",    ff->fe);
  printf("- Version Number : %3.1f\n", ff->vn);
  printf("- Edge Format    : %s\n",    edge_format_to_string(ff->ef));
}
/*
char *remove_newline(char *str)
{
  int i = 0;
  int j = 0;
  while(str[i])
  {
    if(str[i] != '\n')
      str[j++] = str[i];
    i++;
  }
  str[j] = '\0';
  return str;
}
*/
