CC=gcc
CXX=g++
CFLAGS= -std=c99 -Wall -O  -g 
EXECS= 03-findinpartiallysortedmatrix 04-replaceblankinstring 04-extension

all: $(EXECS)

utils:
	cd ./utils; $(MAKE)

03-findinpartiallysortedmatrix: 03-findinpartiallysortedmatrix.c
	$(CC) $(CFLAGS) -o $@ $^

04-replaceblankinstring: 04-replaceblankinstring.c
	$(CC) $(CFLAGS) -o $@ $^

04-extension: 04-extension.c
	$(CC) $(CFLAGS) -o $@ $^


.PHONY: clean
clean:
	rm -rf $(EXECS)
