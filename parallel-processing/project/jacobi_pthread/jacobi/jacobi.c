/**********************
 * name:    jacobi.c
 * purpose: ...
 * author:  Jordan Breen
 * version: 11/10/2021
*/
#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "timer.h"
#include "grid.h"

#define ARGC 6
#define NUM_GRIDS 2
#define HIGH 1.0
#define LOW 0.0
#define MASTER 0

pthread_barrier_t
  barrier;
pthread_mutex_t
  mutex;
int
  grid_size,
  max_iter,
  num_threads,
  last_grid,
  last_iter;
double
  error_tolerance;
grid_val
  **grid[NUM_GRIDS],
  global_max_diff;

typedef struct jacobi_thread
{
  int thread_num;
  pthread_t thread_handle;
} jacobi_thread;

typedef struct timeval time_val;

void *thread_compute(void *arg);

/*********************************************
 * name: 
 *   jacobi.main()
 * parameters:
 *   argv[0]: char[] source_filename - the name of the program.
 *   argv[1]: int    num_threads     - the number of threads.
 *   argv[2]: int    grid_size       - the length and width of the grid (excluding the boundary).
 *   argv[3]: int    max_iter        - the maximum amount of jocobi iterations before ending calculations, base case A.
 *   argv[4]: double error_tolerance - the minimum amount of change between each grid cell per iteration, base case B.
 *   argv[5]: char[] output_filename - the file that the output is directed to, formatted to be read and plotted by GNUplot.
 * returns: (int)
 *   0 - normal termination
 *   1 - abnormal termination
 */
