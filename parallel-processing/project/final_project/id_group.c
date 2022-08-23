#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "id_group.h"
#include "buf_def.h"
enum relation {
  AND = 0,
  OR = 1,
  NUM_RELATIONS
};

static const int
  MIN_CAP = 1,
  MAX_CAP = 8;

struct id_group {
  bit_8
    key,
   *refs,
    num_refs : 3,
    capacity : 3,
    relation : 1;
};

// since the id_group is obscured, we get sizeof this way
size_t get_size_of_id_group () {
  return sizeof(id_group);
}

// returns a new id_group, capacity set to int arg_capacity
id_group *new_id_group(int arg_capacity) {
    if (arg_capacity > MAX_CAP) {
    fprintf(stderr, "%s:%s(int arg_capacity = %d), Error num_ids greater than MAX_CAP(%d)\n", __FILE__, __func__, arg_capacity, MAX_CAP);
    exit(1);
  } else if (arg_capacity < MIN_CAP) {
    fprintf(stderr, "%s:%s(int arg_capacity = %d), Error num_ids less than MIN_CAP(%d)\n", __FILE__, __func__, arg_capacity, MIN_CAP);
    exit(1);
  } else {
    id_group *out = (id_group*)malloc(sizeof(id_group));
    out->num_refs = 0;
    out->capacity = arg_capacity;
    out->refs = (bit_8*)malloc(sizeof(bit_8)*arg_capacity);
    return out;
  }
}

// initializes an already existing id_group, capacity set to int arg_capacity
void init_id_group(id_group* id_group_ref, int arg_capacity) {
    if (arg_capacity > MAX_CAP) {
    fprintf(stderr, "%s:%s(int arg_num_ids = %d), Error num_ids greater than MAX_CAP(%d)\n", __FILE__, __func__, arg_capacity, MAX_CAP);
    exit(1);
  } else if (arg_capacity < MIN_CAP) {
    fprintf(stderr, "%s:%s(int arg_num_ids = %d), Error num_ids less than MIN_CAP(%d)\n", __FILE__, __func__, arg_capacity, MIN_CAP);
    exit(1);
  } else {
    id_group_ref->num_refs = 0;
    id_group_ref->capacity = arg_capacity;
    id_group_ref->refs = (bit_8*)malloc(sizeof(bit_8)*arg_capacity);
  }
}

// frees memory used by id_group, sets dangling pointers to NULL
void free_id_group (id_group **id_group_ref) {
  free((*id_group_ref)->refs);
  (*id_group_ref)->refs = NULL;
  free(*id_group_ref);
  *id_group_ref = NULL;
}

// sets the id unique to each individual id_group
void set_key_id_group (id_group *id_group_ref, bit_8 arg_key) {
  id_group_ref -> key = arg_key;
}

// sets the relation between each reference id in the group (and / or)
void set_rel_id_group (id_group *id_group_ref, int arg_rel) {
  if(arg_rel >= NUM_RELATIONS || arg_rel < 0) {
    fprintf(stderr, "%s:%s(int arg_relation = %d), Error arg_relation outside of range [%d,%d]\n", __FILE__, __func__, arg_rel, 0, NUM_RELATIONS);
    exit(1);
  } else {
    id_group_ref->relation = (relation) arg_rel;
  }
}

// adds a reference id to the group, ref ids <= capacity
void add_ref_id_group (id_group *id_group_ref, bit_8 arg_id) {
  if(is_full_id_group(id_group_ref)) {
    fprintf(stderr, "%s:%s(bit_8 arg_id = %d), Error adding id to id_group_ref exceeds capacity of %d, add aborted\n", __FILE__, __func__, arg_id, id_group_ref->capacity);
    exit(1);
  } else {
    id_group_ref->refs[id_group_ref->num_refs++] = arg_id;
  }
}

// returns a reference id found at the arg_index argument
bit_8 get_ref_id_group (id_group *id_group_ref, bit_8 arg_index) {
  if(!index_in_range_id_group(id_group_ref, arg_index)) {
    fprintf(stderr, "%s:%s(bit_8 arg_index = %d), Error arg_index is outside of current id_group_ref range [%d,%d], get id aborted\n", __FILE__, __func__, arg_index, 0, id_group_ref->num_refs);
    exit(1);
  } else {
    return id_group_ref->refs[arg_index];
  }
}

bit_8 get_num_ref_id_group (id_group *id_group_ref) {
  return id_group_ref->num_refs;
}

bit_8 get_capacity_id_group (id_group *id_group_ref) {
  return id_group_ref->capacity;
}

int index_in_range_id_group (id_group *id_group_ref, bit_8 arg_index) {
  return arg_index < id_group_ref->num_refs && arg_index >= 0;
}

int is_full_id_group (id_group *id_group_ref) {
  return id_group_ref->num_refs >= id_group_ref->capacity;
}

void print_id_group (id_group *id_group_ref, void(*print_function)(ref_id)) {
  for(int i = 0; i < id_group_ref->capacity; i++)
    print_function(id_group_ref->refs[i]);
}

str to_string_id_group (id_group *id_group_ref, str(*to_str_function)(ref_id)) {
  buf buffer = "";
  for(int i = 0; i < id_group_ref->capacity; i++)
    sprintf(buffer, (i==id_group_ref->capacity-1)? "%s%s" : "%s%s, ", buffer, to_str_function(id_group_ref->refs[i]));
  str ret_str = malloc(strlen(buffer)+1);
  strcpy(ret_str, buffer);
  return ret_str;
}

id_group* get_index_ptr_id_group (id_group *array_ref, bit_8 index) {  
  return array_ref + index;
}

