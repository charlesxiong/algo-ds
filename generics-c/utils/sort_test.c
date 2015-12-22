#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

#define RND_MAX 15000
#define R 10 /*关键字基数*/

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
	//bubble_sort_int(arr,n);
	binary_insertion_sort_int(arr,n);
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
	//quick_sort_threeway(arr,0,n-1);
	quick_sort_threeway_fast(arr,0,n-1);
	// int *help = malloc(sizeof(int) * (n+1)); //辅助数组
	// merge_sort_int(arr,help,0,n-1);
	// print(arr,0,n - 1);
	// free(help);

	//merge_sort_inplace(arr,0,n-1);
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


void test4() {
	int n;
	while(scanf("%d",&n) && n != 0) {
		int arr[n];
		for(int i = 0; i <= n - 1; i++)
			arr[i] = rand() % RND_MAX;
		optimal_sort_int(arr,0,n-1);
		print(arr,0,n - 1);
	}
}

/*静态链表*/
typedef struct static_list_node_t {
	int key; /*关键字*/
	int link; /*下一个结点*/
} static_list_node_t;

/**
 * 获取十进制整数中的某一位数字
 * 取数组n的第i位的数字
 */
int get_digit(int n,int i) {
	for(int j = 1;j < i;j++)
		n /= 10;
	return n % 10;
}

/**
 * 链式的基数排序
 * 静态链表,a[0]是头指针
 * d表示最大整数的位数
　* n表示排序元素的个数
 *
 *
 * 用静态链表的好处
 * 能指示到下一个结点的情形
 * 对于在属于某个数的桶中，分配时已经保持了原来的先后关系
 * 收集时只需要定位桶的开始指针和结束指针，前面分配已经保持了桶内关系
 * 桶间关系在收集时联系上
 *
 * 基数排序时间复杂度为O(d*(n+R))，辅助存储是O(R),稳定排序
 */
void radix_sort_list(static_list_node_t a[],int n,int d) {

	int front[R]; /*基数i对应的开始key,*/
	int rear[R]; /*基数i对应的结束key*/
	
	/*初始化静态链表*/
	for(int i = 0;i < n;i++)
		a[i].link = i + 1;
	a[n].link = 0; /*最后一个元素指向开始头元素*/

	/*从低位到高位遍历*/
	int i;
	for(i = 0; i < d;i++) {
		/*按位进行分配*/
		/*把数组的key分配到对应的R个桶中*/
		for(int j = 0;j < R;j++)
			front[j] = 0; /*初始化桶*/
		for(int cur = a[0].link; cur != 0;cur = a[cur].link) {
			int k = get_digit(a[cur].key,i + 1); /*拿到对应的基数放在桶中*/
			if(front[k] == 0) {
				front[k] = cur; /*存储的当前结点*/
				rear[k] = cur;
			} else {
				a[rear[k]].link = cur; /*基数为k的rear指针的下一个结点是cur*/
				rear[k] = cur;
			}
		}
		/*收集: 重新排序静态链表*/
		int j = 0;
		while(front[j] == 0) j++; /*跳过开始未分配的桶*/
		a[0].link = front[j];
		/*在第j桶中的元素自动做好连接了,记录下最后一个桶*/
		int last = rear[j];
		for(j = j + 1;j < R;j++) {
			if(front[j] != 0) {
				a[last].link = front[j];
				last = rear[j];
			}
		}
		a[last].link = 0; /*链接回原来的头结点*/
	}
		
}

void static_list_print(static_list_node_t a[]) {
	int i = a[0].link;
	while(i != 0) {
		printf("%d ",a[i].key);
		i = a[i].link;
	}
}


int main() {
	static_list_node_t a[] = {{0,0},{278,0},{109,0},{63,0},{930,0},{589,0},
		{184,0},{505,0},{269,0},{8,0},{83,0}
	};
	radix_sort_list(a,10,3);
	static_list_print(a);
	return 0;
}