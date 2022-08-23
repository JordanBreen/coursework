#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>
#include "timer.h"
#include "spell.h"
#include "thread.h"
#include "bit_def.h"

static const byte   DEFAULT_NUM_THREADS = 4;
static const size_t DEFAULT_NUM_SPELL_IDS_TO_LOAD = sizeof(char)* 10;
byte                num_threads;
spell             **loaded_spells;
struct timeval      start_time, end_time;
double              elapsed_time;
size_t              num_spell_ids_to_load, num_loaded_spells;
spell_id           *spell_ids_to_load;

int main(int argc, str argv[])
{
  // validating command-line arguments:
  if (argc == 1) {
    num_threads = DEFAULT_NUM_THREADS;
    num_spell_ids_to_load = DEFAULT_NUM_SPELL_IDS_TO_LOAD;
  } else if (argc == 2) {
    num_threads = atoi(argv[1]);
    num_spell_ids_to_load = DEFAULT_NUM_SPELL_IDS_TO_LOAD;
  } else if (argc == 3) {
    num_threads = atoi(argv[1]);
    num_spell_ids_to_load = sizeof(char) * atoi(argv[2]);
  } else
    exit(1);

  // intializing array of ids to be processed:
  num_loaded_spells = num_spell_ids_to_load;
  spell_ids_to_load = (spell_id*) malloc(num_spell_ids_to_load * sizeof(spell_id));
  for(int i = 1; i <= num_spell_ids_to_load; i++)
    spell_ids_to_load[i-1] = (spell_id) i;

  // run processes in parallel:
  gettimeofday(&start_time, NULL);
  init_resources(num_threads);
  load_spells(num_threads, spell_ids_to_load, num_spell_ids_to_load, &loaded_spells);
  gettimeofday(&end_time, NULL);
  elapsed_time = diffgettime(start_time, end_time);

  // output and close program:
  printf("Results: loaded %ld spells in %lf seconds using %d threads.\n\n", num_loaded_spells, elapsed_time, num_threads);
  print_spells(loaded_spells, num_loaded_spells);
  free_resources(num_threads);
  
  return 0;
}
