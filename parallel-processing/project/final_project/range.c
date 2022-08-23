#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "range.h"
#include "sqlite_loader.h"


static int    num_ranges = 0;
static range *ranges     = NULL;

//////////////////////////////////////////////

struct range {
  range_id  _id    : RANGE_ID_BIT; // exp: 6 
  str       _name;      // varied
  bit_8     _fixed : 1; // is the range fixed?
  // scalar data //////////////////
  bit_16    _base  : 9; // exp: max 400
  bit_8     _plus  : 6; // exp: max 40
  bit_8     _rate  : 2; // exp: max 4
};

///////////////////////////////////////////////

int parse_range (void *ext, int argc, str *argv, str *col) {
  const int
    POS_ID   = 0,
    POS_NAME = 1,
    POS_BASE = 2,
    POS_PLUS = 3,
    POS_RATE = 4;

  int index  = atoi(argv[POS_ID]) - 1;
  range *ptr = (range*)ext;
  ptr += index;

  ptr->_id   = index + 1;
  ptr->_name = str_clone(argv[POS_NAME]);

  // testing base column, DANGER possible NULL:
  if(!argv[POS_BASE]) { // fixed range
    ptr->_fixed = 1;
    ptr->_base  = 0;
    ptr->_plus  = 0;
    ptr->_rate  = 0;
  }
  else { // scalar range
    ptr->_fixed = 0;
    ptr->_base  = atoi(argv[POS_BASE]);
    ptr->_plus  = atoi(argv[POS_PLUS]);
    ptr->_rate  = atoi(argv[POS_RATE]);
  }

  return 0;
}

////////////////////////////////////////////////

void init_ranges () {
  ranges = (range*) load_table ("range", parse_range, sizeof(range), &num_ranges);
}

void free_ranges () {
  free(ranges);
}

/////////////////////////////////////////////////
str to_str_range (range_id _range_id) {
  return ranges[id_to_index(_range_id)]._name;
}

void print_ranges () {
  for(int i=0; i < num_ranges; i++) {
    printf ("- range [%d] %s", ranges[i]._id, ranges[i]._name);
    if(!ranges[i]._fixed)
      printf (" (%d ft. + %d ft./%d level%s)", ranges[i]._base, ranges[i]._plus, ranges[i]._rate, (ranges[i]._rate > 1) ? "s" : "");
    printf ("\n");
  }
}
