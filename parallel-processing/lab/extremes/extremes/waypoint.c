/*************************************************************************************************
 * Title   : waypoint.c
 * Purpose : Source file for definitions of waypoint related functions
 * Author  : Jordan Breen
 * Version : 09/30/2021
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "waypoint.h"

waypoint* create_waypoint (int id, char* lbl, float lat, float lng)
{ // Allocate Memory
  waypoint* wp = (waypoint *)malloc(sizeof(waypoint));
  // Assign Values
  wp->id  = id;
  wp->lbl = lbl;
  wp->lat = lat;
  wp->lng = lng;
  // Return
  return wp;
}

segment* create_segment (waypoint *wpa, waypoint *wpb)
{ // Allocate Memory
  segment* s = (segment *)malloc(sizeof(segment));
  // Assign Values
  s->wps[0] = wpa;
  s->wps[1] = wpb;
  // Return
  return s;
}

waypoint* parse_waypoint (int id, char* str)
{ // Expected Format: "[lbl] [lat] [lng]", space seperated values
  const char delim[2] = " ";
  char *lbl_str = strtok(str,  delim);
  char *lat_str = strtok(NULL, delim);
  char *lng_str = strtok(NULL, delim);
  return create_waypoint(id, lbl_str, atof(lat_str), atof(lng_str));
}

segment* parse_segment (char* str, waypoint** waypoints)
{ // Expected Format: "[lbl] [lat] [lng]", space seperated values
  const char delim[2] = " ";
  char *wpa_str = strtok(str,  delim);
  char *wpb_str = strtok(NULL, delim);
  
  int wpa_i = atoi(wpa_str);
  int wpb_i = atoi(wpb_str);

  return create_segment(waypoints[wpa_i], waypoints[wpb_i]);  
}

waypoint* max (Coordinate typ, waypoint* wpa, waypoint* wpb)
{ // Return the waypoint of greater LAT || LNG
  switch(typ){
  case LAT: return (wpa->lat > wpb->lat) ? wpa : wpb;
  case LNG: return (wpa->lng > wpb->lng) ? wpa : wpb;
  default:  return NULL;
  }
}

waypoint* min (Coordinate typ, waypoint* wpa, waypoint* wpb)
{ // Return the waypoint of lesser LAT || LNG
  switch(typ){
  case LAT: return (wpa->lat < wpb->lat) ? wpa : wpb;
  case LNG: return (wpa->lng < wpb->lng) ? wpa : wpb;
  default:  return NULL;
  }
}

void print_waypoint (waypoint* wp)
{ // Print neatly formatted waypoint data
  printf("________ Waypoint[%4d] _________\n", wp->id);
  printf("- Label     : %s\n",    wp->lbl);
  printf("- Latitude  : %3.6f\n", wp->lat);
  printf("- Longitude : %3.6f\n", wp->lng);
}

void print_segment (segment* sg)
{ // Print neatly formatted waypoint data
  printf("________ Segment[%4d] _________\n", sg->id);
  printf("- Waypoint[0] -\n"); print_waypoint(sg->wps[0]);
  printf("- Waypoint[1] -\n"); print_waypoint(sg->wps[1]);
}
