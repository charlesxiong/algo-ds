#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binsearch.h"
#include "../utils/timer.h"

typedef struct item {
	int key;
	int miscs;
} item_t; //由关键字和杂项数据组成



/*比较函数-强制类型转换的效果是改变指针的伸缩，不会改变值*/
int item_cmp(const void *a,const void *b){
	return ((item_t *)a)->key - ((item_t *)b)->key;
}

void random_array(item_t *arr,int len, int MAX_RAND){
	int i=0;
	while(i<len){
		arr[i].key= rand() % MAX_RAND;
		i++;
	}
}

void display_array(item_t *arr,int len){
	int i=0;
	while(i<len){
		printf(" %2d ",arr[i].key);
		i++;
	}
}

/*单次测试*/
double timetest(char *alg,item_t *arr,int len,item_t x){
	item_t *r1;
	
	if(strcmp(alg,"bsearch")) {
		stimer_start();
		r1=bsearch(&x,arr,len,sizeof(item_t),item_cmp);
		if(!r1){
			printf("Can't found!\n");
			exit(1);
		}
		stimer_stop();
	} 
	if(strcmp(alg,"binsearch")) {
		stimer_start();
		r1=binsearch(&x,arr,len,sizeof(item_t),item_cmp);
		if(!r1){
			printf("Can't found!\n");
			exit(1);
		}
		stimer_stop();
	}
	
	return stimer_time_total();
}

/*多次测试*/
double multitests(char *alg,item_t *arr,int len,item_t x,int tests){
	double total=0.0;
	int i;
    for(i=0;i<tests;i++){
      total += timetest(alg,arr,len,x);
    }
   return total;
}

/*测试某数据是否在有序数组里面*/
void bintest(int len){
	item_t x;
	item_t *arr=malloc(sizeof(item_t)*len);

	/*随机生成数据，并进行排序*/
	random_array(arr,len,1000000);
	qsort(arr,len,sizeof(item_t),item_cmp);

	x.key=5677;
	printf("Searching the key %d: ",x.key);

	stimer_start();
	if(binsearch(&x,arr,len,sizeof(item_t),item_cmp)){
		printf("\t Found! \n");
	} else{
		printf("\t Not Found! \n");
	}
	stimer_stop();
	printf("%5.1f\n",stimer_time_total());
	free(arr);
}


void compare_algo(int len,int tests){
	item_t *arr=malloc(sizeof(item_t)*len);

	/*随机生成数据，并进行排序*/
	random_array(arr,len,1000000);
	qsort(arr,len,sizeof(item_t),item_cmp);

	
	double total1=0.0;
	double total2=0.0;
	int i;

	for(i=0;i<len;i++){
		total2 +=multitests("binsearch",arr,len,arr[i],tests);
		total1 +=multitests("bsearch",arr,len,arr[i],tests);
		
	}
	printf("bsearch = %.2f\n",total1/tests);
	printf("binsearch = %.2f\n",total2/tests);

}

int main(){
	//bintest(1000000);
	compare_algo(1000,1000);//测试用例:10个大小为1000的数组
	return 0;
}
