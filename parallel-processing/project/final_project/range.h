#ifndef  RANGE_H
#define  RANGE_H
#define  RANGE_ID_BIT 3
#include "bit_def.h"
#include "str_def.h"

typedef struct range range;
typedef byte range_id;

extern void init_ranges();
extern void free_ranges();
extern str  to_str_range(range_id);
extern void print_ranges();

#endif
