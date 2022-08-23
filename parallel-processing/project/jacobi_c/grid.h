typedef double grid_val;

/*********************************************
 * name:
 *   print_results
 * purpose:
 *   to output information about the final grid's state to the console.
 * parameters:
 *   grid_val** grid            - target 2D grid of type grid_value.
 *   int        total_grid_size - the grid size plus twice the boundary size.
 *   int        boundary_size   - the grid's boundary size, hard coded as 1.
 *   int        iter            - the number of iterations after the final jacobi iteration.
 *   double     max_diff        - the maximum difference found of all grid cells for the final jacobi iteration.
 *   double     time_elapsed    - the total time it took to complete the jacobi iteration test, reference: miliseconds
 */
extern void print_results(grid_val** grid,
                          int        total_grid_size,
                          int        boundary_size,
                          int        iter,
                          double     max_diff,
                          double     time_elapsed);
/*********************************************
 * name:
 *   write_grid
 * purpose:
 *   to output information about the final grid's state to the target output file,
 *   data is formatted to be interpreted by GNUplot.
 * parameters:
 *   grid_val** grid            - target 2D grid of type grid_value.
 *   int        total_grid_size - the grid size plus twice the boundary size.
 *   char*      filename        - the target file to be written to.
 */
extern void write_grid(grid_val** grid,
                      int        total_grid_size,
                      char*      filename);
