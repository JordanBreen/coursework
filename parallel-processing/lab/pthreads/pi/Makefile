# Makefile for pi.c
#
# Jordan Breen
# 10/23/2021
#
CFILES=pi.c
OFILES=$(CFILES:.c=.o)
CC=gcc -g -Wall

mpicoll:	$(OFILES)
	$(CC) -o pi $(OFILES)

clean::
	/bin/rm -f pi $(OFILES)
