#include<ctype.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

#include"timer.h"

#define NUM_LETTERS 26
#define NUM_TASKS   26

typedef struct task
{
  char alpha;
  int  index;
} task;

typedef struct tinfo
{
  pthread_t
    thread_id;
  int
    thread_num,
    *next_task,
    jobs_done,
    pal_found,
    num_words;
  task
   **tasks;
  pthread_mutex_t
    *mutex;
  double
    thread_elapsed_time;
} tinfo;

char **words;
task **tasks;
tinfo *thread_info;

char  *strrev         ( char *str );
int    indexOf        ( char c );
char **ptrToFirst     ( char c );
int    alphaEqual     ( char a, char b );
void  *worker         ( void *arg );
void   print_results  ( const int NUM_THREADS );
void   findPalindromes( const int FLOOR, const int CEILING, int* pal );

// expected arguments...
// argv[0] -> (str) program name (auto)
// argv[1] -> (int) maximum word length in dictionary, determined by shell script run.sh
// argv[2] -> (int) number of words in dictionary, determined by shell script run.sh
// argv[3] -> (str) filepath to dictionary
// argv[4] -> (str) filepath to output
// argv[5] -> (int) test number
// argv[6] -> (int) number of processes
int main(int argc, char *argv[])
{
  const char
    *PROGRAM_NAME     = argv[0],
    *INPUT_FILE_NAME  = argv[3],
    *OUTPUT_FILE_NAME = argv[4],
    FILE_DELIMINATOR  = ','; 
  const int
    MAX_WORD_LEN = atoi(argv[1]),
    NUM_WORDS    = atoi(argv[2]),
    CUR_TEST_NUM = atoi(argv[5]),
    NUM_THREADS  = atoi(argv[6]);    
  char
    letter = '?', c;
  int
    i, next_task, num_pal; // for bag of tasks
  FILE
    *in_fp,
    *out_fp;
  struct timeval
    start_time,
    end_time;
  double
    elapsed_time;
  pthread_mutex_t   mutex;
  
  // Print intro header, displays program name and number of threads
  printf("-------------- Welcome to %s --------------\n", PROGRAM_NAME);
  printf("Using %02d thread(s)\n", NUM_THREADS);
  num_pal = next_task = 0;
  words = (char**)malloc(NUM_WORDS*sizeof(char*));
  // Initialize pthread component(s)
  pthread_mutex_init(&mutex, NULL);
  // Create a number of threads equal to the user argument
  thread_info = (tinfo*)malloc(NUM_THREADS*sizeof(tinfo));
  // Create a task for each letter of the alphabet
  tasks = (task**)malloc(NUM_TASKS*sizeof(task*));
  for (i=0; i<NUM_TASKS; i++)
  {
    tasks[i]=(task*)malloc(sizeof(task));
    tasks[i]->alpha = i+'a';
  }
  // Check if file was successfully opened
  if (!(in_fp=fopen(INPUT_FILE_NAME,"r")))
  {
    fprintf(stderr, "Cannot open input file %s for reading.\n", INPUT_FILE_NAME);
    exit(1);
  }
  else
  {
    // Loading words into string array and finding their first positions
    i = -1;
    while (fscanf(in_fp, "%s",(words[++i]=(char*)malloc(MAX_WORD_LEN*sizeof(char)))) != EOF)
      // IF: A letter and its lowercase != the current letter, we've found a first position
      if (isalpha(c=words[i][0]) && letter!=(c=(isupper(c))?c+32:c))
        tasks[(letter=c)-'a']->index = i;
    fclose(in_fp);
  }
  // Start timer
  gettimeofday(&start_time, NULL);
  // For each thread, initialize and do work
  for (i=0; i<NUM_THREADS; i++)
  {
    thread_info[i].thread_num = i;
    thread_info[i].tasks = tasks;
    thread_info[i].num_words = NUM_WORDS;
    thread_info[i].next_task = &next_task;  // shared
    thread_info[i].mutex = &mutex;          // shared
    thread_info[i].jobs_done = 0;
    thread_info[i].pal_found = 0;          
    pthread_create(&(thread_info[i].thread_id), NULL, worker, &(thread_info[i]));
  }
  for (i=0; i<NUM_THREADS; i++) pthread_join(thread_info[i].thread_id, NULL);
  // After thread join, get time
  gettimeofday(&end_time, NULL);
  elapsed_time = diffgettime(start_time, end_time);
  // For each thread, output results and join, thread work is done
  print_results(NUM_THREADS);
  for (i=0; i<NUM_THREADS; i++) num_pal += thread_info[i].pal_found;
  printf("total time elapsed (sec) -> %03.5lf\n", elapsed_time);
  printf("total palindromes found  -> %03d\n", num_pal);
  if (!(out_fp=fopen(OUTPUT_FILE_NAME,"a")))
  {
    fprintf(stderr, "Cannot open output file %s for writing.\n", OUTPUT_FILE_NAME);
    exit(1);
  }
  else
  {
    fprintf(out_fp, "%d%c%d%c%lf\n", CUR_TEST_NUM, FILE_DELIMINATOR, NUM_THREADS, FILE_DELIMINATOR, elapsed_time);
    fclose(out_fp);
  }
  pthread_mutex_destroy(&mutex);
  // Free/return allocated memory
  for (i = 0; i < NUM_TASKS; i++) free(tasks[i]);
  free(tasks);
  free(thread_info);
  for (i = 0; i < NUM_WORDS; i++) free(words[i]);
  free(words);
  // Exit program
  return 0;
}

