#ifndef _BIN_SEARCH_H_
#define _BIN_SEARCH_H_
#include <stdlib.h>

/**
 *  提供和ANSI C标准库<stdlib.h>中的bsearch()一样的函数接口，参数说明
 *　　它使用了二分查找法在有序数组元素(buf[0]到buf[num-1])查找关键字key
 * 　参数1: 要查找的关键字key, 参数2: 有序数组的基地址buf 
 *  参数3: 指定数组中元素的数目，参数４:  每个元素的长度，size个字节长
 *　　参数5: 一个实现大小比较的函数指针，它将返回正值、0、负值当函数中的第一个参数大于，等于，小于第二个参数
 */
 
void *binsearch(const void *key,const void *buf, size_t num,size_t size,
					int (*comp)(const void *,const void *));


#endif
