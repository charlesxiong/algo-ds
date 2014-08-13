CC=gcc
CPP=g++
CFLAGS=-Wall
EXECUTABLE=array stack queue linkedqueue linklist telemag

all: $(EXECUTABLE)

array: arraylist.o testarraylist.c
	$(CC) $(CFLAGS) arraylist.o testarraylist.c -o array

stack : stack.o teststack.c
	$(CC) $(CFLAGS) stack.o teststack.c -o stack

queue : queue.o testqueue.c
	 $(CC) $(CFLAGS) queue.o testqueue.c -o queue

linkedqueue : linkedqueue.o testlinkedqueue.c
	 $(CC) $(CFLAGS) linkedqueue.o testlinkedqueue.c -o linkedqueue

linklist: linklist.o testlist.c 
	$(CC) $(CFLAGS) linklist.o testlist.c -o list

telemag: telemag.cpp
	$(CPP) $(CFLAGS) telemag.cpp -o telemag
       
arraylist.o: arraylist.c arraylist.h
linkedlist.o: linklist.c linklist.h
stack.o: stack.c stack.h
queue.o: queue.c queue.h
linkedqueue.o: linkedqueue.c linkedqueue.h


 

clean:
	rm -rf *.o *~ $(EXECUTABLE)
