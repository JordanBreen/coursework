# Makefile for int tree programs
#
# Jordan Breen
#
# $Id$
#
CFILES=mpirds-tree.c
OFILES=$(CFILES:.c=.o)
CC=mpicc -g -Wall

slltest:	$(OFILES)
	$(CC) -o mpirds-tree $(OFILES) -lm

clean::
	/bin/rm -f mpirds-tree $(OFILES)
