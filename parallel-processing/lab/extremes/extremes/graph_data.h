/*************************************************************************************************
 * Title   : graph_data.h
 * Purpose : Header file for graph_data structure and related functions
 * Author  : Jordan Breen
 * Version : 09/30/2021
 */

#ifndef _H_GRAPH_DATA
#define _H_GRAPH_DATA

typedef struct graph_data {
  int nv;  // number of verticies
  int ne;  // number of edges
} graph_data;

extern graph_data* create_graph_data (
	           int nv,
	           int ne);

extern graph_data* parse_graph_data (
	           char* str);

extern void        print_graph_data (
	           graph_data* gd);

#endif
