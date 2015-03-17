CC=gcc
CFLAGS=-Wall -O2

all: testtimer

testtimer: testtimer.c timer.o 
	$(CC) -o $@ $^


timer.o: timer.c timer.h

.PHONY: clean
clean: 
	rm -f *.o *~ testtimer

