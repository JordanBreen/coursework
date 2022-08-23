/*************************************************************************************************
 * Title   : waypoint.h
 * Purpose : Header file for waypoint structure and related functions
 * Author  : Jordan Breen
 * Version : 09/30/2021
 */

#ifndef _H_WAYPOINT
#define _H_WAYPOINT
#define MAX_LBL_LEN 256

typedef enum Coordinate {
  LAT, // latitude
  LNG  // longitude
} Coordinate;

typedef struct waypoint {
  int    id;  // id number
  char  *lbl; // label
  float  lat; // latitude
  float  lng; // longitude
} waypoint;

typedef struct segment {
  int       id;
  waypoint *wps[2]; // pointers to waypoints
  //char    **rns;    // pointers to road names
} segment;

extern waypoint* create_waypoint (
		 int   id,
		 char* lbl,
		 float lat,
		 float lng);

extern segment*  create_segment (
		 waypoint* wpa,
		 waypoint* wpb);

extern waypoint* parse_waypoint (
		 int   id,
		 char* str);

extern segment*  parse_segment (
		 char*      str,
		 waypoint** waypoints);

extern waypoint* max (
                 Coordinate typ,
                 waypoint*  wpa,
	         waypoint*  wpb);

extern waypoint* min (
		 Coordinate typ,
		 waypoint*  wpa,
		 waypoint*  wpb);

extern void      print_waypoint (
		 waypoint* wp);

extern void      print_segment (
		 segment* sg);
#endif
