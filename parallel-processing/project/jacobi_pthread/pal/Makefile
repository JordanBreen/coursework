# Makefile for palindrome.c
#
# Jordan Breen
# 10/23/2021
#
CFILES=palindrome.c timer.c
OFILES=$(CFILES:.c=.o)
MAIN_CC=gcc -pthread -g -Wall
ALT_CC=gcc -g -Wall
.DEFAULT_GOAL:=all

all: palindrome process_results

palindrome:	$(OFILES)
	$(MAIN_CC) -o palindrome $(OFILES)

process_results: process_results.c
	$(ALT_CC) -o process_results process_results.c

clean::
	/bin/rm -f palindrome process_results $(OFILES)

