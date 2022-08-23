PROGRAM=final-project.exe
CFILES=main.c class.c descriptor.c gui.c id_group.c range.c resource.c school.c spell.c spell_level.c subschool.c sqlite_loader.c thread.c time_unit.c timer.c
OFILES=$(CFILES:.c=.o)
CC=gcc
CFLAGS=-g -Wall

$(PROGRAM):	$(OFILES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OFILES) -lm -lform -lmenu -lpanel -lncursesw -lsqlite3 -lpthread

clean::
	/bin/rm $(PROGRAM) $(OFILES) *.*~ *.core
