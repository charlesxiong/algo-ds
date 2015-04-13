CC=gcc
CXX=g++
CFLAGS= -std=c99 -Wall -O2 -g 
EXECS= 03-findinpartiallysortedmatrix 04-replaceblankinstring 04-extension 05-reverseprintlist \
08-minnuminrotatedarray 09-fibonacci 28-stringpermutation  \

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

08-minnuminrotatedarray: 08-minnuminrotatedarray.c
	$(CC) $(CFLAGS) -o $@ $^

09-fibonacci: 09-fibonacci.cpp
	$(CXX) -Wall -O2 -g -o $@ $^

28-stringpermutation: 28-stringpermutation.c 
	$(CC) $(CFLAGS) -o $@ $^


.PHONY: clean
clean:
	cd ./utils; $(MAKE) clean
	rm -f *.o
	$(MAKE) cleanbin

.PHONY: cleanbin
cleanbin:
	rm -rf $(EXECS)
