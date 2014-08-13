#include <stdio.h>
#include "linkedqueue.h"

linked_queue_t *init_linked_queue(){
	linked_queue_t *lqt=(linked_queue_t *)malloc(sizeof(linked_queue_t));
	lqt->head=(linknode *)malloc(sizeof(linknode));
	lqt->head->next=lqt->front=lqt->rear;
	lqt->front=NULL;
	lqt->rear=NULL;
	lqt->tag=0;
	return lqt;
}


void enqueue(linked_queue_t *lqt, T elt){
	linknode *tmp=createnode(elt,NULL);
	if(lqt->front==NULL){ //queue is empty
		lqt->head->next=tmp;
		lqt->front=tmp;	
		lqt->tag=1;
	} else if (lqt->rear == lqt->front){  //queue has one node
		lqt->front->next=tmp;
	} else { //queue has more than one node
		lqt->rear->next=tmp;
	}
	lqt->rear=tmp;
}



int is_empty(linked_queue_t *lqt){
	// if(lqt->front==lqt->rear){
	// 	return (lqt->tag==1)? 0:1;
	// }
	// return 0;
	return (lqt->tag==0)?1:0;
}

T dequeue(linked_queue_t *lqt){
	if(lqt->tag==1) {
		linknode *cur=lqt->front;
		T elt=cur->elt;
		if(lqt->front==lqt->rear){ //queue has only one node,   set the tag =0  if dequeueing the node
			lqt->tag=0;
			lqt->head->next=NULL;
			lqt->front=lqt->rear=NULL;
			
		} else {
			lqt->head->next=cur->next;
			lqt->front=cur->next;
		}
		free(cur);
		return elt;
	} else {
		printf("The queue is empty!\n");
		return -1;
	}
}

T queue_peek(linked_queue_t *lqt) {
	return lqt->front->elt;
}

void traversal(linked_queue_t *lqt) {
	linknode *cur=lqt->head->next;
	while(cur!=NULL){
		printf(" %d ",cur->elt);
		cur=cur->next;
	}
	printf("\n");
}



