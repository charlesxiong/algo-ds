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
	/*创建一个单链表*/
	slist_t *l=slist_alloc(int_cmp);
	int arr[MAX_LEN];
	int *res,*val;
	//srand(time(NULL));
	int j=0;

	/*在单链表尾部或头部插入元素*/
	printf("\n测试从单链表尾部或头部插入:\n");
	while(j<MAX_LEN){
		arr[j]= rand() % 100;
		val=&arr[j];
		slist_push_back(l,val);
		j++;
	}
	slist_print(l);

	/*在单链表尾部删除元素*/
	printf("\n测试从单链表尾部删除:\n");
	res=slist_pop_back(l);
	if(res)
		printf("%d Deleted \n",*res);
	else
		printf("Failed\n");
	slist_print(l);

	/*在单链表头部删除元素*/
	printf("\n测试从单链表头部删除:\n");
	res=slist_pop_front(l);
	if(res)
		printf("%d Deleted \n",*res);
	else
		printf("Failed\n");
	slist_print(l);

	/*在单链表某位置插入元素*/
	printf("\n测试从单链表中间删除:\n");
	for(j=MAX_LEN/2;j<MAX_LEN;j++){
		val=&arr[j];
		res=slist_delete(l,val);
		if(res)
			printf("%d Deleted \n",*res);
		else
			printf("Failed\n");
	}
	printf("%d\n",l->n);
	slist_print(l);
	
	/*释放单链表内存*/
	slist_free(l);
	return 0;
}