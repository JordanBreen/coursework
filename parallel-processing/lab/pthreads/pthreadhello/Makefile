# Makefile for pthread hello world program
#
# Jim Teresco, CS 338, Williams College
# CS 341, Mount Holyoke College
# CS 400, Siena College
#
CFILES=pthreadhello.c
OFILES=$(CFILES:.c=.o)
CC=gcc -g

pthreadhello:	$(OFILES)
	$(CC) -o pthreadhello $(OFILES) -lpthread

clean::
	/bin/rm -f pthreadhello $(OFILES)
