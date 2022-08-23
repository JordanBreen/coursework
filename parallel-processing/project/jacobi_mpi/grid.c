#include <stdio.h>
#include <string.h>

typedef double grid_val;

void print_results(grid_val** grid,
                   int        total_grid_size,
                   int        boundary_size,
                   int        iter,
                   double     max_diff,
                   double     elapsed_time){
  // int i, j;
  printf("RESULTS:\n");
  printf("Grid Size:     %d\n", total_grid_size - (2 * boundary_size));
  printf("Iterations:    %d\n", iter);
  printf("Last max_diff: %.5f\n", max_diff);
  printf("Elapsed Time:  %.5f ms\n", elapsed_time);
  printf("\n");
  /*
  for (i = 0; i < total_grid_size; i++){
    for (j = 0; j < total_grid_size; j++)
      printf("%1.3f ", grid[i][j]);
    printf("\n");
  }
  */
}
void write_grid(grid_val** grid,
                int        total_grid_size,
                char*      filename){
  FILE *out_file = fopen(filename, "w");
  int i, j, n = 50;
  grid_val curr_val;
  char out_str[n];
  for (i = 0; i < total_grid_size; i++){
    for (j = 0; j < total_grid_size; j++){
      // Cell's x position ////////////////
      snprintf(out_str, n, "%d", j);
      strcat(out_str, "\t");
      fputs(out_str, out_file);
      // Cell's y position ////////////////
      snprintf(out_str, n, "%d", i);
      strcat(out_str, "\t");
      fputs(out_str, out_file);
      // Cell's double value //////////////
      curr_val = grid[i][j];
      snprintf(out_str, n, "%f", curr_val);
      strcat(out_str, "\t");
      fputs(out_str, out_file);
      // End of Cell's info ///////////////
      fputs("\n", out_file);
    }
  }
  fclose(out_file);
}


