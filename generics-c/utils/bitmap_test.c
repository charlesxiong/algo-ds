#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
#define RAD_NUM 100

int main(){
	/*接受大小为MAX的参数，创建一个位图*/
	bitmap_t *bm=bitmap_alloc(MAX);

	unsigned int i;
	unsigned int arr[RAD_NUM];
	for(i=0;i<RAD_NUM;i++){
		arr[i]=RAD_NUM-i;
	}
	/**
	 * 设置某些数在位图的位表示为1
	 * 生成RAD_NUM个不相同的随机数据
	 * 插入位图中，对应位则设置为1
	 */
	printf("原始无序的数据:\n");
	for(i=0;i<RAD_NUM;i++){
		unsigned int j=i+rand()%(RAD_NUM-i);
		int temp=arr[i];
		arr[i]=arr[j];
		arr[j]=temp;
		printf("%d ",arr[i]);
		if(i%10==0&&i!=0) printf("\n");
		bitmap_set(bm,arr[i]);
	}
	printf("\n");
	
	printf("使用位图排序后的数据:\n");

	/*查询该数是否在数组中，很容易保证有序输出*/
	for(i=0;i<MAX;i++){
		if(bitmap_query(bm,i)){
			printf("%d ",i);
			if(i%10==0&&i!=0) printf("\n");
		}
	}
	printf("\n");

	/*释放位图的内存*/
	bitmap_free(bm);
	return 0;
}