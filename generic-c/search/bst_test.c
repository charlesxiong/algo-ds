#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "../utils/timer.h"

#define MAX_LEN 10
#define MAX_RAND 11

typedef struct item {
	int key;
	int miscs;
} item_t;


int item_cmp(const void *a,const void *b){
	return ((item_t *)a)->key - ((item_t *)b)->key;
}

int main(){
	/*创建一个BST*/
	 bst_t *t=bst_alloc(item_cmp);
	 item_t arr[MAX_LEN];
	 item_t *dup;

	 /*插入表项*/
	printf("插入元素中:\n");
	int j=0;
	srand(time(NULL));
	while(j<MAX_LEN) {
	 	item_t *item=&arr[j];
	 	item->key= rand() % MAX_RAND;
	 	item->miscs= rand() % MAX_RAND;
	 	j++;
	 	if((dup=bst_insert(t,item))){ 
	 		printf(" (检测到重复数: %d- 请重新插入!)\n",dup->key);
	 		j--;
	 	} else {
	 		printf(" %d ", item->key);
	 		if(j%10==0) printf("\n");	 		
	 	}
	}
	printf("\n");

	/*测试是否有重复数*/
	printf("尝试重复插入:\n");
	item_t *cur=&arr[MAX_LEN-1];
	item_t test_dup;
	test_dup.key=cur->key; 
	test_dup.miscs= rand() % MAX_RAND;
	if(bst_insert(t,&test_dup)){
		printf("检测到重复数!\n");
	} else {
		printf("未检测到重复数！\n");
		exit(1);
	}

	/*测试查找功能*/
	printf("\n测试bst_find(): \n");
	item_t lookup_item;
	lookup_item.key=arr[MAX_LEN/2].key;
	item_t *result=bst_find(t,&lookup_item);
	if(result){
		printf("%s\n",result->key==lookup_item.key? "Successful":"Failed");
	} else{
		printf("Failed\n");
	}

	/*测试查找最小值功能*/
	printf("\n测试bst_find_min(): \n");
	result=bst_find_min(t);
	if(result){
		printf("%d Found\n",result->key);
	} else{
		printf("Failed\n");
	}

	/*测试删除功能*/
	printf("\n测试bst_delete(): \n");
	result=bst_delete(t,&lookup_item);
	if(result){
		printf("%s\n",result->key==lookup_item.key? "Successful":"Failed");
	} else{
		printf("Failed\n");
	}

	/*测试删除功能*/
	printf("\n测试bst_delete_min(): \n");
	result=bst_delete_min(t);
	if(result){
		printf("%d Found\n",result->key);
	} else{
		printf("Failed\n");
	}

	/*测试释放功能*/
	printf("\n测试bst_free(): \n");
	bst_free(t);
	printf("Successful\n");


	/*重复性的插入和删除*/
	t=bst_alloc(item_cmp);
	printf("\n重复性地插入和删除测试: \n");
	for(j=0;j<MAX_LEN;j++){
		item_t *item=&arr[j];
		bst_insert(t,item);
	}
	for(j=MAX_LEN/2;j<MAX_LEN;j++){
		item_t *item=&arr[j];
		if(!bst_delete(t,item)){
			printf("Failed\n");
		}
	}

	for(j=MAX_LEN/2;j<MAX_LEN;j++){
		item_t *item=&arr[j];
		bst_insert(t,item);
	}

	for(j=0;j<MAX_LEN/2;j++){
		item_t *item=&arr[j];
		if(!bst_delete(t,item)){
			printf("Failed\n");
		}
	}

	for(j=MAX_LEN/2;j<MAX_LEN;j++){
		item_t *item=&arr[j];
		if(!bst_delete(t,item)){
			printf("Failed\n");
		}
	}
	printf("Successful\n");
	bst_free(t);

	return 0;
}