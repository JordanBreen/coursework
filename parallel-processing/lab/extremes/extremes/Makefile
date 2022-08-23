# Makefile for extremes programs
# Jordan Breen
CFILES= extremes.c file_format.c graph.c graph_data.c waypoint.c
OFILES=$(CFILES:.c=.o)
CC=gcc -g -Wall

extremes:	$(OFILES)
	 $(CC) -o extremes $(OFILES)

clean::
	/bin/rm -f extremes $(OFILES)
