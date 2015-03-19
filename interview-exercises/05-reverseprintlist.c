#include <stdio.h>
#include "./utils/linklist.h"

#define MAX_LEN 100
#define MAX_RAND 100000

int int_cmp(const void *a ,const void *b){ //表项元素就是int值
	return *((int *)a) - *((int *)b);
}

void printlist(slist_t *l){
	list_node_t *cur;
	printf("正向输出链表:\n");
	if(l->head){
		cur=l->head;
		while(cur){
			printf("%d ",*(int *)cur->item);
			cur=cur->next;
		}
	}
	printf("\n");
}

/**
 * 基于栈实现反向遍历：
 * 每遍历一个结点，压入栈中；
 * 遍历完整个链表后，从栈顶开始逐个输出结点值，则输出顺序为逆序
 * 
 * 用栈基于循环实现的代码鲁棒性更好
 */
void reverseprintlist_iterative(slist_t *l){
	if(l->head){
		/*快速的简单栈实现*/
		list_node_t **stack=malloc((l->n) * sizeof(list_node_t *));
		list_node_t *cur=l->head;
		int top=0;
		while(cur){ //入栈
			stack[top++]=cur;
			cur=cur->next;
		}

		printf("以栈迭代方式反向输出链表:\n");
		while(top>0){ //top退出是top=0，返回待插入的下一个元素，注意条件不能是top=0;
			cur=stack[--top]; //出栈
			printf("%d ",*(int *)(cur->item));
		}
		free(stack);
		printf("\n");
	}

}

/**
 * 基于递归实现反向输出：
 * 每访问一个结点的时候，先递归输出它后面的结点，再输出该结点本身
 *
 * 问题：链表很长时,导致调用的层级很深，容易栈溢出，推荐用栈实现
 */
void print_recusive(list_node_t *p){
	if(p){
		print_recusive(p->next);
		printf("%d ",*(int *)(p->item));
	} else{
		return ;
	}
}

void reverseprintlist_recursive(slist_t *l){
	if(l->head){
		printf("以递归方式反向输出链表:\n");
		print_recusive(l->head);
		printf("\n");
	}
}


/******************************************************/
void test(char *testname,slist_t *l){
	if(testname){
		printf("%s: \n",testname);
		printlist(l);
		reverseprintlist_iterative(l);
		reverseprintlist_recursive(l);
		printf("\n");
	}
}

/**
 * 测试用例:
 * 功能测试： 链表含有多个结点、链表只有一个结点
 * 特殊输入测试: 链表为空
 */

/*多个结点*/
void test_case1() {
	slist_t *l=slist_alloc(int_cmp);
	int arr[MAX_LEN];
	int *val;
	for(int j=0;j<MAX_LEN;j++){
		arr[j]=rand() % MAX_RAND;
		val=&arr[j];
		slist_insert_end(l,val);
	}
	test("Case 1 test",l);
	slist_free(l);
}

/*1个结点*/
void test_case2() {
	slist_t *l=slist_alloc(int_cmp);
	int val=2;
	slist_insert_end(l,&val);
	test("Case 2 test",l);
	slist_free(l);
}

/*空链表*/
void test_case3() {
	slist_t *l=slist_alloc(int_cmp); 
	test("Case 3 test",l);
	slist_free(l);

}


void simple_test(){
	slist_t *l=slist_alloc(int_cmp);
	int arr[MAX_LEN]={1,2,8,7,6};
	int *val;
	for(int j=0;j<MAX_LEN;j++){
		val=&arr[j];
		slist_insert_end(l,val);
	}
	printlist(l);
	reverseprintlist_recursive(l);
	reverseprintlist_iterative(l);

	slist_free(l);
}


int main(){
	//simple_test();
	test_case1();
	test_case2();
	test_case3();
	return 0;
}