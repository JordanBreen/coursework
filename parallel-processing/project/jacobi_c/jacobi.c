/**********************
 * name:    jacobi.c
 * purpose: ...
 * author:  Jordan Breen
 * version: 09/26/2021
*/

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "timer.h"
#include "grid.h"

#define ARGC  5
#define HIGH  1.0
#define LOW   0.0

typedef struct timeval time_val;
/*********************************************
 * name: 
 *   main
 * parameters:
 *   argv[0]: char[] source_filename - the name of this source file.
 *   argv[1]: int    grid_size       - the length and width of the grid (excluding the boundary).
 *   argv[2]: int    max_iter        - the maximum amount of jocobi iterations before ending calculations, base case A.
 *   argv[3]: double error_tolerance - the minimum amount of change between each grid cell per iteration, base case B.
 *   argv[4]: char[] output_filename - the file that the output is directed to, formatted to be read and plotted by GNUplot.
 * returns: (int)
 *   0 - normal termination
 *   1 - abnormal termination
 */
int main(int   argc,
	 char* argv[]){
  // Passed unexpected number of arguments
  if(argc != ARGC){
    fprintf(stderr, "Usage: %s (int)grid_size, (int)max_iter, (double)error_tolerance, (string)output_filename\n", argv[0]);
    exit(1);
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PARSING:
  // Try: Parse integer value at argv[1]
  int grid_size;
  if(!(grid_size = atoi(argv[1]))){
    fprintf(stderr, "%s: Failed to parse integer from value at argv[1], found %s\n", argv[0], argv[1]);
    exit(1);
  }
  // Try: Parse integer value at argv[2]
  int max_iter, iter;
  if(!(max_iter = atoi(argv[2]))){
    fprintf(stderr, "%s: Failed to parse integer from value at argv[2], found %s\n", argv[0], argv[2]);
    exit(1);
  }
  // Try: Parse double value at argv[3]
  double error_tolerance;
  if(!(error_tolerance = strtod(argv[3], NULL))){
    fprintf(stderr, "%s: Failed to parse double from value at argv[3], found %s\n", argv[0], argv[3]);
    exit(1);
  }
  else if((error_tolerance <= LOW)||(error_tolerance >= HIGH)){
    fprintf(stderr, "%s: Value at argv[3], Outside of range (%f,%f), found %s\n", argv[0], LOW, HIGH, argv[3]);
    exit(1);
  }
  // Get: string value at argv[4]
  char* output_filename = argv[4];
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // DECLARATIONS:
  // Named indexes, to better show loop behavior
  const int OUTER_START   = 0;
  const int OUTER_END     = grid_size + 1;
  const int INNER_START   = 1;
  const int INNER_END     = grid_size;
  const int BOUNDARY_SIZE = 1;
  const int TOTAL_SIZE    = grid_size + (2 * BOUNDARY_SIZE);
  const int NUM_GRIDS     = 2;
  // Grid structure and iterators
  grid_val **grid[NUM_GRIDS];
  int curr, prev, i, j;
  const long int SEED = 0;
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // INITIALIZATION:
  // Random Seed 
  srand48(SEED);
  // Allocating memory for the grid
  grid[0] = (grid_val **) malloc((TOTAL_SIZE) * sizeof(grid_val *));
  for (i = OUTER_START; i <= OUTER_END; i++)
    grid[0][i] = (grid_val *) malloc((TOTAL_SIZE) * sizeof(grid_val));
  grid[1] = (grid_val **) malloc((TOTAL_SIZE) * sizeof(grid_val *));
  for (i = OUTER_START; i <= OUTER_END; i++)
    grid[1][i] = (grid_val *) malloc((TOTAL_SIZE) * sizeof(grid_val));
  // Initialize the grids:
  // Top and Left Borders equal 1, everything else equals 0.
  for (i = OUTER_START; i <= OUTER_END; i++)
    for (j = OUTER_START; j <= OUTER_END; j++)
      grid[1][i][j] =
	grid[0][i][j] =
	  ((i == OUTER_START) || (j == OUTER_START)) ? HIGH : LOW;
  // Start current grid at 0
  curr = 0;
  prev = 1;
  // Initialize the current grid with random double values, ranging (0.0, 1.0)
  for (i = INNER_START; i <= INNER_END; i++)
    for (j = INNER_START; j <= INNER_END; j++)
      grid[prev][i][j] =
        grid[curr][i][j] =
	  (grid_val)rand() / (grid_val)((unsigned)RAND_MAX + 1);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // PROCESSING:
  grid_val max_diff, diff;
  time_val start_time, end_time;
  double   elapsed_time;
  // Start timer
  gettimeofday(&start_time, NULL);
  for (iter = 0; iter < max_iter; iter++){
    max_diff = 0.0f;
    // swap the grids
    curr = 1 - curr;
    prev = 1 - prev;
    // visit each grid cell
    for (i = INNER_START; i <= INNER_END; i++){
      for (j = INNER_START; j <= INNER_END; j++){
	// Get: average of grid[prev][i][j]'s four neighbors
        grid[curr][i][j] = (grid_val) ((grid[prev][i-1][ j ]  +
					grid[prev][ i ][j-1]  +
					grid[prev][ i ][j+1]  +
					grid[prev][i+1][ j ]) * 0.25);
	// Get the absolute value of the difference
	diff = grid[curr][i][j] - grid[prev][i][j];
	diff = (diff < 0) ? (diff * -1.0f) : (diff);
	// Possibly update max_diff to the current difference
	if(diff > max_diff)
	  max_diff = diff;
      }
    }
    // Base Case: If there isn't anymore meaningful change, end the iteration
    if (max_diff <= error_tolerance)
      break;
  }
  // Stop timer
  gettimeofday(&end_time, NULL);
  elapsed_time = diffgettime(start_time, end_time);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // OUTPUT:
  print_results(grid[curr], TOTAL_SIZE, BOUNDARY_SIZE, iter, max_diff, elapsed_time);
  write_grid(grid[curr], TOTAL_SIZE, output_filename);
  // Deallocating memory of the grid
  for (i = 0; i <= grid_size + 1; i++)
    free(grid[0][i]);
  free(grid[0]);
  for (i = 0; i <= grid_size + 1; i++)
    free(grid[1][i]);
  free(grid[1]);
  // Done, exit jacobi.c
  return 0;
}
