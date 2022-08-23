#ifndef  SUBSCHOOL_H
#define  SUBSCHOOL_H
#define  SUBSCHOOL_ID_BIT 4
#include "school.h"
#include "id_group.h"
#include "bit_def.h"
#include "str_def.h"

typedef struct subschool subschool;
typedef bit_8 subschool_id;

extern void  init_subschools ();
extern void  free_subschools ();
extern str   get_name_subschool (subschool_id);
extern bit_8 get_num_subschools ();
extern id_group* get_subschool_id_group(subschool_id); 
extern void  print_subschool (subschool_id);
extern void  print_subschools ();
extern void  print_subschool_id_group (subschool_id);
extern void  print_subschool_id_groups ();
#endif
