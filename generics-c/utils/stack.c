#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy


/*为栈分配一定容量的内存*/
stack_t *stack_alloc(int capacity,int type_size){
	stack_t *st=malloc(sizeof(stack_t));
	st->data=malloc(capacity*type_size); //分配一定容量大小的数组，该数组大小可动态变化
	st->capacity=capacity;
	st->top=0;
	st->type_size=type_size;
	return st;
}

stack_t *stack_alloc_default(int type_size){
	return stack_alloc(DEFAULT_CAPACITY,type_size);
}

/*释放栈内存*/
void stack_free(stack_t *st){
	free(st->data);
	free(st);
}

int stack_size(stack_t *st){
	return st->top;
}

bool stack_empty(stack_t *st){
	return (st->top==0)?true:false;
}

/****************辅助函数**********************/
/*使用字节流从src复制size个字节到dst位置上*/
void copy(void *dst,void *src,int size){
	char *buf=malloc(size);
	memcpy(buf,src,size);
	memcpy(dst,buf,size);
	free(buf);
}

/*******************************************/

/*入栈: 若栈没有多余的空间，数组容量加倍*/
void stack_push(stack_t *st,void *elt){
	if(st->top==st->capacity){ //栈
		st->capacity=stack_size(st)*2;
		st->data=realloc(st->data,st->capacity*st->type_size);
	}
	void *elt_pos=(char *)st->data+st->top*st->type_size; //取下一个栈顶元素的位置，强制转换为字节表示
	copy(elt_pos,elt,st->type_size);
	st->top++;
}

/*出栈: 出栈后如果数组太大，将长度减半*/
void *stack_pop(stack_t *st){
	if(stack_empty(st)){
		printf("Stack is empty\n");
		return NULL;
	}
	--st->top;
	void *elt_pos=(char *)st->data+st->top*st->type_size;
	return elt_pos;
}

/*读取栈顶元素*/
void *stack_top(stack_t *st){
	void *elt_pos=(char *)st->data+(st->top-1)*st->type_size;
	return elt_pos;
}


