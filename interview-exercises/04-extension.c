#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

bool isSorted(int arr[],int len){
	int j;
	bool flag=true; //默认有序
	for(j=1;j<len;j++){
		if(arr[j-1]>arr[j]){
			flag=false;
			break;
		}
	}
	return flag;
}

void merge_twoarray(int a[],int len1,int b[],int len2){
	int p1=len1-1;
	int p2=len2-1;
	int p3=len1+len2-1;
    assert(isSorted(a,len1)==true);
    assert(isSorted(b,len2)==true);

    /**
     * 提供两个工作指针,分别指向两数组的尾部；另外使用一个指针，指向合并后数组的尾位置
     *　从后向前遍历
     */
	while(p1 >=0 && p2 >=0){ 
		if(a[p1]>=b[p2]){
			a[p3]=a[p1];
			p1--;
		} else {
			a[p3]=b[p2];
			p2--;
		}
		p3--;
	}
	while(p1>=0)  a[p3--]=a[p1--]; //数组2已经遍历完，而数组1还未复制完
	while(p2>=0)  a[p3--]=b[p2--]; //数组2已经遍历完，而数组1还未复制完
	assert(isSorted(a,len1+len2));
}




/**
 * 测试用例：
 * 正常: 两数组元素大小交替、A1整体大于A2、A2整体大于A1
 * 特殊输入测试(两数组至少有一个未排序、或者有一个为空数组)
**/

void simple_test(){
	int a[20];
	a[0]=4;
	a[1]=5;
	a[2]=8;
	a[3]=9;
	a[4]=13;
	int b[5]={1,2,6,7,12};

	// a[0]=1;
	// a[1]=2;
	// a[2]=3;
	// a[3]=4;
	// a[4]=5;
	// int b[5]={6,7,8,9,10};

	//int b[5]={1,2,6,7,12};

	merge_twoarray(a,5,b,5);
	int i;
	for(i=0;i<10;i++)
		printf(" %d ",a[i]);
	printf("\n");
}

int main(){
	simple_test();
	return 0;
}