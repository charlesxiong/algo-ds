#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timer.h"

int comp(const void *a,const void *b){
	return *(int *)a- *(int *)b;
}

double timetest(char *alg,int n){
   srand(time(NULL));
   int *arr=malloc(sizeof(int)*n);
   int i;
   stimer_start();
   for(i=0;i<n;i++)
         arr[i]=rand()%10000;
   if(strcmp(alg,"qsort")==0) qsort(arr,n,sizeof(int),comp);
   stimer_stop();
   free(arr);
   return stimer_time_total();
}

/**
 * 重复测试: 运行大量的测试数，减小系统本身的误差
 * 测试次数越多，每次测试所需的平均时间就越接近于真实的平均数据
 */
double multitests(char *alg,int n,int tests){
   double total=0.0;
   int i;
   for(i=0;i<tests;i++){
      total +=timetest(alg,n);
   }
   return total/tests;
}

/**
 * 倍率测试: 估计运行时间的增长数量级的方法，用于发现性能问题
 * T(N) = a* N^b *lg N -> T(2N)/T(N) = 2^b
 * 一般地，数学模型中的对数项是不能忽略的，但在倍率假设中预测性能的公式并不那么重要
 * 可选单次测试数或者大量重复测试数
 */
void doubling_ratio(char *alg){
   double prev=multitests(alg,125,20);
   int N=250;
   while(N <= 200000){
      double cur=multitests(alg,N,20); //大量的重复测试数
      printf("%8d %8.1f",N,cur);
      printf("%5.1f\n",cur/prev);
      prev=cur;
      N <<=1;
   }
}

int main(){
   doubling_ratio("qsort");
   return 0;
}
