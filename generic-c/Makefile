CC=gcc
CFLAGS=-Wall -g
EXEC=array genarray linklist stack genstack queue linkedqueue 

all: $(EXEC)

# 　bench测试使用自动变量
array: testarraylist.c arraylist.o 
	$(CC) $(CFLAGS) -o $@ $^
genarray: testgenarraylist.c genarraylist.o 
	$(CC) $(CFLAGS) -o $@ $^
linklist: testlist.c  linklist.o 
	$(CC) $(CFLAGS) -o $@ $^
stack: teststack.c stack.o 
	$(CC) $(CFLAGS) -o $@ $^
genstack: testgenstack.c genstack.o 
	$(CC) $(CFLAGS) -o $@ $^
queue: testqueue.c queue.o 
	 $(CC) $(CFLAGS)-o $@ $^
linkedqueue: testlinkedqueue.c linkedqueue.o 
	 $(CC) $(CFLAGS) -o $@ $^


# *.o : *.c *.h使用隐含规则
arraylist.o: arraylist.c arraylist.h
genarraylist.o: genarraylist.c genarraylist.h
linkedlist.o: linklist.c linklist.h
stack.o: stack.c stack.h
genstack.o: genstack.c genstack.h
queue.o: queue.c queue.h
linkedqueue.o: linkedqueue.c linkedqueue.h

.PHONY: clean
clean:
	rm -rf *.o *~ $(EXEC)
