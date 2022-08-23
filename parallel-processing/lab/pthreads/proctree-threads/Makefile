# Makefile for pthread tree program
#
# Jim Teresco, CS 338, Williams College
# CS 341, Mount Holyoke College
# CS 400, Siena College
#
CFILES=proctree_threads.c
OFILES=$(CFILES:.c=.o)
CC=gcc -g

proctree_threads:	$(OFILES)
	$(CC) -o proctree_threads $(OFILES) -lpthread

clean::
	/bin/rm -f proctree_threads $(OFILES)
