#ifndef _DYNARR_H_
#define _DYNARR_H_

#include <stdbool.h>

#define DEFAULT_CAPACITY 16

/**
 * 动态数组的结构定义
 * data:  指向一块连续内存的指针；type_size: 元素类型的大小(动态执行时才能确定类型)
 * capacity: 动态数组的容量大小，最大可用空间
 * index: 动态数组的实际大小
 * int (*comp)(const void *,const void *): 元素的大小比较函数
 */
typedef struct {
	void *data; 
	int capacity;
	int index;
	int type_size;
	int (*comp)(const void *,const void *);
} array_t;

/*为动态数组分配内存*/
array_t *array_alloc(int capacity,int type_size,int (*comp)(const void *,const void *));

/*为动态数组分配默认容量大小的内存*/
array_t *array_alloc_default(int type_size,int (*comp)(const void *,const void *));

/*释放动态数组的内存*/
void array_free(array_t *arr);


bool array_empty(array_t *arr);

bool array_full(array_t *arr);

int array_size(array_t *arr);

void array_foreach(array_t *arr, void (*visit)(void *elt));

/**
 * 插入一个元素，根据实际空间决定是否扩充或缩减容量
 * 默认范围内，保持不变；超过默认容量，则扩充
 */
void array_push(array_t *arr,void *elt);

/*把尾部元素拿掉*/
void *array_pop(array_t *arr);

/*成功找到pos位置上的元素，否则返回NULL*/
void *array_get(array_t *arr, int pos);

/*把位置pos上的内容设置成item对应的内容*/
void array_set(array_t *arr,void *item,int pos);

/*动态数组排序*/
void array_sort(array_t *arr);

#endif