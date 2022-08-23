/*
  C implementation of insertion sort functions

  CSIS 220, Siena College
  CSC 381, The College of Saint Rose
  CSIS 301, Siena College

  Jim Teresco, code based on examples from David Hemmendinger.
*/

#include <stdio.h>

/*  A standard insertion sort for an integer array */
void isort(int a[], int asize) {
  int i, j, tmp;

  for (i = 1; i < asize; i++) {
    j = i;
    tmp = a[i];
    while ((j > 0) && (a[j-1] > tmp)) {
      a[j] = a[j-1];
      j--;
    }
    a[j] = tmp;
  }
}

/*  The same, done with pointers and pointer arithmetic */
void isortptr(int *a, int asize) {
  int *p = a;
  int *q;
  int tmp;

  for (++p;  p < a+asize; p++) {
    q = p;
    tmp = *p;
    while ((q > a) && (*(q-1) > tmp)) {
      *q = *(q-1);
      q--;
    }
    *q = tmp;
  }
}

/* print the contents of an array, space separated, on one line */
void print_array(int a[], int asize) {
  int i;

  for (i=0; i<asize; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

/* The same, done with pointers and pointer arithmetic */
void print_array_ptr(int *a, int asize){
  int *p = a;
  while(p < a+asize)
    printf("%d ", *p++);
  printf("\n");
}

/* driver for testing */
int main() {

  int thearray[10];
  thearray[0] = 16;
  thearray[1] = 43;
  thearray[2] = -1;
  thearray[3] = 9383;
  thearray[4] = -17;
  thearray[5] = 23;
  thearray[6] = 23;
  thearray[7] = 7;
  thearray[8] = -913;
  thearray[9] = 0;

  printf("Before sorting: ");
  print_array(thearray, 10);

  /* replace with isortptr to test pointer-based subroutine */
  isort(thearray, 10);

  printf("After sorting: ");
  print_array(thearray, 10);

  return 0;
}
