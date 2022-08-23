/* File: mpirds-reduce.c
 *
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <mpi.h>
#include <math.h>

int main(void) {
  
  /**     DATA STORAGE     **/
  const int NUM_DIGITS  = 10;
  const int MASTER_RANK =  0;
  const int BUFFER_SIZE = 20;
  const int N           = 1073741824; // Arbitrary
  int my_rank, comm_sz; // MPI Variables 
  int i, j;             // Iterators     

  int global_count[NUM_DIGITS];

  /**     MPI BOOT PROCESS     **/
  MPI_Init(NULL, NULL);                   
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  
  /**     ERROR CHECKING     **/
  double log2_d = log2((double)comm_sz);
  int    log2_i = log2_d;
  if((log2_d - log2_i) != 0) {
    fprintf(stderr, "Error: number of processes is not a power of 2, found %d\n", comm_sz);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  if(N % comm_sz != 0) {
    fprintf(stderr, "Error: N is not evenly divisible by the number of processes\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  
  /**     DATA STORAGE     **/
  // Varibales: ////////////////////////////////
  int interval = N / comm_sz;
  int floor    = interval * my_rank;
  int ceiling  = (interval * (my_rank + 1)) - 1;
  // Arrays : //////////////////////////////////
  int  local_count[NUM_DIGITS];
  char num_str[BUFFER_SIZE];
  //////////////////////////////////////////////
  /**    ARRAY INITIALIZATION    **/
  for(i=0;i<NUM_DIGITS;i++)
    local_count[i] = 0;

  int local_sum;
  // For each process range;
  for(i=floor;i<=ceiling;i++){
    sprintf(num_str, "%d", i);
    while(strlen(num_str) > 1){
      local_sum = 0;
      for(j=0;j<strlen(num_str);j++)
        local_sum += num_str[j]-'0';	
      sprintf(num_str, "%d", local_sum);
    }
    local_count[*num_str-'0']++;
  }

  MPI_Barrier(MPI_COMM_WORLD);
  
  /** OUTPUT **/
  printf("rank %d local counts:[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d ]\n",
         my_rank,
         local_count[0],
         local_count[1],
         local_count[2],
         local_count[3],
         local_count[4],
         local_count[5],
         local_count[6],
         local_count[7],
         local_count[8],
         local_count[9]);

  MPI_Barrier(MPI_COMM_WORLD);
  
  /** MESSAGING **/
  for(i=0;i<NUM_DIGITS;i++)
    MPI_Reduce(local_count, global_count, i, MPI_INT, MPI_SUM, MASTER_RANK, MPI_COMM_WORLD);

  MPI_Barrier(MPI_COMM_WORLD);

  /** OUTPUT **/
  if(my_rank == MASTER_RANK)
    printf("final sum:[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d ]\n",
  	    global_count[0],
	    global_count[1],
            global_count[2],
	    global_count[3],
            global_count[4],
            global_count[5],
            global_count[6],
            global_count[7],
            global_count[8],
            global_count[9]);
  
  /** CLOSING PROCESSES **/
  MPI_Finalize();
  return 0;
}
