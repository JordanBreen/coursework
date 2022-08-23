#ifndef  SCHOOL_H
#define  SCHOOL_H
#define  SCHOOL_ID_BIT 4
#include "bit_def.h"
#include "str_def.h"

typedef struct school school;
typedef bit_8 school_id;
extern void init_schools    ();
extern void free_schools    ();
extern str  get_name_school (school_id);
extern void print_school    (school_id);
extern void print_schools   ();

#endif
