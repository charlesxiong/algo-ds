CC=gcc
CFLAGS= -std=c11 -Wall -O2 -g 
EXECS=bsearch_test bst_test uf_test sl_test

all: $(EXECS)

shared: 
	cd ../utils; $(MAKE) 

bsearch_test: binsearch_test.c binsearch.o ../utils/timer.o
	$(CC) $(CFLAGS) -o $@ $^

bst_test: bst_test.c bst.o ../utils/timer.o
	$(CC) $(CFLAGS) -o $@ $^

sl_test: skiplist_test.c skiplist.o 
	$(CC) $(CFLAGS) -o $@ $^ -lm

uf_test: uf_test.c uf.o 
	$(CC) $(CFLAGS) -o $@ $^

binsearch.o: binsearch.c binsearch.h
bst.o: bst.c bst.h
skiplist.o: skiplist.c skiplist.h
uf.o: uf.c uf.h

clean:
	cd ../utils; $(MAKE) clean
	rm -f *.o *~ $(EXECS)