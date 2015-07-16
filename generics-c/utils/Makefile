CC=gcc
CFLAGS= -std=c11 -Wall -g -O2
EXECS= timer_test dynarr_test linklist_test dlinklist_test \
stack_test queue_test bintree_test bitmap_test sort_test \


all: $(EXECS)

timer_test: timer_test.c timer.o 
	$(CC) $(CFLAGS) -o $@ $^

dynarr_test: dynarr_test.c dynarr.o
	$(CC) $(CFLAGS) -o $@ $^

linklist_test: linklist_test.c linklist.o 
	$(CC) $(CFLAGS) -o $@ $^

dlinklist_test: dlinklist_test.c dlinklist.o 
	$(CC) $(CFLAGS) -o $@ $^

stack_test: stack_test.c stack.o 
	$(CC) $(CFLAGS) -o $@ $^

queue_test: queue_test.c queue.o 
	$(CC) $(CFLAGS) -o $@ $^

bintree_test: bintree_test.c bintree.o 
	$(CC) $(CFLAGS) -o $@ $^

bitmap_test: bitmap_test.c bitmap.o
	$(CC) $(CFLAGS) -o $@ $^

sort_test: sort_test.c sort.o
	$(CC) $(CFLAGS) -o $@ $^

timer.o: timer.c timer.h
dynarr.o: dynarr.c dynarr.h
linklist.o: linklist.c linklist.h
dlinklist.o: dlinklist.c dlinklist.h
stack.o: stack.c stack.h
queue.o: queue.c queue.h
bintree.o: bintree.c bintree.h
bitmap.o: bitmap.c bitmap.h
sort.o: sort.c sort.h

.PHONY: clean
clean: 
	rm -f *.o *~ $(EXECS)

