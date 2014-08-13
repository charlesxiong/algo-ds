#include <stdio.h>
#include "linkedqueue.h"


void test1(){
	linked_queue_t *lqt=init_linked_queue();
	printf("%d \n",is_empty(lqt));
	enqueue(lqt,1);
	printf("%d %d\n",is_empty(lqt),dequeue(lqt));
	enqueue(lqt,2);
	printf("%d %d %d\n",lqt->front->elt,lqt->rear->elt,is_empty(lqt));
	printf("%d\n",dequeue(lqt));
	enqueue(lqt,10);
	enqueue(lqt,23);
	enqueue(lqt,33);
    traversal(lqt);
    while(!is_empty(lqt))
    	printf(" %d ",dequeue(lqt));
    printf("\n");
    enqueue(lqt,22);
    while(!is_empty(lqt))
    	printf(" %d ",dequeue(lqt));
    printf("%d\n",is_empty(lqt));

}


int main(){
	test1();
	return 0;
}