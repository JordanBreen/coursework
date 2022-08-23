/*************************************************************************************************
 * Title   : graph.h
 * Purpose : Header file for graph structure and related functions
 * Author  : Jordan Breen
 * Version : 09/30/2021
 */

#ifndef _H_GRAPH
#define _H_GRAPH

#include "file_format.h"
#include "graph_data.h"
#include "waypoint.h"

typedef struct graph {        // MEMBERS:
  file_format *m_file_format; // file format
  graph_data  *m_graph_data;  // graph data
  waypoint   **m_waypoints;   // waypoints
  segment    **m_segments;    // segments
} graph;

extern graph* create_graph();
#endif
