#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spell_level.h"
#include "buf_def.h"

struct spell_level {
  level    _level    : SPELL_LEVEL_BIT;
  class_id _class_id : CLASS_ID_BIT;
};

struct spell_level_group {
  spell_level ** _spell_level_refs;
  byte _size, _length;
};
  
spell_level* new_spell_level (level _level, class_id _class_id) {
  if(!valid_spell_level(_level)) {
    fprintf(stderr, "%s:%s(level _level = %d) ERROR, _level is outside of range [%d,%d]\n", __FILE__, __func__, _level, MIN_SPELL_LEVEL, MAX_SPELL_LEVEL);
    exit(1);
  }
  spell_level *ret_sl = malloc(sizeof(spell_level));
  ret_sl->_level    = _level;
  ret_sl->_class_id = _class_id;
  return ret_sl;
}

spell_level_group* new_spell_level_group (byte _length) {
  spell_level_group *ret_slg = malloc(sizeof(spell_level_group));
  ret_slg->_spell_level_refs = malloc(sizeof(spell_level*) * _length);
  ret_slg->_length = _length;
  ret_slg->_size = 0;
  return ret_slg;
}

void add_spell_level_group (spell_level_group *spell_level_group_ref, spell_level *spell_level_ref) {
  if(spell_level_group_ref->_size >= spell_level_group_ref->_length) {
    fprintf(stderr, "%s:%s() ERROR, Cannot add to full spell level group\n", __FILE__, __func__);
    exit(1);
  }
  spell_level_group_ref->_spell_level_refs[spell_level_group_ref->_size++] = spell_level_ref;
}

void free_spell_level (spell_level **spell_level_ref) {
  free(*spell_level_ref);
  *spell_level_ref = NULL;
}

str to_str_spell_level(spell_level *spell_level_ref) {
  buf buffer = "";
  sprintf(buffer, "%s %d", to_str_class(spell_level_ref->_class_id), spell_level_ref->_level);
  str ret_str = malloc(strlen(buffer)+1);
  strcpy(ret_str, buffer);
  return ret_str;
}

str to_str_spell_level_group(spell_level_group *spell_level_group_ref) {
  buf buffer = "";
  str catch;
  for(int i = 0; i < spell_level_group_ref->_size; i++) {
    catch = to_str_spell_level(spell_level_group_ref->_spell_level_refs[i]);
    sprintf(buffer, (i==spell_level_group_ref->_size-1) ? "%s%s" : "%s%s, ", buffer, catch);
    free(catch);
  }
  str ret_str = malloc(strlen(buffer)+1);
  strcpy(ret_str, buffer);
  return ret_str;
}

level get_level (spell_level *spell_level_ref) {
  return spell_level_ref->_level;
}

class_id get_class_id (spell_level *spell_level_ref) {
  return spell_level_ref->_class_id;
}

int valid_spell_level (level _level) {
  return (_level >= MIN_SPELL_LEVEL && _level <= MAX_SPELL_LEVEL);
}

size_t get_size_of_spell_level() {
  return sizeof(spell_level);
}
