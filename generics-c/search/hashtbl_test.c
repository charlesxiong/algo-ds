#include "hashtbl.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_ITEMS 30
#define NUM_BUCKETS 17
#define RND_MAX 1000

typedef struct {
	int key;
	int val;
} test_item_t;

int comp_fcn(const void *a,const void *b){
	return ((test_item_t *)a)->key-((test_item_t*)b)->key;
}

int hash_fcn(const void *item, int n){
	/*将键值作为随机的种子*/
	// srand(((test_item_t *)item)->key);
	// rand();
	// return rand()%n;
	int key=((test_item_t *)item)->key;
	return  key% n;
}

void visit(hash_tbl_node_t *cur){
	if(cur){
		test_item_t *item=(test_item_t *)cur->item;
		printf("(%d , %d) ",item->key,item->val);
	}
}


void test(){
	test_item_t arr[NUM_ITEMS],*cur,*item;
	int i;
	for(i=0;i<NUM_ITEMS;i++){
		arr[i].key=i*i;
		arr[i].val=rand()%RND_MAX;
	}

	printf("\n========以NUM_BUCKETS大小将散列表初始化========\n");
	hash_tbl_t *tbl=hashtbl_alloc(NUM_BUCKETS,hash_fcn,comp_fcn);

	printf("\n========散列表的插入测试========\n");
	for(i=0;i<NUM_ITEMS;i++){
		item=&arr[i];
		cur=hashtbl_insert(tbl,item);
		if(cur){
			printf("Duplicate key-val pair: (%d , %d) detected, try again please !\n",cur->key,cur->val);
			i--;
		} else{
			printf("Inserted key-val pair: (%d , %d)\n",item->key,item->val);
		}
	}
	

	printf("\n========散列表的重复插入测试========\n");
	test_item_t test_dup;
	test_dup.key=2*2;
	if(hashtbl_insert(tbl,&test_dup)){
		printf("Duplicate detected\n");
	} else {
		printf("No Duplicate\n");
	}

	printf("\n========散列表的查找测试========\n");
	test_item_t find_dup;
	for(i=0;i<NUM_ITEMS;i++){
		find_dup.key=i;
		if(hashtbl_find(tbl,&find_dup)){
			printf("key %d found \n",i);
		} else{
			printf("key %d not found \n",i);
		}
	}

	printf("\n========插入操作后散列表的遍历========\n");
	hashtbl_foreach(tbl,visit);

	printf("\n========散列表的删除测试========\n");
	test_item_t del_item;
	for(i=0;i<NUM_ITEMS;i++){
		del_item.key=i;
		printf("key %d: ",del_item.key);
		if(hashtbl_delete(tbl,&del_item)){
			printf("delete successfully\n");
		} else{
			printf("not exists\n");
		}
	}
	printf("\n========删除操作后散列表的遍历========\n");
	hashtbl_foreach(tbl,visit);

	printf("\n========释放散列表内存========\n");
	hashtbl_free(tbl);
	printf("\n========释放散列表内存后散列表的遍历========\n");

}

int main(){
	test();
	return 0;
}

