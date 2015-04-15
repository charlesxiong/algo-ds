#include "dynarr.h"
#include <stdio.h>
#include <math.h>
#include <string.h> //strcmp

#define MAX_LEN 20
#define EPSILON 0.000005

typedef struct item {
	int key;
	int miscs;
} item_t;

int item_cmp(const void *a,const void *b){
	return ((item_t *)a)->key - ((item_t *)b)->key;
}

void visit(void *a){
	printf("%d ",((item_t *)a)->key);
}

int doublecomp(void *v1,void *v2){ 
	double *p1=v1;
	double *p2=v2;
	double dif=*p1-*p2;
	if(fabs(dif)<EPSILON)
		return 0;
	else if(dif >0.0)
		return 1;
	else
		return -1;
}

int strcomp(void *v1,void *v2){  
	char *p1=*(char **)v1;
	char *p2=*(char **)v2;
	return strcmp(p1,p2);
}


int main(){
	/*创建一个一定大小的动态数组*/
	array_t *arr=array_alloc_default(sizeof(item_t),item_cmp);
	item_t it[MAX_LEN],*cur;
	printf("dynamic array size: %d\n",array_size(arr));
	printf("dynamic array capacity: %d\n",arr->capacity);

	/*往数组中添加元素*/
	for(int i=0;i<MAX_LEN;i++){
		cur=&it[i];
		cur->key=i;
		array_push(arr,cur);
	}
	printf("dynamic array size: %d\n",array_size(arr));
	printf("dynamic array capacity: %d\n",arr->capacity);
	array_foreach(arr,visit);

	/*数组中弹出元素*/
	while(array_size(arr)>10){ //数组剩下10个元素才退出
		cur=array_pop(arr);
		visit(cur);
	}
	printf("\ndynamic array size: %d\n",array_size(arr));
	printf("dynamic array capacity: %d\n",arr->capacity);
	array_foreach(arr,visit);

	/*设置数组值和获取数组值*/
	cur=array_get(arr,array_size(arr)-1);
	visit(cur);
	printf("\n");

	cur=&it[15];
	array_set(arr,cur,5);
	cur=&it[13];
	array_set(arr,cur,2);
	array_foreach(arr,visit);

	/*快速排序动态数组的元素*/
	array_sort(arr);
	array_foreach(arr,visit);

	/*释放动态数组内存*/
	array_free(arr);
	return 0;

}