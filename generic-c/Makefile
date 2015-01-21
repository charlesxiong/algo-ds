CC=gcc
CPP=g++
CFLAGS=-Wall -g
EXECUTABLE=array genarray linklist  stack genstack queue linkedqueue 

all: $(EXECUTABLE)

array: arraylist.o testarraylist.c
	$(CC) $(CFLAGS) arraylist.o testarraylist.c -o array
genarray: genarraylist.o testgenarraylist.c
	$(CC) $(CFLAGS) genarraylist.o testgenarraylist.c -o genarray
linklist: linklist.o testlist.c 
	$(CC) $(CFLAGS) linklist.o testlist.c -o linklist
stack: stack.o teststack.c
	$(CC) $(CFLAGS) stack.o teststack.c -o stack
genstack: genstack.o testgenstack.c
	$(CC) $(CFLAGS) genstack.o testgenstack.c -o genstack
queue: queue.o testqueue.c
	 $(CC) $(CFLAGS) queue.o testqueue.c -o queue
linkedqueue: linkedqueue.o testlinkedqueue.c
	 $(CC) $(CFLAGS) linkedqueue.o testlinkedqueue.c -o linkedqueue




arraylist.o: arraylist.c arraylist.h
genarraylist.o: genarraylist.c genarraylist.h
linkedlist.o: linklist.c linklist.h
stack.o: stack.c stack.h
genstack.o: genstack.c genstack.h
queue.o: queue.c queue.h
linkedqueue.o: linkedqueue.c linkedqueue.h

clean:
	rm -rf *.o *~ $(EXECUTABLE)
