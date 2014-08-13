#ifndef _ARRAY_H_
#define _ARRAY_H_
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define DEFAULT_SZ 16
typedef int T;
typedef struct {
	 T *data;
	 int size; //the size of data
	 int index; 
} array_t;

array_t *array_create(int capacity);
array_t *array_create_default();
void array_push(array_t *arr, T elt);
int array_isempty(array_t *arr);
void array_clear(array_t *arr);
T array_pop(array_t *arr);
void array_set(array_t *arr,T elt,int pos);
T array_get(array_t *arr,int pos);
void array_for_each(array_t *arr);
void array_sort(array_t *arr);

static inline array_t *
array_init(int capacity){
	array_t *arr=(array_t *)malloc(sizeof(array_t));
	if(NULL==arr) {
		printf("Allocating memory failed...\n");
		return NULL;
	}
	arr->index=0;
	arr->size=capacity;
	return arr;
} 

static inline void 
swap(T *v,int i,int j){
	T tmp=v[i];
	v[i]=v[j];
	v[j]=tmp;
}

static inline int 
numcmp(T *v1,T *v2){
	if(*v1<*v2)
		return -1;
	else if (*v1 > *v2)
		return 1;
	else
		return 0;
	// *v1-*v2
}

static inline void
array_qsort(array_t *arr,int left,int right,int (*comp)(T *,T *)){
	if(left >=right) return;
	int i,last;
	swap(arr->data,left,(left+right)>>1);
	last=left;
	for(i=left+1;i<=right;i++){
		if((*comp)(&arr->data[i],&arr->data[left])<0) //pointer to a function
			swap(arr->data,++last,i);
	}
	swap(arr->data,left,last);
	array_qsort(arr,left,last-1,comp);
	array_qsort(arr,last+1,right,comp);
}




#endif 