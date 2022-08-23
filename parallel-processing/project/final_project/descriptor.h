#ifndef  DESCRIPTOR_H
#define  DESCRIPTOR_H
#define  DESCRIPTOR_ID_BIT 5
#include "bit_def.h"
#include "str_def.h"

typedef struct descriptor descriptor;
typedef bit_8 descriptor_id, d_id;

extern void init_descriptors    ();
extern void free_descriptors    ();
extern d_id get_id_descriptor   (str);
extern str  get_name_descriptor (d_id);
extern int  get_num_descriptors ();
extern void print_descriptors   ();

#endif
