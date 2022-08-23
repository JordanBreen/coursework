# Makefile for int tree programs
#
# Jordan Breen
#
# $Id$
#
CFILES=mpirds-reduce.c
OFILES=$(CFILES:.c=.o)
CC=mpicc -g -Wall

slltest:	$(OFILES)
	$(CC) -o mpirds-reduce $(OFILES) -lm

clean::
	/bin/rm -f mpirds-reduce $(OFILES)