// reverses string argument and returns it, returns null on bad input
char *strrev(char *str)
{
  char *head, *tail, *out;
  // returns bad input
  if (!str || !*str) return str;
  out = (char*)malloc((strlen(str)*sizeof(char))+1);
  out = strcpy(out, str);
  for (head=out, tail=out+strlen(out)-1; tail>head; ++head,--tail)
  {
    // XOR bitshifting does a value swap between head and tail
    *head ^= *tail;
    *tail ^= *head;
    *head ^= *tail;
  }
  // returns reversed input
  return out;
}

// returns the index of the alphabetical char argument, (a=0, A=0, b=1, B=1, ...)
int indexOf(char c)
{
  if(isalpha(c))
    return c-((isupper(c))?'A':'a');
  else
    return -1;
}

// Makes case insensitive character comparison between two alphabetical values
int alphaEqual(char a, char b)
{
  return (isalpha(a) && isalpha(b)) && ( (a==b) || (a==(b+32)) || (b==(a+32)) );
}

// searches in range of the first letter of the reversed word for a palindromic match
void findPalindromes(const int FLOOR, const int CEILING, int *pal)
{
  int  x, y, z;
  char *rev;
  // range is, in the example of 'a', the first appearance of 'a',
  // to the last appearence of 'a' in our amassed collection of words.
  for (x=FLOOR; x<CEILING; x++)
  {
    rev = strrev(words[x]);
    // if the reversed string starts with a letter
    if((y=indexOf(rev[0]))!=-1)
    {
      y=(tasks[y]->index);
      // while the first characters match
      while (alphaEqual(words[y][0], rev[0]))
      {
        z=0;
	// while the words are equal (up to pos 'k')
        while (alphaEqual(words[y][z], rev[z])) z++;
	// if we get to the end of the word and they still match
        if(!words[y][z] && !rev[z] && ++(*pal)) break;
	// words do not match, proceed to next word
        y++;
      }
    }
    free(rev);
  }
}

void print_results(const int NUM_THREADS)
{
  int i;
  printf("thread | job(s) | palidromes found | time elapsed\n");
  for (i=0; i<NUM_THREADS; i++)
    printf("%6d | %6d | %16d | %.2lf sec\n",
	   i, thread_info[i].jobs_done,
	   thread_info[i].pal_found,
	   thread_info[i].thread_elapsed_time);
}

void *worker(void *arg)
{
  tinfo *ti = (tinfo *)arg;
  struct timeval start_time_local, end_time_local;
  // start the local timer
  gettimeofday(&start_time_local, NULL);
  char
    my_alpha;
  int
    my_index,
    my_task = -1,
    FLOOR,
    CEILING;  
  while (1)
  {
    // grab a task from the bag, atomic operation
    pthread_mutex_lock(ti->mutex);
    my_task = *ti->next_task;
    *ti->next_task += 1;
    pthread_mutex_unlock(ti->mutex);
    // if trying to do a task outside of task range
    if (my_task >= NUM_TASKS) break;
    // if trying to do an actual task, proceed to do the task
    my_alpha = ti->tasks[my_task]->alpha;
    my_index = ti->tasks[my_task]->index;
    FLOOR    = my_index;
    CEILING  = (my_alpha != 'z') ? (ti->tasks[(my_alpha-'a')+1])->index : ti->num_words;
    findPalindromes(FLOOR, CEILING, &(ti->pal_found));
    ti->jobs_done++;
  }
  // get local elapsed time and store it in thread info collection
  gettimeofday(&end_time_local, NULL);
  ti->thread_elapsed_time = diffgettime(start_time_local, end_time_local);
  return NULL;
}
