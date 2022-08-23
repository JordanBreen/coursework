#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "subschool.h"
#include "index.h"

static int
  num_subschools          = 0,
  num_subschool_id_groups = 0;
static subschool
  *subschools = NULL;
static id_group
  *subschool_id_groups = NULL;

//////////////////////////////////////////////

struct subschool {
  subschool_id id : SUBSCHOOL_ID_BIT;     // for personal id 
  str          name;                      // varied
  school_id    school_id : SCHOOL_ID_BIT; // exp: 16
};

///////////////////////////////////////////////

int parse_subschool (void *ext, int argc, str *argv, str *col) {
  const int
    arg_id        = 0,
    arg_name      = 1,
    arg_school_id = 2;
  
  int index = id_to_index(atoi(argv[arg_id]));
  subschool *ptr = (subschool*)ext;
  ptr += index;

  ptr->id   = index_to_id(index);
  ptr->name = str_clone(argv[arg_name]);

  // school_id: DANGER possible NULL
  if (!argv[arg_school_id])
    num_subschool_id_groups++;
  else
    ptr->school_id = atoi(argv[arg_school_id]);

  return 0;
}
int parse_subschool_id_group (void *ext, int argc, str *argv, str *col) {
  const int
    pos_id             = 0,
    pos_group_size     = 1,
    pos_subschool_id_1 = 2,
    pos_subschool_id_2 = 3,
    pos_relation       = 4;
  // setup: point to our already allocated static array subschool_id_groups
  int index = id_to_index(atoi(argv[pos_id]));
  id_group *ptr = get_index_ptr_id_group(subschool_id_groups, index);
  // constants: for readability
  const int
    GROUP_SIZE     = atoi(argv[pos_group_size]),
    SUBSCHOOL_ID_1 = atoi(argv[pos_subschool_id_1]),
    SUBSCHOOL_ID_2 = atoi(argv[pos_subschool_id_2]),
    RELATION_INT   = atoi(argv[pos_relation])-1;
  // fill the already existing subschool_id_group
  init_id_group(ptr, GROUP_SIZE);
  set_key_id_group (ptr, index_to_id(index));
  add_ref_id_group (ptr, SUBSCHOOL_ID_1);
  add_ref_id_group (ptr, SUBSCHOOL_ID_2);
  set_rel_id_group (ptr, RELATION_INT);
  // done:
  return 0;
}

////////////////////////////////////////////////

void init_subschools () {
  subschools = (subschool*) load_table ("subschool", parse_subschool, sizeof(subschool), &num_subschools);
  num_subschools -= num_subschool_id_groups;
  subschools = realloc(subschools, sizeof(subschool) * num_subschools);
  if(!subschools) {
    fprintf(stderr, "%s:%s: Fatal Error, could not reallocated memory for subschools\n", __FILE__, __func__);
    exit(1);
  }
  subschool_id_groups = malloc(get_size_of_id_group() * num_subschool_id_groups); 
  load_table ("subschool_group", parse_subschool_id_group, get_size_of_id_group(), &num_subschool_id_groups);
}

void free_subschools () {
  free(subschools);
}

void free_subschool_groups () {
  free(subschool_id_groups);
}

/////////////////////////////////////////////////
str get_name_subschool (subschool_id id) {
  return subschools[id_to_index(id)].name;
}

void print_subschool (subschool_id id) {
  printf("%s", subschools[id_to_index(id)].name);
}

void print_subschools () {
  for(int id=1; id <= num_subschools; id++)
    print_subschool(id);
}

void print_subschool_id_group (subschool_id id) {
  print_id_group(get_subschool_id_group(id), print_subschool);
}

void print_subschool_id_groups () {
  for(int id=1; id <= num_subschool_id_groups; id++)
    print_subschool_id_group(id);
}

bit_8 get_num_subschools() {
  return num_subschools;
}

id_group *get_subschool_id_group(subschool_id id) {
  return get_index_ptr_id_group(subschool_id_groups, id_to_index(id));
}
