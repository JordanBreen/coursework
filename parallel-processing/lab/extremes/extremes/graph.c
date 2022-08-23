/*************************************************************************************************
 * Title   : graph.c
 * Purpose : Source file for graph structure and related functions
 * Author  : Jordan Breen
 * Version : 09/30/2021
 */
#include <stdlib.h>
#include "graph.h"

extern graph* create_graph()
{
  return (graph *)malloc(sizeof(graph));
}
