/*
  CS 322/324 Example Code
  Mount Holyoke College
  CS 220/CS 335, Siena College
  CSC 433, The College of Saint Rose
  Jim Teresco

  ratio-related functions
*/

#include <stdlib.h>
#include <stdio.h>
#include "ratio.h"
#include "gcd.h"

/* create a new ratio structure with the given numerator and denominator */
ratio *create_ratio(int numerator, int denominator) {
  ratio *r = (ratio *)malloc(sizeof(ratio));

  r->numerator = numerator;
  r->denominator = denominator;

  return r;
}

/* add two ratios, return result in lowest terms */
ratio *add_ratios(ratio *rat1, ratio *rat2) {
  ratio *r = (ratio *)malloc(sizeof(ratio));

  r->numerator = ((rat1->numerator * rat2->denominator) +
		  (rat2->numerator * rat1->denominator));
  r->denominator = rat1->denominator * rat2->denominator;

  reduce_ratio(r);

  return r;
}

/* reduce ratio to lowest terms */
void reduce_ratio(ratio *r) {

  int div = gcd(r->numerator, r->denominator);
  r->numerator /= div;
  r->denominator /= div;
}

/* print out a ratio */
void print_ratio(ratio *r) {

  printf("%d/%d", r->numerator, r->denominator);
}
