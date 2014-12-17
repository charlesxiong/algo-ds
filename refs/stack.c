#include "stack.h"

stack_t *init_stack(int capacity){
	stack_t *st=init(capacity);
	st->elts=(T *)malloc(sizeof(T)*capacity);
	assert(st->elts !=NULL);
	return st;
}

stack_t *init_default_stack(){
	return init_stack(DEFAULT_SIZE);
}

int is_full(stack_t *st){
	return (st->top==st->size-1)?1:0;
}

int is_empty(stack_t *st){
	return (st->top==-1)?1:0;
}

void push(stack_t *st,T elt){
     if(is_full(st)) {
     	/*resizing array*/
     	printf("The origin stack is full,resize the size of stack !\n");
     	int sz=st->size;
     	T *new_elts=(T *)malloc(sizeof(T)*sz*2);
     	T *src=st->elts;
     	T *dst=new_elts;
     	while(sz--){
     		*dst++=*src++;
     	}
     	free(st->elts);
     	st->elts=new_elts;
     	st->size *=2;
     }
     st->elts[++st->top]=elt;
}

T pop(stack_t *st){
	if(is_empty(st)) {
		printf("Empty stack!\n");
		return -1;
	}
	return st->elts[st->top--];
}

T stack_peek(stack_t *st){
	return st->elts[st->top];
}

int getsize(stack_t *st){
	return st->top+1;
}

void foreach(stack_t *st){
	int i;
	for(i=0;i<=st->top;i++)
		printf("%d ",st->elts[i]);
	printf("\n");
}



