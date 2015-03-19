#ifndef _DYNARR_H_
#define _DYNARR_H_

/**
 * 动态数组的结构定义
 * item:  指向一块连续内存的指针；type_size: 元素类型的大小
 * capacity: 动态数组的容量大小，最大可用空间
 * index: 动态数组的实际大小
 */
typedef struct {
	void *item; 
	int capacity;
	int index;
	int type_size;
} array_t;

/*分配动态数组的内存*/
array_t *array_alloc(int capacity,int type_size);

array_t *array_free()

#endif