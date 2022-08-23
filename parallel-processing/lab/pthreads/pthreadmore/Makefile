CFILES=pthreadhello-more.c
OFILES=$(CFILES:.c=.o)
CC=gcc -g

pthreadhello:	$(OFILES)
	$(CC) -o pthreadhello-more $(OFILES) -lpthread

clean::
	/bin/rm -f pthreadhello-more $(OFILES)
