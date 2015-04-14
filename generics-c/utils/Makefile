CC=gcc
CFLAGS= -std=c11 -Wall -O -g
EXECS= timer_test linklist_test stack_test queue_test bintree_test 

all: $(EXECS)

timer_test: timer_test.c timer.o 
	$(CC) $(CFLAGS) -o $@ $^

linklist_test: linklist_test.c linklist.o 
	$(CC) $(CFLAGS) -o $@ $^

stack_test: stack_test.c stack.o 
	$(CC) $(CFLAGS) -o $@ $^

queue_test: queue_test.c queue.o 
	$(CC) $(CFLAGS) -o $@ $^

bintree_test: bintree_test.c bintree.o 
	$(CC) $(CFLAGS) -o $@ $^

timer.o: timer.c timer.h
linklist.o: linklist.c linklist.h
stack.o: stack.c stack.h
queue.o: queue.c queue.h
bintree.o: bintree.c bintree.h

.PHONY: clean
clean: 
	rm -f *.o *~ $(EXECS)

