#include "dlinklist.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 10

int int_cmp(const void *a ,const void *b){ //表项元素就是int值
	return *((int *)a) - *((int *)b);
}

void visit(dlist_node_t *cur){
	if(cur){
		printf("%d ",*(int *)cur->item);
	}
}

int main(){
	/*创建一个双链表*/
	dlist_t *l=dlist_alloc(int_cmp);
	printf("%d\n",dlist_size(l));

	/*双向循环链表的插入和查找测试*/
	int arr[MAX_LEN];
	int *val;
	int j=0;
	while(j<MAX_LEN){
		arr[j]=j;
		val=&arr[j];
		dlist_push_back(l,val);
		j++;
	}

	/*查找存在和不存在的元素*/
	dlist_node_t *cur=dlist_find(l,&arr[2]);
	visit(cur);
	printf("\n");
	int b=18;
	cur=dlist_find(l,&b);
	visit(cur);
	printf("\n");

	/*在位置1插入5*/
	dlist_insert(l,&arr[5],1);
	printf("%d\n",dlist_size(l));
	dlist_foreach(l,visit);
	printf("\n");

	/*在位置8插入3*/
	dlist_insert(l,&arr[3],8);
	printf("%d\n",dlist_size(l));
	dlist_foreach(l,visit);
	printf("\n");

	/*在位置5插入8*/
	dlist_insert(l,&arr[8],5);
	printf("%d\n",dlist_size(l));
	dlist_foreach(l,visit);
	printf("\n");

	/*删除元素*/
	val=dlist_pop_front(l);
	printf("%d\n",*val);

	val=dlist_pop_back(l);
	printf("%d\n",*val);
	val=dlist_delete(l,4);
	printf("%d\n",*val);

	printf("%d\n",dlist_size(l));
	dlist_foreach(l,visit);
	printf("\n");





	/*释放双链表内存*/
	dlist_free(l);
	return 0;
}