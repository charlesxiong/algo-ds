CC=gcc
CPP=g++
CFLAGS=-Wall -g -O2


all: asbline chainorder lcs optbst

asbline: asbline.o
	$(CPP) $(CFLAGS) -o asbline asbline.o

chainorder: chainorder.o
	$(CPP) $(CFLAGS) -o chainorder chainorder.o

lcs: lcs.o
	$(CPP) $(CFLAGS)  -o lcs lcs.o

optbst: optbst.o
	$(CPP) $(CFLAGS)  -o optbst optbst.o


asbline.o: asbline.cpp
chainorder.o: chainorder.cpp
lcs.o: lcs.cpp
optbst.o: optbst.cpp

clean: 
	rm *.o 