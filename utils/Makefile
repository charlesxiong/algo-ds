CC=gcc
CFLAGS= -std=c11 -Wall -g -O2
EXECS= timer_test 


all: $(EXECS)

timer_test: timer_test.c timer.o 
	$(CC) $(CFLAGS) -o $@ $^

timer.o: timer.c timer.h


.PHONY: clean
clean: 
	rm -f *.o *~ $(EXECS)

