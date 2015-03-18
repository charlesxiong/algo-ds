CC=gcc
CFLAGS= -Wall -O2 -g
EXECS= timer_test linklist_test

all: $(EXECS)

timer_test: timer_test.c timer.o 
	$(CC) -o $@ $^

linklist_test: linklist_test.c linklist.o 
	$(CC) -o $@ $^


timer.o: timer.c timer.h
linklist.o: linklist.c linklist.h

.PHONY: clean
clean: 
	rm -f *.o *~ $(EXECS)

