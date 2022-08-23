#include "resource.h"

static task initializers[] = {
  init_class_types,
  init_classes,
  init_descriptors,
  init_ranges,
  init_schools,
  init_subschools,
  init_time_units
};

static task destructors[] = {
  free_class_types,
  free_classes,
  free_descriptors,
  free_ranges,
  free_schools,
  free_subschools,
  free_time_units
};

size_t get_initializer_tasks(task **task_ref) {
  *task_ref = initializers;
  return sizeof(initializers) / sizeof(*initializers);
}

size_t get_destructor_tasks(task **task_ref) {
  *task_ref = destructors;
  return sizeof(destructors) / sizeof(*destructors);
}
