CC=gcc
CFLAGS=-O2 -g 

all: bsearch_test

shared: 
	cd ../utils; $(MAKE) 

bsearch_test: binsearch_test.c binsearch.o ../utils/timer.o
	$(CC) $(CFLAGS) -o $@ $^

binsearch.o: binsearch.c binsearch.h

clean:
	cd ../utils; $(MAKE) clean
	rm -f *.o *~ bsearch_test