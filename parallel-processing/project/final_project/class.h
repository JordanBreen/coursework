#ifndef  CLASS_H
#define  CLASS_H
#define  CLASS_ID_BIT 6
#define  CLASS_TYPE_ID_BIT 3
#define  SKILL_RANK_BIT 4
#include "bit_def.h"
#include "str_def.h"

typedef struct class_type class_type;
typedef struct class class;
typedef bit_8 class_id, class_type_id;

extern void init_class_types();
extern void init_classes();

extern void free_class_types();
extern void free_classes();

extern str to_str_class_type (class_type_id);
extern str to_str_class (class_id);

extern byte     get_num_classes();
extern class_id get_id_class (str);

extern void print_classes();

#endif
