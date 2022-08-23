#ifndef  SPELL_H
#define  SPELL_H
#define  SPELL_ID_BIT 12
#define  NUM_SPELL_LEVELS 10 // range 0-9
// structures:
#include "class.h"
#include "descriptor.h"
#include "range.h"
#include "school.h"
#include "spell.h"
#include "spell_level.h"
#include "subschool.h"
#include "time_unit.h"
// utilities:
#include "logx.h"
#include "bit_def.h"
#include "str_def.h"
#include "id_group.h"

typedef bit_16 spell_id;

typedef struct spell_components spell_components;

typedef struct spell_attributes spell_attributes;

typedef enum answer {
  NO       = 0,
  YES      = 1,
  SEE_TEXT = 2,
  NUM_ANSWERS
} answer;

typedef struct duration duration;

typedef struct spell spell;

extern spell *load_spell (spell_id);
extern void   print_spell (spell*);
extern void   print_spells (spell**, size_t);
extern size_t get_size_of_spell_ptr ();
extern size_t get_size_of_spell ();
#endif
