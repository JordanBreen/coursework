/*************************************************************************************************
 * Title   : graph_data.c
 * Purpose : Source file for definitions of graph_data related functions
 * Author  : Jordan Breen
 * Version : 09/30/2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_format.h"
#include "graph_data.h"

graph_data* create_graph_data (int nv, int ne)
{ // Allocate Memory
  graph_data* gd = (graph_data *)malloc(sizeof(graph_data));
  // Assign Values
  gd->nv = nv;
  gd->ne = ne;
  // Return
  return gd;
}

graph_data* parse_graph_data (char* str)
{ // Expected Format: "[nv] [ne]", space seperated values
  // Note: assumed not edge_format.TRAV, no current implementation for this type [10/01/2021]
  const char delim[2] = " ";
  char *nv_str = strtok(str,  delim);
  char *ne_str = strtok(NULL, delim);
  return create_graph_data(atoi(nv_str), atoi(ne_str));
}

void print_graph_data (graph_data* gd)
{ // Print neatly formatted file_format data
  printf("__________ Graph Data ___________\n");
  printf("- Number of Verticies : %7d\n", gd->nv);
  printf("- Number of Edges     : %7d\n", gd->ne);
}
