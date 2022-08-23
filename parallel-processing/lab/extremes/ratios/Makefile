# Makefile for ratios programs
#
# Jim Teresco, CS 322/324, Mount Holyoke College, CS 220, Siena College
# CSC 433, The College of Saint Rose
#
CFILES=ratio.c gcd.c ratio_example.c
OFILES=$(CFILES:.c=.o)
CC=gcc -g -Wall

ratio_example:	$(OFILES)
	$(CC) -o ratio_example $(OFILES)

clean::
	/bin/rm -f ratio_example $(OFILES)
