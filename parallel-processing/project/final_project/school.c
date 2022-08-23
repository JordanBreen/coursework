#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "school.h"
#include "index.h"

static int    num_schools = 0;
static school *schools     = NULL;

//////////////////////////////////////////////

struct school {
  school_id id : SCHOOL_ID_BIT; // exp: 10 
  str name;         // varied
};

///////////////////////////////////////////////

int parse_school (void *ext, int argc, str *argv, str *col) {
  const int
    arg_id   = 0,
    arg_name = 1;

  int index = atoi(argv[arg_id]) - 1;
  school *ptr = (school*)ext;
  ptr += index;
  
  ptr->id = index + 1;
  ptr->name = str_clone(argv[arg_name]);

  return 0;
}

////////////////////////////////////////////////

void init_schools () {
  schools = (school*) load_table ("school", parse_school, sizeof(school), &num_schools);
}

void free_schools () {
  free(schools);
}

/////////////////////////////////////////////////

str get_name_school (school_id id) {
  return schools[id_to_index(id)].name;
}
void print_school (school_id id) {
  printf ("%s\n", schools[id_to_index(id)].name);
}

void print_schools () {
  for(int i=1; i <= num_schools; i++)
    print_school(i);
}
