#ifndef _stack_H_
#define _stack_H_
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define DEFAULT_SIZE 16

/** maintain a fix-sized stack 
* #define MAXTOKENS 100
* #define MAXTOKENLEN 64
* enum tokentype {IDENTIFIER,QUALIFILE,TYPE} ;
* int top=-1;
* typedef struct {
*	char type;
*	char string[MAXTOKENLEN]; //one mark's length
* } token;
* token stack[MAXTOKENS]; //the size of all marks
* #define _pop stack[top--]
* #define _push(s) stack[(++top)]=s
*/

typedef int T;
typedef struct stack_node {
	int top;
	T *elts;
	int size;
} stack_t;

stack_t *init_stack(int capacity);
stack_t *init_default_stack();
void push(stack_t *st,T elt);
T pop(stack_t *st);
T stack_peek(stack_t *st);
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



#endif 