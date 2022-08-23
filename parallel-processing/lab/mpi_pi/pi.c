#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP_ARG 2
#define RET_ERR 1
#define RET_NRM 0
#define TAG_INC 0
#define TAG_APX 1

double rand_double(){
  return (double) rand() / (RAND_MAX);
}

double distance(double x, double y){
  return sqrt((x * x) + (y * y));
}

int main(int argc, char* argv[]){

  const int
    MAIN_RANK = 0;
  int
    lcl_rank,
    lcl_seed,
    num_proc,
    i;
  long int
    lcl_in_circle,
    gbl_max_circle,
    gbl_min_circle,
    num_rand = 0;
  double
    lcl_approx_pi,
    gbl_approx_pi = 0;


  if ((MPI_Init(&argc,&argv)) != MPI_SUCCESS) {
    fprintf(stderr,"Cannot initialize MPI\n");
    MPI_Abort(MPI_COMM_WORLD, RET_ERR);
  }

  MPI_Comm_rank(MPI_COMM_WORLD, &lcl_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

  // Only the main rank does this
  if(lcl_rank == MAIN_RANK){
    if (argc != EXP_ARG){
      fprintf(stderr, "%s::Invalid number of arguments\n", argv[0]);
      MPI_Abort(MPI_COMM_WORLD, RET_ERR);
    }
    if (!(num_rand = atol(argv[1]))){
      fprintf(stderr, "%s::Could not parse argv[1] to long int\n", argv[0]);
      MPI_Abort(MPI_COMM_WORLD, RET_ERR);
    }
    printf("Will use %ld points per process\n", num_rand);
  }
  
  MPI_Bcast(&num_rand, 1, MPI_LONG, MAIN_RANK, MPI_COMM_WORLD);

  // Every rank does this
  lcl_in_circle = 0;
  lcl_seed = lcl_rank;
  srand(lcl_seed);
  
  for(i = 0; i < num_rand; i++)
    if(distance(rand_double(), rand_double()) <= 1)
      lcl_in_circle++;
  
  lcl_approx_pi = (double)lcl_in_circle / num_rand * 4;

  // SEND SECTION
  MPI_Send(&lcl_in_circle, 1, MPI_INT,    MAIN_RANK, TAG_INC, MPI_COMM_WORLD);
  MPI_Send(&lcl_approx_pi, 1, MPI_DOUBLE, MAIN_RANK, TAG_APX, MPI_COMM_WORLD);

  // REDUCTION SECTION
  MPI_Reduce(&lcl_in_circle, &gbl_max_circle, 1, MPI_LONG,   MPI_MAX, MAIN_RANK, MPI_COMM_WORLD);
  MPI_Reduce(&lcl_in_circle, &gbl_min_circle, 1, MPI_LONG,   MPI_MIN, MAIN_RANK, MPI_COMM_WORLD);
  MPI_Reduce(&lcl_approx_pi, &gbl_approx_pi,  1, MPI_DOUBLE, MPI_SUM, MAIN_RANK, MPI_COMM_WORLD);
  
  // OUTPUT RESULTS
  if(lcl_rank == MAIN_RANK) {
    for(i = 0; i < num_proc; i++) {
      long int rec_in_circle = 0;
      double   rec_approx_pi = 0;
      MPI_Recv(&rec_in_circle, 1, MPI_INT,    i, TAG_INC, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Recv(&rec_approx_pi, 1, MPI_DOUBLE, i, TAG_APX, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("[%d] %ld in circle, pi approx = %.6lf\n", i, rec_in_circle, rec_approx_pi);
    }//!for
    printf("in circle values range from %ld to %ld\n", gbl_min_circle, gbl_max_circle);
    printf("Final approximation of pi: %.6lf\n", gbl_approx_pi / num_proc);
  }//!if
  
  MPI_Finalize();
  return RET_NRM;
}
