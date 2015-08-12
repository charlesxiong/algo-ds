CC=gcc
CXX=g++
CFLAGS= -std=c11 -Wall -O2 -g
CXXFLAGS= -std=c++11 -Wall -O2 -g 
EXECS=bsearch_test bst_test uf_test sl_test hashtbl_test trie_test

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

hashtbl_test: hashtbl_test.c hashtbl.o
	$(CC) $(CFLAGS) -o $@ $^

trie_test: trie_test.cpp trie.o
	$(CXX) $(CXXFLAGS) -o $@ $^

binsearch.o: binsearch.c binsearch.h
bst.o: bst.c bst.h
skiplist.o: skiplist.c skiplist.h
uf.o: uf.c uf.h
hashtbl.o: hashtbl.c hashtbl.h
trie.o: trie.cpp trie.h


clean:
	cd ../utils; $(MAKE) clean
	rm -f *.o *~ $(EXECS)