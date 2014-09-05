#include "genarraylist.h"

void test1(){
	array_t *t=array_create(2,sizeof(int));
    int a=1,b=2,c=3;
    array_push(t,&a); 
    array_push(t,&b);
    array_push(t,&c);
	int i=0;
	for(;i<t->index;i++){
		printf("%d \n",*((int *)array_get(t,i)));
	}
    array_qsort(t,0,t->index-1,intcomp);
	i=0;
	for(;i<t->index;i++){
		printf("%d \n",*((int *)array_get(t,i)));
	}
	array_pop(t);
	int d=7887;
	array_push(t,&d);
	i=0;
	for(;i<t->index;i++){
		printf("%d \n",*((int *)array_get(t,i)));
	}
	printf("\n");
	array_qsort(t,0,t->index-1,intcomp);
	i=0;
	for(;i<t->index;i++){
		printf("%d \n",*((int *)array_get(t,i)));
	}
}

void test2(){
	student s[]={
		{"张三",92.5},
		{"李四",80.8},
		{"你",92.5},
		{"我",100},
		{"他",72.8},
		{"她",60}
	};
	array_t *t=array_create_default(sizeof(student));
	int i=0;
	for(;i<sizeof(s)/sizeof(s[0]);i++){
			array_push(t,&s[i]);
	}
	i=0;
	for(;i<t->index;i++){
		printf("%.1f \n",((student *)array_get(t,i))->score);
	}
	printf("\nqsort result : \n");
	array_qsort(t,0,t->index-1,structcomp);
	i=0;
	for(;i<t->index;i++){
		printf("%.1f \n",((student *)array_get(t,i))->score);
	}
	printf("\n");

}
int main(){
	test2();
	// array_t *stut=array_create_default(sizeof(student));
	// array_t *dt=array_create_default(sizeof(double));
	// array_t *ct=array_create_default(sizeof(char));
	// array_t *strt=array_create_default(sizeof(char *)); //dynamic string array

	return 0;
}
