#ifndef  SPELL_LEVEL_H
#define  SPELL_LEVEL_H
#define  NUM_SPELL_LEVEL 10
#define  MAX_SPELL_LEVEL  9
#define  MIN_SPELL_LEVEL  0
#define  SPELL_LEVEL_BIT  4
#include "bit_def.h"
#include "str_def.h"
#include "class.h"

typedef struct spell_level spell_level, SL;
typedef struct spell_level_group spell_level_group, SL_group;
typedef bit_8 level;

extern spell_level       *new_spell_level    (level, class_id);
extern spell_level_group *new_spell_level_group (byte);
extern void   add_spell_level_group (spell_level_group *, spell_level *);
extern void   free_spell_level   ();
extern str    to_str_spell_level (spell_level *);
extern str    to_str_spell_level_group(spell_level_group*);
extern int    valid_spell_level  (level);
extern size_t get_size_of_spell_level();
#endif
