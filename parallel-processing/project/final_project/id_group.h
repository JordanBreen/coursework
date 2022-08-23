#ifndef ID_GROUP_H
#define ID_GROUP_H

#include "bit_def.h"
#include "str_def.h"
#include "logx.h"

typedef enum   relation relation;
typedef struct id_group id_group;
typedef bit_8  ref_id;

size_t    get_size_of_id_group    ();
id_group *new_id_group            (int);
void      init_id_group           (id_group *, int);
void      free_id_group           (id_group **);
void      set_rel_id_group        (id_group *, int);
void      set_key_id_group        (id_group *, bit_8);
void      add_ref_id_group        (id_group *, bit_8);
ref_id    get_ref_id_group        (id_group *, bit_8);
ref_id    get_num_ref_id_group    (id_group *);
bit_8     get_capacity_id_group   (id_group *);
int       index_in_range_id_group (id_group *, bit_8);
int       is_full_id_group        (id_group *);
void      print_id_group          (id_group *, void(*)(ref_id));
str       to_string_id_group      (id_group *, str (*)(ref_id));
id_group *get_index_ptr_id_group  (id_group *, bit_8);
#endif
