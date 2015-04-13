#include <stdio.h>

int min(int a,int b){
	return (a<b)? a:b;
}

/**
 * 求旋转数组中的最小数字
 * 注意:　数组中允许出现重复数字、允许不旋转的
 */
int find_min_rotated(int *arr,int low,int high){
	if(arr==NULL|| low<0){
		printf("无效的参数 ");
		return -1;
	}
	int mid;
	while(low<high){
		if(arr[low] < arr[high]) //这两个条件用于简化判断，要求数组至少为3个元素采进行二分查找
			return arr[low];
		if(high-low==1)
			return arr[high];
	
		mid=low+ ((high-low) >> 1);
		if(arr[low] < arr[mid]){
			low=mid+1;
		} else if(arr[mid] < arr[high]){
			high=mid;
		} else {
			return min(find_min_rotated(arr,low,mid),find_min_rotated(arr,mid+1,high));
		}
	}
	return arr[low];
}

void test(const char *testname,int *arr,int low,int high,int expected){
	if(testname!=NULL){
		printf("%s: ",testname);
		int result=find_min_rotated(arr,low,high);
		if(result==expected){
			printf("Passed\n");
		} else{
			printf("Failed\n");
		}
	}
}

/**
 * 测试用例
 *　正常旋转数组：
 * 分无重复数字如3/4/5/1/2、4/5/1/2/3; 有重复数字3/3/1/2/3、３/5/1/2/3 
 * 边界测试条件: 已升序数组、只有一个数字的数组
 * 特殊输入测试: 数组为NULL指针或长度小于等于0
 */

void test_case1(){
	int len=5;
	int arr[]={3,4,5,1,2};
	test("Case 1 test",arr,0,len-1,1);
}

void test_case2(){
	int len=5;
	int arr[]={4,5,1,2,3};
	test("Case 2 test",arr,0,len-1,1);
}

void test_case3(){
	int len=5;
	int arr[]={1,2,3,4,5};
	test("Case 3 test",arr,0,len-1,1);
}

void test_case4(){
	int len=6;
	int arr[]={2,2,2,1,2,2};
	test("Case 4 test",arr,0,len-1,1);
}

void test_case5(){
	int len=6;
	int arr[]={2,1,2,2,2,2};
	test("Case 5 test",arr,0,len-1,1);
}

/*测试特殊输入，可忽略*/
void test_case6(){
	int len=5;
	test("Case 6 test",NULL,0,len-1,-1);
}

int main(){
	test_case1();
	test_case2();
	test_case3();
	test_case4();
	test_case5();
	test_case6();
	return 0;
}