#include "dynarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*为动态数组分配内存*/
array_t *array_alloc(int capacity,int type_size,int (*comp)(const void *,const void *)){
	array_t *arr=malloc(sizeof(array_t));
	arr->data=malloc(capacity*type_size);
	arr->capacity=capacity;
	arr->index=0;
	arr->type_size=type_size;
	arr->comp=comp;
	return arr;
}

/*为动态数组分配默认容量大小的内存*/
array_t *array_alloc_default(int type_size,int (*comp)(const void *,const void *)){
	return array_alloc(DEFAULT_CAPACITY,type_size,comp);
}

/*释放动态数组的内存*/
void array_free(array_t *arr){
	free(arr->data);
	free(arr);
}

bool array_empty(array_t *arr){
	return (arr->index==0)?true:false;
}

bool array_full(array_t *arr){
	return (arr->index==arr->capacity)?true:false;
}

int array_size(array_t *arr){
	return arr->index;
}

void array_foreach(array_t *arr, void (*visit)(void *elt)){
	for(int i=0;i<arr->index;i++){
		void *elt=(char *)arr->data+i*arr->type_size;
		visit(elt);
	}
	printf("\n");
}



/****************辅助函数**********************/
/*使用字节流从src复制size个字节到dst位置上*/
void copy(void *dst,void *src,int size){
	char *buf=malloc(size);
	memcpy(buf,src,size);
	memcpy(dst,buf,size);
	free(buf);
}

/*使用字节流交换v1和v2的size个字节大小*/
void swap(void *v1,void *v2,int size){
	char *buf=malloc(size);
	memcpy(buf,v1,size);
	memcpy(v1,v2,size);
	memcpy(v2,buf,size);
	free(buf);
}

void exchange(array_t *arr,int i,int j){
	void *v1=(char *)arr->data+i*arr->type_size;
	void *v2=(char *)arr->data+j*arr->type_size;
	swap(v1,v2,arr->type_size);

}

int compare(array_t *arr,int i,int j){
	void *v1=(char *)arr->data+i*arr->type_size;
	void *v2=(char *)arr->data+j*arr->type_size;
	return (arr->comp)(v1,v2);
}


void array_qsort(array_t *arr,int left,int right){
	if(left<right) {
		int last=left,i;
		exchange(arr,left,(left+right)/2); 
		for(i=left+1;i<=right;i++){
			if(compare(arr,i,left)<0){
				exchange(arr,++last,i);
			}
		}
		exchange(arr,left,last);
		array_qsort(arr,left,last-1);
		array_qsort(arr,last+1,right);
	}
}
/*******************************************/


/**
 * 插入一个元素，根据实际空间决定是否扩充或缩减容量
 * 默认范围内，保持不变；超过容量，则扩充
 */
void array_push(array_t *arr,void *elt){
	if(array_full(arr)){
		/*实现复制函数*/
		void *new_data=malloc(arr->type_size*arr->capacity*2);
		void *src;
		void *dst;
		for(int i=0;i< arr->index;i++){
			src=(char *)arr->data + i*arr->type_size;
			dst=(char *)new_data + i*arr->type_size;
			copy(dst,src,arr->type_size);
		}
		free(arr->data);
		arr->data=new_data;
		arr->capacity *=2;

		/*使用realloc函数*/
		// arr->capacity *=2;
		// arr->data=realloc(arr->data,arr->type_size*arr->capacity);

	}
	void *new_elt=(char *)arr->data + arr->index * arr->type_size;
	copy(new_elt,elt,arr->type_size);
	arr->index++;
}


/*把尾部元素拿掉*/
void *array_pop(array_t *arr){
	--arr->index;
	void *elt=(char *)arr->data+arr->index*arr->type_size;
	return elt;
}

/**
 * 成功找到pos位置上的元素，否则返回NULL
 * 注意: 如果查找函数，需要定义元素大小的比较函数int (*comp)(const void *,const void *)
 */
void *array_get(array_t *arr, int pos){
	if(pos<0||pos>=arr->index){
		printf("Invalid position\n");
		return NULL;
	}
	void *elt=(char *)arr->data+pos*arr->type_size;
	return elt;
}

/*把位置pos上的内容设置成item对应的内容*/
void array_set(array_t *arr,void *elt,int pos){
	if(pos<0||pos>=arr->index){
		printf("Invalid position\n");
		return ;
	}
	void *new_elt=(char *)arr->data+pos*arr->type_size;
	copy(new_elt,elt,arr->type_size);
}


/*动态数组排序*/
void array_sort(array_t *arr){
	array_qsort(arr,0,arr->index-1);
}


