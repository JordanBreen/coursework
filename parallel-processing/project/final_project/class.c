#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "class.h"
#include "index.h"
static int        num_class_types = 0;
static int        num_classes     = 0;
static class_type *class_types     = NULL;
static class      *classes         = NULL;

//////////////////////////////////////////////

struct class_type {
  class_type_id _id : CLASS_TYPE_ID_BIT; // exp: 7 class types
  str           _name;                   // varies
};

struct class {
  class_id      _id : CLASS_ID_BIT;
  str           _name;
  str           _abrv;                              // exp: 3 characters
  class_type_id _class_type_id : CLASS_TYPE_ID_BIT; // exp: 7 class types
  bit_8         _skill_ranks   : SKILL_RANK_BIT;    // exp: max value of 8 (rogue)
  bit_8         _source_id;
};

///////////////////////////////////////////////

int parse_class_type (void  *ext, int argc, str *argv, str *col) {
  const int
    POS_ID   = 0,
    POS_NAME = 1;
  
  int index = atoi(argv[POS_ID]) - 1;
  class_type *ptr = (class_type*)ext;
  ptr += index;
  
  ptr->_id = index + 1;
  ptr->_name = str_clone(argv[POS_NAME]);

  return 0;
}

int parse_class (void  *ext, int argc, str *argv, str *col) {
  const int
    POS_ID            = 0,
    POS_NAME          = 1,
    POS_ABRV          = 2,
    POS_CLASS_TYPE_ID = 3,
    POS_SKILL_RANKS   = 4,
    POS_SOURCE_ID     = 5;
  
  int index = atoi(argv[POS_ID]) - 1;
  class *ptr = (class*)ext;
  ptr += index;

  ptr->_id = index + 1;
  ptr->_name = str_clone(argv[POS_NAME]);
  ptr->_abrv = str_clone(argv[POS_ABRV]);
  ptr->_class_type_id = atoi(argv[POS_CLASS_TYPE_ID]);
  ptr->_skill_ranks = atoi(argv[POS_SKILL_RANKS]);
  ptr->_source_id = atoi(argv[POS_SOURCE_ID]);

  return 0;
}

////////////////////////////////////////////////

void init_class_types() {
  class_types = (class_type*) load_table ("class_type", parse_class_type, sizeof(class_type), &num_class_types);
}
void init_classes() {
  classes = (class*) load_table ("class", parse_class, sizeof(class), &num_classes);
}

void free_class_types() {
  free(class_types);
}

void free_classes() {
  free(classes);
}

/////////////////////////////////////////////////

byte get_num_classes () {
  return num_classes;
}

str to_str_class_type (class_type_id _class_type_id) {
  return class_types[id_to_index(_class_type_id)]._name;
}

str to_str_class(class_id _class_id) {
  return classes[id_to_index(_class_id)]._name;
}

class_id get_id_class (str _str){
  for(int i = 0; i < num_classes; i++) {
    if(_str[0] == classes[i]._name[0] && strcmp(_str, classes[i]._name) == 0)
      return classes[i]._id;
  }
  fprintf(stderr, "%s:%s() ERROR, %s not found as a name in classes\n", __FILE__, __func__, _str);
  return -1;
}

void print_classes () {
  for(int i = 1; i <= num_classes; i++)
    printf("%s\n", to_str_class(i));
}
  

