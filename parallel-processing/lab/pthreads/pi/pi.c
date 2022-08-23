#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define EXP_ARG 2
#define RET_ERR 1
#define RET_NRM 0
#define TAG_INC 0
#define TAG_APX 1

int num_gen;

double rand_double();
double distance(double x, double y);

int main(int argc, char* argv[])
{
  const int
    MAIN_RANK = 0;
  int
    lcl_rank,
    lcl_seed,
    num_threads,
    i;
  long int
    lcl_in_circle,
    gbl_max_circle,
    gbl_min_circle,
    num_rand = 0;
  double
    lcl_approx_pi,
    gbl_approx_pi = 0;
  pthread_t*
    threads;


  if (argc != EXP_ARG+1)
  {
    fprintf(stderr, "%s::Invalid number of arguments\n", argv[0]);
    exit(0);
  }
  if (!(num_threads = atoi(argv[1])))
  {
    fprintf(stderr, "%s::Could not parse argv[1] to int\n", argv[0]);
    exit(0)
  }
  if (!(num_rand = atol(argv[2])))
  {
    fprintf(stderr, "%s::Could not parse argv[2] to long int\n", argv[0]);
    exit(0)
  }

  /*
int main(int argc, char *argv[])
{
  pthread_t* threads;
  int* vals;
  int i;

  thread_count = strtol(argv[1], NULL, 10);

  threads = (pthread_t*) malloc(thread_count * sizeof(pthread_t));
  vals    = (int*) malloc(thread_count * sizeof(int));

  for (i=0; i<thread_count; i++)
    vals[i] = i+1;

  for (i=0; i<thread_count; i++)
    if(pthread_create(&threads[i], NULL, thread, (void *)&(vals[i])) != 0)
      fprintf(stderr,"Could not create child thread %d\n", i);

  for (i=0; i<thread_count; i++)
    pthread_join(threads[i],NULL);

  printf("Goodbye from the main thread\n");

  return 0;
}

void* thread(void *args)
{
  int *val=(int *)args;
  printf("This is thread with val %d\n", *val);
  pthread_exit(0);
}
   */
  threads = (pthread_t*) malloc(thread_count * sizeof(pthread_t));
  for (i=0; i<thread_count; i++)
    if(pthread_create(&threads[i], NULL, thread, (void *)&(vals[i])) != 0)
      fprintf(stderr,"Could not create child thread %d\n", i);

  lcl_in_circle = 0;
  lcl_seed = pthread_self();
  srand(lcl_seed);
  
  for(i = 0; i < num_rand; i++)
    if(distance(rand_double(), rand_double()) <= 1)
      lcl_in_circle++;
  
  lcl_approx_pi = (double)lcl_in_circle / num_rand * 4;

  /*
  // SEND SECTION
  MPI_Send(&lcl_in_circle, 1, MPI_INT,    MAIN_RANK, TAG_INC, MPI_COMM_WORLD);
  MPI_Send(&lcl_approx_pi, 1, MPI_DOUBLE, MAIN_RANK, TAG_APX, MPI_COMM_WORLD);

  // REDUCTION SECTION
  MPI_Reduce(&lcl_in_circle, &gbl_max_circle, 1, MPI_LONG,   MPI_MAX, MAIN_RANK, MPI_COMM_WORLD);
  MPI_Reduce(&lcl_in_circle, &gbl_min_circle, 1, MPI_LONG,   MPI_MIN, MAIN_RANK, MPI_COMM_WORLD);
  MPI_Reduce(&lcl_approx_pi, &gbl_approx_pi,  1, MPI_DOUBLE, MPI_SUM, MAIN_RANK, MPI_COMM_WORLD);
  */
  
  // OUTPUT RESULTS
  for(i = 0; i < num_proc; i++)
  {
    long int rec_in_circle = 0;
    double   rec_approx_pi = 0;
    //MPI_Recv(&rec_in_circle, 1, MPI_INT,    i, TAG_INC, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //MPI_Recv(&rec_approx_pi, 1, MPI_DOUBLE, i, TAG_APX, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("[%d] %ld in circle, pi approx = %.6lf\n", i, rec_in_circle, rec_approx_pi);
  }//!for
  printf("in circle values range from %ld to %ld\n", gbl_min_circle, gbl_max_circle);
  printf("Final approximation of pi: %.6lf\n", gbl_approx_pi / num_proc);
  
  return RET_NRM;
}

double rand_double()
{
  return (double) rand() / (RAND_MAX);
}

double distance(double x, double y)
{
  return sqrt((x * x) + (y * y));
}

void* calc(void *args)
{
  int *val=(int *)args, i;
  for()
  pthread_exit(0);
}
