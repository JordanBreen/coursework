#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_format.h"
#include "graph.h"
#include "graph_data.h"
#include "waypoint.h"

char *remove_newline(char *str);

int main (int argc, char *argv[])
{
  int   XARG = 2;       // Expected number of arguments
  char *PROG = argv[0]; // Program name
  
  if(argc != XARG){
    fprintf(stderr, "%s: Invalid number of arguments, was expecting %d argument(s) [str in_fn]\n", PROG, XARG);
    exit(1);
  }
  
  char *in_fn = argv[1];
  FILE *in_fp  = fopen(in_fn, "r");
  if(in_fp == NULL){
    fprintf(stderr, "%s: Error: could not open file <%s>\n", PROG, in_fn);
    exit(1);
  }

  char  *buffer;
  size_t buffsize = 32;

  buffer = (char *)malloc(buffsize * sizeof(char));
  if(buffer == NULL){
    fprintf(stderr, "%s: Error: could not allocate memory for char buffer[%zd]\n", PROG, buffsize);
    exit(1);
  }

  char *XFILE = "TMG";
  graph *my_graph = create_graph();
  // LOADING DATA FROM TMG FILE: //////////////////////////////////////////////////////////////////
  // File_Format Section:
  getline(&buffer, &buffsize, in_fp);
  buffer = remove_newline(buffer);
  my_graph -> m_file_format = parse_file_format(buffer);
  print_file_format(my_graph -> m_file_format);
  if(strcmp(my_graph -> m_file_format -> fe, XFILE) != 0){
    fprintf(stderr, "%s: Error: invalid file type, was expecting file type %s\n", PROG, XFILE);
    exit(1);
  }
  // Graph_Data Section:
  getline(&buffer, &buffsize, in_fp);
  buffer = remove_newline(buffer);
  my_graph -> m_graph_data = parse_graph_data(buffer);
  print_graph_data(my_graph -> m_graph_data);

  my_graph -> m_waypoints = (waypoint **) malloc ((my_graph -> m_graph_data -> nv) * sizeof(waypoint *));
  my_graph -> m_segments  = (segment  **) malloc ((my_graph -> m_graph_data -> ne) * sizeof(segment  *));

  // Waypoint Section:
  int i;
  for(i = 0; i < my_graph -> m_graph_data -> nv; i++){
    getline(&buffer, &buffsize, in_fp);
    buffer = remove_newline(buffer);
    my_graph -> m_waypoints[i] = parse_waypoint(i, buffer);
  }

  // Segment Section:
  //for(i = 0; i < my_graph -> m_graph_data -> ne; i++){
    // getline(&buffer, &buffsize, in_fp);
    // buffer = remove_newline(buffer);
    // my_graph -> m_segments[i] = parse_segment(buffer, my_graph -> m_waypoints);
    // my_graph -> m_segments[i] -> id = i;
    //}
  
  // Now looking for global extremes of my_graph:
  // Extremes:
  waypoint *max_lat, *max_lng,
           *min_lat, *min_lng;
  // Primer:
  max_lat = max_lng = min_lat = min_lng = my_graph->m_waypoints[0];
  
  for(i = 1; i < my_graph -> m_graph_data -> nv; i++){
    max_lat = max(LAT, max_lat, my_graph -> m_waypoints[i]);
    max_lng = max(LNG, max_lng, my_graph -> m_waypoints[i]);
    min_lat = min(LAT, min_lat, my_graph -> m_waypoints[i]);
    min_lng = min(LNG, min_lng, my_graph -> m_waypoints[i]);
  }
  fprintf(stdout, "____________ RESULTS ____________\n");
  fprintf(stdout, "____________ max_lat ____________\n"); print_waypoint(max_lat);
  fprintf(stdout, "____________ max_lng ____________\n"); print_waypoint(max_lng);
  fprintf(stdout, "____________ min_lat ____________\n"); print_waypoint(min_lat);
  fprintf(stdout, "____________ min_lng ____________\n"); print_waypoint(min_lng);

  for(i = 0; i < my_graph -> m_graph_data -> nv; i++)
    free(my_graph -> m_waypoints[i]);

  
  return 0;
}

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

