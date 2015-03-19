#ifndef _STACK_H_
#define _STACK_H_

/*基于动态数组的栈结构定义*/
typedef struct {
	void *item;
	int capacity;
	int top;
	int type_size;
} stack_t;

/*为栈分配一定容量的内存*/
stack_t *stack_alloc(int capacity,int type_size);
stack_t *stack_alloc_default(int type_size);

/*释放栈内存*/
void stack_free(stack_t *st);

/*入栈: 若栈没有多余的空间，数组容量加倍*/
void stack_push(stack_t *st,void *item);

/*出栈: 出栈后如果数组太大，将长度减半*/
void *stack_pop(stack_t *st);

/*读取栈顶元素*/
void *stack_top(stack_t *st);

#endif