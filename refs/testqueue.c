#include <stdio.h>
#include "queue.h"


void test1(){
	queue_t *qt=init_queue();
	int ele;
	while(!is_full(qt)){
		scanf("%d",&ele);
		enqueue(qt,ele);
	}
	printf("The queue is full,size is :%d ,the peek : %d \n",getsize(qt),queue_peek(qt));
	while(!is_empty(qt)){
		printf(" %d ",dequeue(qt));
	}
	printf("\nThe queue is empty,size is :%d \n",getsize(qt));


}
int main(){
	test1();
	return 0;
}
