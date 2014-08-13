#ifndef _QUEUE_H_
#define _QUEUE_H_
#define MAX_QUEUE_SIZE 5
typedef int T;
typedef struct queue_node { //circular queue
	T elts[MAX_QUEUE_SIZE];
	int front; //the previous pointer to the first element of the queue 
	int rear; //the pointer to the last element of the queue
} queue_t; 

queue_t *init_queue();
void enqueue(queue_t *qt,T elt);
T dequeue(queue_t *qt);
T queue_peek(queue_t *qt);
int getsize(queue_t *qt);
int is_full(queue_t *qt);
int is_empty(queue_t *qt);
void foreach(queue_t *qt);


#endif