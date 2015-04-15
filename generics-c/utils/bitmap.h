#ifndef _BIT_MAP_H_
#define _BIT_MAP_H_
#include <stdbool.h>

#define BITS_LENGTH  32 
#define SHIFT 5
#define MASK 0x1F
// #define BIT_SLOT(b) ((b)>>SHIFT)
// #define BIT_SLOT_INDEX(b) (1<<((b)& MASK))
// #define BITS_SLOTS(size) ((size+BITS_LENGTH-1)/BITS_LENGTH)


/*位示图数据结构定义*/
typedef struct bitmap{
	unsigned int *bits;
	int size; //整数个数大小
} bitmap_t;

/*分配指定size大小的位示图内存*/
bitmap_t *bitmap_alloc(int size);

/*释放位图内存*/
void bitmap_free(bitmap_t *bm);

/*清除位图中的某一位*/
void bitmap_clear(bitmap_t *bm,unsigned i);

/*设置位图中的某一位*/
void bitmap_set(bitmap_t *bm,unsigned i);

/*查询位图中的某一位*/
bool bitmap_query(bitmap_t *bm,unsigned i);

/*从位图的偏移位置ofs开始，查找第一个0 bit位*/
int bitmap_find(bitmap_t *bm,unsigned ofs);


#endif