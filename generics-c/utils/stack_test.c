#include "stack.h"
#include <stdio.h>

#define MAX_LEN 20

typedef struct item {
	int key;
	int miscs;
} item_t;

int item_cmp(const void *a,const void *b){
	return ((item_t *)a)->key - ((item_t *)b)->key;
}

int main(){
	/*创建一个默认大小的栈*/
	stack_t *st=stack_alloc_default(sizeof(item_t));
	item_t arr[MAX_LEN];

	/*往栈中插入元素*/
	for(int i=0;i<MAX_LEN;i++){
		item_t *cur=&arr[i];
		cur->key=i;
		stack_push(st,cur);
	}

	/*从栈里弹出元素*/
	while(stack_size(st)>=5){
		item_t *p=stack_pop(st);
		printf("%d\n",p->key);
	}

	/*先入栈再出栈*/
	stack_push(st,&arr[8]);
	while(stack_size(st)>0){
		item_t *p=stack_pop(st);
		printf("%d\n",p->key);
	}
	
	/*释放栈内存*/
	stack_free(st);

	return 0;
}