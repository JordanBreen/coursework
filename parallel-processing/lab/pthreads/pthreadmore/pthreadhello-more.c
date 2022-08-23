/*
  Jordan Breen
  Fall 2020
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;

void* thread(void *args);

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
