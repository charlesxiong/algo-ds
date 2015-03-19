CC=gcc
CXX=g++
CFLAGS= -std=c99 -Wall -O  -g 
EXECS= 03-findinpartiallysortedmatrix 04-replaceblankinstring 04-extension 05-reverseprintlist

all: $(EXECS)

utils:
	cd ./utils; $(MAKE)

03-findinpartiallysortedmatrix: 03-findinpartiallysortedmatrix.c
	$(CC) $(CFLAGS) -o $@ $^

04-replaceblankinstring: 04-replaceblankinstring.c
	$(CC) $(CFLAGS) -o $@ $^

04-extension: 04-extension.c
	$(CC) $(CFLAGS) -o $@ $^

05-reverseprintlist: 05-reverseprintlist.c ./utils/linklist.o
	$(CC) $(CFLAGS) -o $@ $^


.PHONY: clean
clean:
	cd ./utils; $(MAKE) clean
	rm -rf $(EXECS)
