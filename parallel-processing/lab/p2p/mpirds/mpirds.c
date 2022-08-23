/* File: mpiexchange.c
 *
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <mpi.h>

/* Included as a part of Question 2 on Lab 4: */
double diffgettime(struct timeval tp1, struct timeval tp2);

typedef struct timeval timeval;

int main(void) {
  int my_rank, comm_sz, i, j, k, c, N = 1073741824; // ...Some large arbitrary number
  
   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   if(N % comm_sz != 0){
     fprintf(stderr, "Error: N is not evenly divisible by the number of processes ([N=%d] %% %d != 0)\n", N, comm_sz);
     MPI_Abort(MPI_COMM_WORLD, 1);
   }
   const int NUM_DIGITS  = 10;
   const int ADDER_RANK  = 0;
   const int DEFAULT_TAG = 0;
   
   int interval = N / comm_sz;
   int floor    = interval * my_rank;
   int ceiling  = (interval * (my_rank + 1)) - 1;
   int local_count[NUM_DIGITS];

   char num_str[20];
   // Init array to 0
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
   // Output: ///////////////////////////////////////////
   // Print each processes' local count
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

   // MPI_Send Section: /////////////////////////////////
   if(my_rank != 0) {
     MPI_Send(local_count,
	      NUM_DIGITS,
	      MPI_INT,
	      ADDER_RANK,
	      DEFAULT_TAG,
	      MPI_COMM_WORLD);
   }
   // MPI_Recv Section: /////////////////////////////////
   else{
     int global_count[NUM_DIGITS];
     for(c = 0; c < NUM_DIGITS; c++)
         global_count[c] = local_count[c];
     for(k = 1; k < comm_sz; k++){
       MPI_Recv(local_count,
		NUM_DIGITS,
	        MPI_INT,
		k,
	        DEFAULT_TAG,
		MPI_COMM_WORLD,
	        MPI_STATUS_IGNORE);
       for(c = 0; c < NUM_DIGITS; c++)
	 global_count[c] += local_count[c];
     }//!for(k)
     // Output: //////////////////////////////////////////
     // Global Count
     printf("global counts:[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d ]\n",
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
   }//!else
   
   /* Shut down MPI */
   MPI_Finalize();
   
   return 0;
}
