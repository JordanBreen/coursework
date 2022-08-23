#ifndef RESOURCE_H
#define RESOURCE_H
#include <stddef.h>
#include "spell.h"
typedef void(*task)();
size_t get_initializer_tasks (task**);
size_t get_destructor_tasks  (task**);
#endif
