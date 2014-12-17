#include "stack.h"
void test1(){
	stack_t *st=init_default_stack(3);
	push(st,1);
	push(st,2);
	push(st,3);
	push(st,4);
	foreach(st);
	int i;
	for(i=0;i<5;i++)
		push(st,i+10);
	printf("Size: %d %d %d\n",getsize(st),is_empty(st),is_full(st));
	while(!is_empty(st)) {
		printf("%d \n",pop(st));
	}
}

void test2(){
	stack_t *st=init_stack(5);
	push(st,'1');
	push(st,'2');
	push(st,'a');
	push(st,'z');
	foreach(st);
	push(st,'c');
	foreach(st);
	//printf("%c %c %c %c\n",pop(st),pop(st),pop(st),pop(st));
	printf("%c \n",pop(st));


}
int main(){
	test1();
	return 0;
}