int main(int argc, char* argv[])
{
  // Passed unexpected number of arguments
  if(argc != ARGC)
  {
    fprintf(stderr, "Usage: %s (int)grid_size, (int)max_iter, (double)error_tolerance, (string)output_filename\n", argv[0]);
    exit(1);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PARSING:
  // Try: Parse integer value at argv[1]
  if(!(num_threads = atoi(argv[1])))
  {
    fprintf(stderr, "%s: Failed to parse integer from value at argv[1], found %s\n", argv[0], argv[1]);
    exit(1);
  }
  if(!(grid_size = atoi(argv[2])))
  {
    fprintf(stderr, "%s: Failed to parse integer from value at argv[2], found %s\n", argv[0], argv[2]);
    exit(1);
  }
  // Try: Parse integer value at argv[2]
  if(!(max_iter = atoi(argv[3])))
  {
    fprintf(stderr, "%s: Failed to parse integer from value at argv[3], found %s\n", argv[0], argv[3]);
    exit(1);
  }
  // Try: Parse double value at argv[3]
  if(!(error_tolerance = strtod(argv[4], NULL)))
  {
    fprintf(stderr, "%s: Failed to parse double from value at argv[5], found %s\n", argv[0], argv[4]);
    exit(1);
  }
  else if((error_tolerance <= LOW)||(error_tolerance >= HIGH))
  {
    fprintf(stderr, "%s: Value at argv[3], Outside of range (%f,%f), found %s\n", argv[0], LOW, HIGH, argv[3]);
    exit(1);
  }
  char* output_filename = argv[5];
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // DECLARATIONS:
  const int
    OUTER_START   = 0,
    OUTER_END     = grid_size + 1,
    INNER_START   = 1,
    INNER_END     = grid_size,
    BOUNDARY_SIZE = 1,
    TOTAL_SIZE    = grid_size + (2 * BOUNDARY_SIZE);
  int
    i, j, rc;
  time_val
    start_time, end_time;
  double
    elapsed_time = 0.0f;
  jacobi_thread
    *thread_info;

  ///////////////////////////////////////////////////////////////////////////////
  global_max_diff = 0.0f;
  srand48(0);
  
  grid[0] = (grid_val **)malloc((TOTAL_SIZE)*sizeof(grid_val *));
  for (i = OUTER_START; i <= OUTER_END; i++)
    grid[0][i] = (grid_val *)malloc((TOTAL_SIZE)*sizeof(grid_val));

  grid[1] = (grid_val **)malloc((TOTAL_SIZE) * sizeof(grid_val *));
  for (i = OUTER_START; i <= OUTER_END; i++)
    grid[1][i] = (grid_val *)malloc((TOTAL_SIZE)*sizeof(grid_val));
  
  ///////////////////////////////////////////////////////////////////////////////
  // Initialize the grids:

  // Top and Left Borders equal 1, everything else equals 0.
  for (i = OUTER_START; i <= OUTER_END; i++)
    for (j = OUTER_START; j <= OUTER_END; j++)
      grid[0][i][j] = grid[1][i][j] = ((i == OUTER_START) || (j == OUTER_START)) ? HIGH : LOW;

  // Initialize the current grid with random double values, ranging (0.0, 1.0)
  for (i = INNER_START; i <= INNER_END; i++)
    for (j = INNER_START; j <= INNER_END; j++)
      grid[0][i][j] = grid[1][i][j] = (grid_val)rand()/(grid_val)((unsigned)RAND_MAX + 1);

  ///////////////////////////////////////////////////////////////////////////////

  pthread_barrier_init(&barrier, NULL, num_threads);
  pthread_mutex_init(&mutex, NULL);
  thread_info = (jacobi_thread *)malloc(num_threads*sizeof(jacobi_thread));

  ///////////////////////////////////////////////////////////////////////////////

  gettimeofday(&start_time, NULL);
  // PARALLEL SECECTION
  for (int i = 0; i < num_threads; i++)
  {
    thread_info[i].thread_num = i;
    rc = pthread_create(&(thread_info[i].thread_handle), NULL, thread_compute, &(thread_info[i]));
    if (rc)
    {
      fprintf(stderr, "Could not create thread %d\n", i);
      exit(1);
    }
  }
  // PARALLEL DONE, JOIN
  for (i = 0; i < num_threads; i++)
    pthread_join(thread_info[i].thread_handle, NULL);

  gettimeofday(&end_time, NULL);

  //////////////////////////////////////////////////////////////////////////////
  
  elapsed_time = diffgettime(start_time, end_time);
  print_results(grid[last_grid], TOTAL_SIZE, BOUNDARY_SIZE, last_iter, global_max_diff, elapsed_time);
  write_grid(grid[last_grid], TOTAL_SIZE, output_filename);

  pthread_barrier_destroy(&barrier);
  pthread_mutex_destroy(&mutex);

  // Deallocating memory of the grids
  for (i = 0; i <= grid_size + 1; i++) free(grid[0][i]);
  free(grid[0]);
  for (i = 0; i <= grid_size + 1; i++) free(grid[1][i]);
  free(grid[1]);
  // Done, exit jacobi.c
  return 0;
}

void *thread_compute(void *arg)
{
  jacobi_thread
    *me = (jacobi_thread *)arg;
  int
    i, j,
    curr = 0, prev = 1, // local copies, to avoid mutex locks 
    start_row = me->thread_num * grid_size / num_threads + 1,
    end_row   = start_row + grid_size / num_threads - 1;
  double
    local_max_diff,
    diff;
  for (int iter = 1; (iter <= max_iter); iter++)
  {
    if(me->thread_num == MASTER)
    {
      last_grid = prev;
      last_iter = iter;
      global_max_diff = 0.0f;
    }
    local_max_diff = 0.0f;
    // swap the grids
    curr = 1 - curr;
    prev = 1 - prev;
    /////////////////////////////////
    pthread_barrier_wait(&barrier);//
    /////////////////////////////////
    for (i=start_row;i<=end_row;i++)
    {
      for (j=1;j<=grid_size;j++)
      {
	// Get: average of grid[prev][i][j]'s four neighbors
	grid[curr][i][j] = (grid_val)((grid[prev][i-1][j] + grid[prev][i][j-1] + grid[prev][i][j+1] + grid[prev][i+1][j]) * 0.25);
        // Get the absolute value of the difference
        diff = grid[curr][i][j] - grid[prev][i][j];
        diff = (diff < 0) ? (diff * -1.0f) : (diff);
        // Possibly update max_diff to the current difference
        local_max_diff = (diff > local_max_diff) ? (diff) : (local_max_diff);
      }
    }
    pthread_mutex_lock(&mutex);
    if(local_max_diff > global_max_diff) global_max_diff = local_max_diff;
    pthread_mutex_unlock(&mutex);
    /////////////////////////////////
    pthread_barrier_wait(&barrier);//
    /////////////////////////////////
    if (global_max_diff <= error_tolerance)
      break;
    /////////////////////////////////
    pthread_barrier_wait(&barrier);//
    /////////////////////////////////
  }
  return NULL;
}
