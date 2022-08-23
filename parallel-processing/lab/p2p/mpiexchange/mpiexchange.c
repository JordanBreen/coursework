/* File: mpiexchange.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>

/* Included as a part of Question 2 on Lab 4: */
double diffgettime(struct timeval tp1, struct timeval tp2);

typedef struct timeval timeval;

int main(void) {
  int my_rank, comm_sz, local_int = 25; // ...Some arbitrary number 

   timeval start_time, end_time;
   double  elapsed_time;
   gettimeofday(&start_time, NULL);
   
   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

   if(comm_sz != 2){
     fprintf(stderr, "Error: Invalid number of processes, was expecting 2.\n");
     exit(1);
   }
   
   /* Recieve, Calculate, Send Back */
   if (my_rank != 0){
      MPI_Recv(&local_int, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%d recieved %d from %d\n", my_rank, local_int, 0);

      local_int *= 2;   
      MPI_Send(&local_int, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      printf("%d sending %d to %d\n", my_rank, local_int, 0);
   }
   /* Send, Wait, Recieve Altered Send*/
   else {
      MPI_Send(&local_int, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      printf("%d sending %d to %d\n", my_rank, local_int, 1);
   }

   /* Print the result */
   if (my_rank == 0) {
      MPI_Recv(&local_int, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%d recieved %d from %d\n", my_rank, local_int, 1);
   }
   /* Shut down MPI */
   MPI_Finalize();

   /* Output elapsed time of each process */
   gettimeofday(&end_time, NULL);
   elapsed_time = diffgettime(start_time, end_time);
   printf("Elapsed Time: %10.1f ms\n", elapsed_time);
   
   return 0;
}
double diffgettime(struct timeval tp1, struct timeval tp2) {
   int delta[2] ;

   delta[0] = tp2.tv_sec  - tp1.tv_sec;
   delta[1] = tp2.tv_usec - tp1.tv_usec;

   /*  See if we've wrapped and deal with it accordingly: */
   if( delta[1] < 0 ) {
       delta[0] = delta[0] - 1;
       delta[1] = delta[1] + 1000000;
    }

   return( (double) delta[0] + (double) delta[1]*1.0E-6 );
}
