CC=gcc
CFLAGS= -std=c11 -Wall -g -O2
EXECS= stopwatch_test 


all: $(EXECS)

stopwatch_test: stopwatch_test.c stopwatch.o 
	$(CC) $(CFLAGS) -o $@ $^

stopwatch.o: stopwatch.c stopwatch.h


.PHONY: clean
clean: 
	rm -f *.o *~ $(EXECS)

