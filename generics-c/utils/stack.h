#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>


#define DEFAULT_CAPACITY 16 

/*基于动态数组的栈结构定义*/
typedef struct {
	void *data;
	int capacity; //允许容纳最大容量
	int top; //当前栈顶的下一个位置
	int type_size; //元素类型的字节大小
} stack_t;


/*为栈分配一定容量的内存*/
stack_t *stack_alloc(int capacity,int type_size);
stack_t *stack_alloc_default(int type_size);

int stack_size(stack_t *st);
bool stack_empty(stack_t *st);

/*释放栈内存*/
void stack_free(stack_t *st);

/*入栈: 若栈没有多余的空间，数组容量加倍*/
void stack_push(stack_t *st,void *elt);

/*出栈*/
void *stack_pop(stack_t *st);

/*读取栈顶元素*/
void *stack_top(stack_t *st);

#endif