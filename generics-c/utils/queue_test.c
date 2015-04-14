#include "queue.h"
#include <stdio.h>

#define MAX_LEN 10

typedef struct item {
	char key;
	int miscs;
} item_t;

int main(){
	/*创建一个默认大小的队列*/
	queue_t *qt=queue_alloc_default(sizeof(item_t));

	item_t arr[MAX_LEN];
	item_t *cur;

	/*队列中插入元素*/
	for(int i=0;i<MAX_LEN;i++){
		cur=&arr[i];
		cur->key='a'+i;
		enqueue(qt,cur);
	}

	/*出队*/
	while(queue_size(qt)>=5){
		cur=dequeue(qt);
		printf("%c\n",cur->key);
	}

	enqueue(qt,&arr[7]);
	enqueue(qt,&arr[8]);
	enqueue(qt,&arr[9]);
	while(queue_empty(qt)==0){
		cur=dequeue(qt);
		printf("%c\n",cur->key);
	}

	queue_free(qt);


	
	return 0;
}