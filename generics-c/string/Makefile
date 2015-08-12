CC=gcc
CXX=g++
CFLAGS= -std=c11 -Wall -O2 -g
CXXFLAGS= -std=c++11 -Wall -O2 -g 
EXECS=trie_test

all: $(EXECS)

shared: 
	cd ../utils; $(MAKE) 

trie_test: trie_test.cpp trie.o
	$(CXX) $(CXXFLAGS) -o $@ $^


trie.o: trie.cpp trie.h


clean:
	cd ../utils; $(MAKE) clean
	rm -f *.o *~ $(EXECS)
