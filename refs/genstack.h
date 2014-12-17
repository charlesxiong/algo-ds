#ifndef _GEN_STACK_H_
#define _GEN_STACK_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define DEFAULT_SIZE 16

typedef struct stack_node {
	int top;
	void *elts;
	int size;
    int type_sz; //the size of the element type 
} stack_t;

stack_t *init_stack(int capacity,int sz);
stack_t *init_default_stack(int sz);
void push(stack_t *st,void *elt);
void* pop(stack_t *st);
void* stack_peek(stack_t *st);
int is_empty(stack_t *st);
int is_full(stack_t *st);
int getsize(stack_t *st);
void foreach(stack_t *st);

static inline 
stack_t *init(int capacity){
	stack_t *node=(stack_t *)malloc(sizeof(stack_t));
	assert(node!=NULL);
	node->top=-1;
	node->size=capacity;
	return node;
}


/* 变量不能声明为void无类型，因为你不知道传进的参数是什么类型的，且不用将*用于无类型指针，因为编译阶段没有此地址指向对象大小的信息
* so 需要在调用的地方传入相关要交换对象的地址空间大小size并利用字节内存操作函数memcpy进行赋值
* 默认要求两值类型必须完全一致，否则容易出现一些问题
*/
static inline void 
assign(void *vp1,void *vp2,int size){
	char *buffer=(char *)malloc(size);
	memcpy(buffer,vp1,size);
	memcpy(vp2,buffer,size);
	free(buffer);
} 
/* 基于内存操作函数memcpy/memcmp函数实现支持多种数据类型即可进行两元素内容交换的泛型方法
*/
static inline void 
exchange(void *vp1,void *vp2,int size){
	char *buffer=(char *)malloc(size);
	memcpy(buffer,vp1,size);
	memcpy(vp1,vp2,size);
	memcpy(vp2,buffer,size);
	free(buffer);
}


#endif 
