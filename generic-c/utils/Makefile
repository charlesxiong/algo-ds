CC=gcc
CFLAGS=-Wall -g -O2　

all: timer_test


timer_test: timer_test.c timer.o 
	$(CC) -o $@ $^


timer.o: timer.c timer.h

.PHONY: clean
clean: 
	rm -f *.o *~ testtimer

