#ifndef _LINKEDQUEUE_H_
#define _LINKEDQUEUE_H_
#include <stdlib.h>

typedef int T;
typedef struct linknode {
	T elt;
	struct linknode *next;
} linknode;

typedef struct {
	linknode *head; //dummy header
	linknode *front;
	linknode *rear;
	int tag; //the mark of empty queue
} linked_queue_t;

linked_queue_t *init_linked_queue();
void enqueue(linked_queue_t *lqt, T elt);
T dequeue(linked_queue_t *lqt);
int is_empty(linked_queue_t *lqt);
T queue_peek(linked_queue_t *lqt);
void traversal(linked_queue_t *lqt);

static inline linknode *
createnode(T elt,linknode *next){
	linknode *new_node=(linknode *)malloc(sizeof(linknode));
	new_node->elt=elt;
	new_node->next=next;
	return new_node;
}


#endif 