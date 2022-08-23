/*
  CS 322/324 Example Code
  Mount Holyoke College
  CS 220/CS 335, Siena College
  CSC 433, The College of Saint Rose
  Jim Teresco

  ratio example program: a demonstration of messy C memory management

  Draw pictures!
*/

#include <stdio.h>
#include <stdlib.h>
#include "ratio.h"

int main(int argc, char *argv[]) {
  /* pointers to ratios */
  ratio *r1, *r2, *ans;

  /* pointer to a dynamically-allocated array of ratio pointers */
  ratio **r_array1;

  /* a statically-allocated array of pointers to ratios */
  ratio *r_array2[3];

  /* a statically-allocated array of ratios (rather than pointers) */
  ratio r_array3[3];

  int i;

  /* First, we'll add together a couple of ratios */
  r1 = create_ratio(1, 3);
  r2 = create_ratio(1, 6);

  ans = add_ratios(r1, r2);

  /* At this point, the variables r1, r2, and ans refer to ratio
     structures that were allocated by malloc in create_ratio
     or add_ratios */

  print_ratio(r1);
  printf(" + ");
  print_ratio(r2);
  printf(" = ");
  print_ratio(ans);
  printf("\n");

  /* and we clean up our memory from this operation before continuing */
  free(r1);
  free(r2);
  free(ans);

  /* at this point, r1, r2, and ans are still pointers to the memory we
     have returned to the system, but it would be problematic if we were
     to access that memory after the free calls */

  /* Next, we'll allocate an array of 3 ratios */
  /* We need to request a chunk of space large enough to hold an 
     array of three pointers to ratios */

  r_array1 = (ratio **)malloc(3*sizeof(ratio *));

  /* now we'll put some ratios in there and reduce them */
  r_array1[0] = create_ratio(15, 24);
  r_array1[1] = create_ratio(3, 6);
  r_array1[2] = create_ratio(9, 16);

  /* Now, the three entries of our array contain pointers to ratio
     structures that were allocated by malloc in create_ratio calls */

  for (i=0; i<3; i++) {
    print_ratio(r_array1[i]);
    printf(" reduces to ");
    reduce_ratio(r_array1[i]);
    print_ratio(r_array1[i]);
    printf("\n");
  }

  /* before we clean up from this one, let's store pointers to two of
     these three ratios in our static array of pointers to ratios */
  r_array2[0] = r_array1[0];
  r_array2[1] = r_array1[1];

  /* and we'll free the memory of the third */
  free(r_array1[2]);

  /* and now we'll give back the memory for our dynamic array */
  free(r_array1);

  /* Now, we'll add the two in the static array and store the pointer
     to the answer in the third */
  r_array2[2] = add_ratios(r_array2[0], r_array2[1]);

  print_ratio(r_array2[0]);
  printf(" + ");
  print_ratio(r_array2[1]);
  printf(" = ");
  print_ratio(r_array2[2]);
  printf("\n");

  /* and now we'll clean up these three */
  for (i=0; i<3; i++) {
    free(r_array2[i]);
  }

  /* and r_array2 does not need to be cleaned up */

  /* Finally, we experiment with the static array of
     statically-allocated ratios */
  /* these need to be dealt with differently! */
  r_array3[0].numerator = 10;
  r_array3[0].denominator = 13;
  r_array3[1].numerator = 4;
  r_array3[1].denominator = 10;
  r_array3[2].numerator = 8;
  r_array3[2].denominator = 9;

  /* let's reduce them */
  for (i=0; i<3; i++) {
    print_ratio(&r_array3[i]); /* note the & operator to get a pointer! */
    printf(" reduces to ");
    reduce_ratio(&r_array3[i]);
    print_ratio(&r_array3[i]);
    printf("\n");
  }

  /* and none of these need to be cleaned up, since these statically-allocated
     structures will be deallocated automatically when main returns */

  return 0;
}
