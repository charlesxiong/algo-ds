#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t *init_queue(){
	queue_t *qt=(queue_t *)malloc(sizeof(queue_t));
	qt->front=0;
	qt->rear=0;
	return qt;
}

int is_full(queue_t *qt){
	return ((qt->rear+1)%MAX_QUEUE_SIZE==qt->front)?1:0;
}

int is_empty(queue_t *qt){
	return (qt->front==qt->rear)?1:0;
}

int getsize(queue_t *qt){
	return (qt->rear-qt->front+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
}

void enqueue(queue_t *qt,T elt){
	if(is_full(qt)) {
		printf("The queue is full");
		return;
	}
	qt->rear=(qt->rear+1)%MAX_QUEUE_SIZE;
	qt->elts[qt->rear]=elt;
}

T dequeue(queue_t *qt){
	if(is_empty(qt)){
		printf("The queue is empty");
		return -1;
	}
	qt->front=(qt->front+1)%MAX_QUEUE_SIZE;
	return qt->elts[qt->front];
}

T queue_peek(queue_t *qt){
	return qt->elts[(qt->front+1)%MAX_QUEUE_SIZE];
}

void foreach(queue_t *qt){
	int i;
	for(i=0;i<getsize(qt);i++)
		printf("%d ",qt->elts[i+1]);
	printf("\n");
}