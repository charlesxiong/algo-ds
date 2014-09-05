#include "genstack.h"

stack_t *init_stack(int capacity,int sz){
	stack_t *st=init(capacity);
    st->type_sz=sz;
	st->elts=malloc(st->type_sz*capacity);
	assert(st->elts !=NULL);
	return st;
}

stack_t *init_default_stack(int sz){
	return init_stack(DEFAULT_SIZE,sz);
}

int is_full(stack_t *st){
	return (st->top==st->size-1)?1:0;
}

int is_empty(stack_t *st){
	return (st->top==-1)?1:0;
}


void push(stack_t *st,void *elt){
     if(is_full(st)) {
     	/*resizing array*/
     	printf("The origin stack is full,resize the size of stack !\n");
     	int sz=st->size;
     	void *new_elts=malloc(st->type_sz*sz*2);
     	void *src;
     	void *dst;
     	int i;
	    for(i=0;i<sz;i++){
		     src=(char *)(st->elts)+i*st->type_sz;
             dst=(char *)new_elts+i*st->type_sz;
             assign(src,dst,st->type_sz); //*dst=*src;
               
		}
     	free(st->elts);
     	st->elts=new_elts;
     	st->size *=2;
     }
       //st->elts[++st->top]=elt;
		++st->top;
        void *new_elt=(char *)st->elts+st->top*st->type_sz;
	   assign(elt,new_elt,st->type_sz);
}

void* pop(stack_t *st){
	if(is_empty(st)) {
		printf("Empty stack!\n");
		return NULL;
	}
	void *elt=(char *)st->elts+st->top*st->type_sz;
     st->top--;
	return elt;
}

void* stack_peek(stack_t *st){
    void *elt=(char *)st->elts+st->top*st->type_sz;
	return elt;
}

int getsize(stack_t *st){
	return st->top+1;
}

void foreach(stack_t *st){
	 //int i;
	 //for(i=0;i<=st->top;i++)
	 //	printf("%d ",st->elts[i]);
	 //printf("\n");
}



