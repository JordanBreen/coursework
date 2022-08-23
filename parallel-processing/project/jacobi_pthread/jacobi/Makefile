CC=gcc -pthread -g -Wall
CFILES=timer.c grid.c jacobi.c
OFILES=$(CFILES:.c=.o)
jacobi:	$(OFILES)
	$(CC) -o jacobi $(OFILES)
jacobi.o:	timer.h grid.h
.c.o:
	$(CC) -c $<
clean::
	/bin/rm $(OFILES) jacobi
