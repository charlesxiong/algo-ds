CC=gcc
CFLAGS=-Wall -O2 -g 
EXECS=bsearch_test bst_test

all: $(EXECS)

shared: 
	cd ../utils; $(MAKE) 

bsearch_test: binsearch_test.c binsearch.o ../utils/timer.o
	$(CC) $(CFLAGS) -o $@ $^

bst_test: bst_test.c bst.o ../utils/timer.o
	$(CC) $(CFLAGS) -o $@ $^

binsearch.o: binsearch.c binsearch.h
bst.o: bst.c bst.h

clean:
	cd ../utils; $(MAKE) clean
	rm -f *.o *~ $(EXECS)