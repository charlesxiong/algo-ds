#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

#define MAX_LEN 10

int int_cmp(const void *a ,const void *b){ //表项元素就是int值
	return *((int *)a) - *((int *)b);
}

void slist_print(slist_t *l){
	list_node_t *cur;
	printf("遍历链表:\n");
	if(l->head){
		cur=l->head;
		while(cur){
			printf("%d ",*(int *)cur->item);
			cur=cur->next;
		}
	}
	printf("\n");
}



int main(){
	slist_t *l=slist_alloc(int_cmp);
	int arr[MAX_LEN];
	int *res,*val;
	//srand(time(NULL));
	int j=0;
	printf("\n测试从单链表尾部或头部插入:\n");
	while(j<MAX_LEN){
		arr[j]= rand() % 100;
		//printf(" %d ",arr[j]);
		val=&arr[j];
		slist_insert_end(l,val);
		j++;
	}
	slist_print(l);

	printf("\n测试从单链表尾部删除:\n");
	res=slist_delete_end(l);
	if(res)
		printf("%d Deleted \n",*res);
	else
		printf("Failed\n");
	slist_print(l);

	printf("\n测试从单链表头部删除:\n");
	res=slist_delete_begin(l);
	if(res)
		printf("%d Deleted \n",*res);
	else
		printf("Failed\n");
	slist_print(l);

	printf("\n测试从单链表中间删除:\n");
	for(j=MAX_LEN/2;j<MAX_LEN;j++){
		val=&arr[j];
		res=slist_delete_middle(l,val);
		if(res)
			printf("%d Deleted \n",*res);
		else
			printf("Failed\n");
	}
	printf("%d\n",l->n);
	slist_print(l);
	
	
	slist_free(l);
	return 0;
}