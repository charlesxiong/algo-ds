#include "genstack.h"
typedef struct {
	char *name;
        double mark;
        char *course;       
} student;

void test1(){
	stack_t *st=init_stack(5,sizeof(char));
        char a='a',b='b';
	push(st,&a);
	push(st,&b);
         while(!is_empty(st)) {
		printf("%c \n",*((char *)pop(st)));
	 }
}
int main(){
	stack_t *s1=init_default_stack(sizeof(student));
    student stu1,stu2;
    stu1.name="john"; stu1.mark=86.0; stu1.course="计算机网络";
    stu2.name="amy"; stu2.mark=95.0; stu2.course="算法设计与分析";
    push(s1,&stu1);
    push(s1,&stu2);
        
    stack_t *st=init_default_stack(sizeof(int));
    int a=1,b=2,c=3,d=4;
	push(st,&a);
	push(st,&b);
	push(st,&c);
	push(st,&d);
    printf("%d\n",*((int *)pop(st)));
       
    test1();
	return 0;
}
