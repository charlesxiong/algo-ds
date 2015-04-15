#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*分配指定size大小的位示图内存*/
bitmap_t *bitmap_alloc(int size){
	bitmap_t *bm=malloc(sizeof(bitmap_t));
	bm->bits=malloc(sizeof(bm->bits[0])*(size+BITS_LENGTH-1)/BITS_LENGTH); //计算合适的slot个数
	bm->size=size;
	memset(bm->bits,0,sizeof(bm->bits[0])*(size+BITS_LENGTH-1)/BITS_LENGTH);
	return bm;
}

/*释放位图内存*/
void bitmap_free(bitmap_t *bm){
	free(bm->bits);
	free(bm);
}

/**
 * 一个unsigned int数能表示32个整数,整数从0开始,针对整数i:
 * i对应的无符号数组下标索引slot: i/32
 * i对应的索引内容里面的比特位数: i%32(1<<(i&MASK)
 * 
 * 清除位图某位: bm->bits[i/32] &= ~(1<<(i%32))
 * 设置位图某位: bm->bits[i/32] |= (1<<(i%32))
 * 测试位图某位: bm->bits[i/32] & (1<<(i%32))
 * 这里采用位掩码运算的方法完成这些操作，避免取模和除数运算，效率更高
 */

/**/
void bitmap_clear(bitmap_t *bm,unsigned i){
	if(i>=bm->size){
		printf("Invalid integer\n");
		return ;
	}
	bm->bits[i>>SHIFT] &= ~(1<<(i & MASK));
}

/*设置位图中的某一位*/
void bitmap_set(bitmap_t *bm,unsigned i){
	if(i>=bm->size){
		printf("Invalid integer\n");
		return ;
	}
	bm->bits[i>>SHIFT] |= (1<<(i & MASK));
}

/*查询位图中的某一位,该位为1，返回true;否则返回false*/
bool bitmap_query(bitmap_t *bm,unsigned i){
	if(i>= bm->size)
		return false;
	if( (bm->bits[i>>SHIFT]) & (1<<(i & MASK)))
		return true;
	return false;
}

/**
 * 从位图的偏移位置ofs开始，查找第一个0bit位
 * 可用此法判断不在数组存储的整数
 * ? 实现仍有问题！！！
 */
int bitmap_find(bitmap_t *bm,unsigned ofs){ 
	if(ofs > bm->size) ofs=0;
	int i,j;
	i=ofs;
	while(i < bm->size){
		if(~(bm->bits[i>>SHIFT])){ //只要该索引下至少有一位为0，就能保证取非是真
			j=i;
			do{
				if(!bitmap_query(bm,j)) return j; //对应位为0，返回当前位置
				j++;
			} while((j&0x1F) && (j< bm->size)) ;
		}
		i +=32; //进行下一轮判断
		i &=~31;
	}
	return -1;
}