#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"

#define MAXSIZE 16
#define RND_MAX 10000

typedef struct {
	int key;
	int val;
} test_item_t;

void visit(skiplist_node_t *cur){
	if(cur)
		printf("%d ",((test_item_t *)(cur->item))->key);
		//printf(" (key-%d val-%d) ",((test_item_t *)(cur->item))->key,((test_item_t *)(cur->item))->val);
}

int item_cmp(const void *a,const void *b){
	return ((test_item_t *)a)->key-((test_item_t*)b)->key;
}

void test(){
	/*创建一个跳表*/
	//srand(time(NULL));
	skiplist_t *sl=skiplist_alloc(MAXSIZE,0.5,item_cmp);

	
	printf("\n========跳表的插入测试========\n");
	test_item_t arr[MAXSIZE],*cur,*dup,*res;
	int i;
	for(i=MAXSIZE-1;i>=0;i--){
		cur=&arr[i];
		cur->key=i;
		cur->val=rand()%RND_MAX;
		if((dup=skiplist_insert(sl,cur))){
			printf("Duplicate %d detected -trying again\n",dup->key);
			i++;
		} else {
			printf("Inserted key : %d \n",cur->key);
		}
	}
	skiplist_foreach(sl,visit);

	printf("\n========跳表元素的重复插入========\n");
	cur=&arr[MAXSIZE/2];
	test_item_t tdup;
	tdup.key=cur->key;
	tdup.val=rand()%RND_MAX;
	if(skiplist_insert(sl,&tdup)){
		printf("Duplicate detected\n");
	} else{
		printf("No Duplicate\n");
	}

	printf("\n========跳表的查找测试========\n");
	if(skiplist_find(sl,&tdup)){
		printf("Found\n");
	} else{
		printf("Not Found\n");
	}

	printf("\n========跳表的最小键值查找测试========\n");
	if((res=skiplist_find_min(sl))){
		printf("%d\n",res->key);
	} else
		printf("Failed\n");


	printf("\n========跳表的删除测试1========\n");
	for(i=MAXSIZE/2;i<MAXSIZE;i++){
		cur=&arr[i];
		printf("Deleting key %d:\n",cur->key);
		if(!skiplist_delete(sl,cur))
			printf("failed.\n");
	}
	skiplist_foreach(sl,visit);

	printf("\n========跳表的删除测试2========\n");
	for(i=4;i<MAXSIZE/2;i++){
		cur=&arr[i];
		printf("Deleting key %d:\n",cur->key);
		if(!skiplist_delete(sl,cur))
			printf("failed.\n");
	}
	skiplist_foreach(sl,visit);

	printf("\n========跳表的最小键值删除测试========\n");
	if((res=skiplist_delete_min(sl))){
		printf("%d\n",res->key);
	} else
		printf("Failed\n");
	skiplist_foreach(sl,visit);

	/*释放跳表内存*/
	skiplist_free(sl);
}
int main(int argc,char *argv[]){
	test();
}