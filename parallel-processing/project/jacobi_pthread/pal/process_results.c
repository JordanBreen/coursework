#include<stdio.h>
#include<stdlib.h>
typedef struct test_result
{
  int
  test_num,
  num_proc;
  double
  time_elapsed;
} test_result;
int
  NUM_PROC_TESTS,
  NUM_TEST_TRIALS,
  NUM_RESULTS;
test_result
  *results,
  **averages;

test_result *get_average(test_result *index);
void print_results();
void print_averages();
int main(int argc, char *argv[])
{
  const char
    *PROG_NAME = argv[0],
    *FILE_NAME = argv[1];
  
  NUM_PROC_TESTS  = atoi(argv[2]),
  NUM_TEST_TRIALS = atoi(argv[3]),
  NUM_RESULTS = NUM_PROC_TESTS * NUM_TEST_TRIALS;

  int i;
  results  = (test_result*)malloc(NUM_RESULTS*sizeof(test_result));
  averages = (test_result**)malloc(NUM_PROC_TESTS*sizeof(test_result*));
 
  FILE *fp;
  if(!(fp=fopen(FILE_NAME, "r")))
  {
    fprintf(stderr, "Could not open input file %s in %s\n", FILE_NAME, PROG_NAME);
    exit(1);
  }
  else
    for(i=0; i<NUM_RESULTS; i++)
      fscanf(fp, "%d,%d,%lf", &(results[i].test_num), &(results[i].num_proc), &(results[i].time_elapsed));
  fclose(fp);
  //print_results();
  for(i=0; i<NUM_PROC_TESTS; i++)
    averages[i] = get_average(&results[i]);
  print_averages();
  free(averages);
  free(results);
  return 0;
}

test_result *get_average(test_result *index)
{
  test_result *out = (test_result*)malloc(sizeof(test_result));
  out->num_proc = index->num_proc;
  out->test_num = 0;
  out->time_elapsed = 0.0f;
  test_result *trav = index;
  while(trav < (index+NUM_RESULTS))
  {
    out->time_elapsed += trav->time_elapsed;
    trav += NUM_PROC_TESTS;
  }
  out->time_elapsed /= NUM_TEST_TRIALS;
  return out;
}

void print_results()
{
  test_result *tr = results;
  while(tr != results + NUM_RESULTS)
  {
    printf("Test#%d | Procs: %2d | Time: %.4lf\n", tr->test_num, tr->num_proc, tr->time_elapsed);
    tr++;
  }
}

void print_averages()
{
  test_result **tr = averages;
  while(tr != averages + NUM_PROC_TESTS)
  {
    printf("Average time for %2d Proccesses = %.4lf sec\n", (*tr)->num_proc, (*tr)->time_elapsed);
    tr++;
  }
}
