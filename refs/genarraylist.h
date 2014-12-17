#ifndef _GEN_ARRAY_H_
#define _GEN_ARRAY_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //memcpy,strcmp
#include <math.h> //fabs
#define DEFAULT_SZ 16
#define EPSILON 0.000005
typedef struct {
	 void *data;
	 int size; //the size of data
	 int index; 
	 int type_sz; //the real size of the data type
} array_t;

typedef struct {
	char name[15];
	double score;
} student;

array_t *array_create(int capacity,int sz);
array_t *array_create_default(int sz);
void array_push(array_t *arr, void *elt);
int array_isempty(array_t *arr);
void array_clear(array_t *arr);
void *array_pop(array_t *arr);
void array_set(array_t *arr,void *elt,int pos);
void *array_get(array_t *arr,int pos);



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
swap(void *v1,void *v2,int size){ 
//generics swap the two values using byte flow , size : the real size of memory block v1&v2's type 
	char *buffer=(char *)malloc(size);
	memcpy(buffer,v1,size);
	memcpy(v1,v2,size);
	memcpy(v2,buffer,size);
	free(buffer); //must free or it will malloc twice
}

static inline void 
exchange(void *v,int i,int j,int size){
	void *v1=(char *)v+i*size;
	void *v2=(char *)v+j*size;
	swap(v1,v2,size);
}

static inline int 
intcomp(void *v1,void *v2){ //compare two ints 
	int *p1=v1;
	int *p2=v2;
	return *p1-*p2;
}

static inline int 
doublecomp(void *v1,void *v2){ //compare two doubles
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

static inline int
strcomp(void *v1,void *v2){ //compare two string 
	char *p1=*(char **)v1;
	char *p2=*(char **)v2;
	return strcmp(p1,p2);
}

static inline int 
charcomp(void *v1,void *v2){ //compare two chars
	char *p1=v1;
	char *p2=v2;
	return *p1-*p2;
}

static inline int 
structcomp(void *v1,void *v2){ 
	student *p1=v1;
	student *p2=v2;
	return doublecomp(&p1->score,&p2->score);
    
}

static inline void 
assign(void *vp1,void *vp2,int size){
	char *buffer=(char *)malloc(size);
	memcpy(buffer,vp1,size);
	memcpy(vp2,buffer,size);
	free(buffer);
} 


/* C library function : void qsort(void *base,int nsize,int type_size,int (*comp)(const void *,const void *))
* it provides all types's qsort's algorithm
*/
static inline void
array_qsort(array_t *arr,int left,int right,int (*comp)(void *,void *)){
	if(left >=right) return;
	int i,last;
	exchange(arr->data,left,(left+right)>>1,arr->type_sz);
	last=left;
	for(i=left+1;i<=right;i++){
		void *v1=(char *)arr->data+i*arr->type_sz;
		void *v2=(char *)arr->data+left*arr->type_sz;
		if((*comp)(v1,v2)<0) 
			exchange(arr->data,++last,i,arr->type_sz);
	}
	
	exchange(arr->data,left,last,arr->type_sz);
	array_qsort(arr,left,last-1,comp);
	array_qsort(arr,last+1,right,comp);
}



#endif 
