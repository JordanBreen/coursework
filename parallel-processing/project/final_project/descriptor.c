#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "descriptor.h"
#include "index.h"

static int         num_descriptors = 0;
static descriptor *descriptors     = NULL;

//////////////////////////////////////////////

struct descriptor {
  d_id id; 
  str  name;
};

///////////////////////////////////////////////

int parse_descriptor (void  *ext, int argc, str *argv, str *col) {
  const int
    arg_id   = 0,
    arg_name = 1;

  int index = atoi(argv[arg_id]) - 1;
  descriptor *ptr = (descriptor*)ext;
  ptr += index;

  ptr->id = index + 1;
  ptr->name = str_clone(argv[arg_name]);

  return 0;
}

////////////////////////////////////////////////

void init_descriptors() {
  descriptors = (descriptor*) load_table ("descriptor", parse_descriptor, sizeof(descriptor), &num_descriptors);
}

void free_descriptors() {
  free(descriptors);
}

/////////////////////////////////////////////////

d_id get_id_descriptor (str arg_name) {
  for(int i = 0; i < num_descriptors; i++)
    if(arg_name[0] == descriptors[i].name[0] && strcmp(arg_name, descriptors[i].name) == 0)
      return descriptors[i].id;
  fprintf(stderr, "%s:%s() ERROR, %s not found as a name in descriptors\n", __FILE__, __func__, arg_name);
  return -1;
}

str get_name_descriptor (descriptor_id arg_id) {
  return descriptors[id_to_index(arg_id)].name;
}

int get_num_descriptors () {
  return num_descriptors;
}


void print_descriptors() {
  for(int i=0; i < num_descriptors; i++) {
    printf ("- descriptors[%d] -\n", i);
    printf ("  id   = %d\n", descriptors[i].id);
    printf ("  name = %s\n", descriptors[i].name);
  }
}
