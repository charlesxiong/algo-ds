#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void print(int *arr,int left,int right) {
	for(int i = left; i<= right;i++)
		printf("%d ",arr[i]);
	printf("\n");
}

/*基于partition算法取最小的k个数*/
void getleastk(int *arr,int n,int k) {
 	int left = 0;
	int right = n - 1;
    int pos = partition(arr,left,right);
    while(pos != k - 1) {
        if(pos > k - 1) {
            right = pos - 1;
            pos = partition(arr,left,right);
        } else {
            left = pos + 1;
            pos = partition(arr,left,right);
        }
    }
    print(arr,0,k-1);
}

/*三指针记录排序荷兰三色旗问题*/
void sort_color(int *arr,int n) {
	int left = 0;
	int right = n - 1;
        int cur = 0;
        while(cur <= right) {
        if(arr[cur] == 1) {
            cur++;
        } else if(arr[cur] == 0) {
            swap(&arr[left],&arr[cur]);
            left++;
            cur++;
        } else {
            swap(&arr[cur],&arr[right]);
            right--; //cur不变化
        }
    }
}

/*基于最大堆求最小的k个数*/
void getmink(int *arr,int n,int k) {
	int b[k+1];
	for(int i = 1; i <= k;i++) {
        	b[i] = arr[i - 1];		
	}

    build_max_heap(b,k);
    for(int i = k; i < n;i++) {
        if(arr[i] > b[1])
            continue;
        else {
            b[1] = arr[i];
            sink_down(b,1,k);
        }
    }
    heap_sort_int(b,k);
    print(b,1,k);
}

/**
 * 测试插入排序、冒泡排序、选择排序
 */
void test() {
	int n;
	scanf("%d",&n);
	int *arr = malloc(sizeof(int) * n);
	for(int i = 0; i < n ;i++) {
		scanf("%d",&arr[i]);
	}
	//insertion_sort_int(arr,n);
	//selection_sort_int(arr,n);
	bubble_sort_int(arr,n);
	print(arr,0,n - 1);
	free(arr);
}

/**
 * 测试快速排序和归并排序
 */
void test1() {
	int n;
	scanf("%d",&n);
	int *arr = malloc(sizeof(int) * n);
	for(int i = 0; i < n ;i++) {
		scanf("%d",&arr[i]);
	}
	quick_sort_int(arr,0,n-1);
	print(arr,0,n - 1);
	free(arr);
}

/**
 * 测试堆排序
 */
void test2() {
	int n;
	scanf("%d",&n);
	int *arr = malloc(sizeof(int) * (n+1));
	for(int i = 1; i <= n;i++) {
		scanf("%d",&arr[i]);
	}
	heap_sort_int(arr,n);
	print(arr,1,n);
	free(arr);
}

/*求最小的k个数*/
void test3() {
    int n,k;
	scanf("%d %d",&n,&k);
	int *arr = malloc(sizeof(int) * n);
	for(int i = 0; i <= n - 1;i++) {
		scanf("%d",&arr[i]);
	}
	getmink(arr,n,k);
	//getlargestk(arr,n,k);
}


int main() {
	test3();
	return 0;
}