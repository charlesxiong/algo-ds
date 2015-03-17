#include <stdio.h>

/**
 * 二维数组中，每行从左向右递增排序，每列从上到下递增排序
 * 给定一个二维数组和一个整数，判断整数是否在数组中
 * 思路：以具体的二维数组右上角开始分析，进行二分查找的筛选
 */
bool find(int *arr,int row,int column,int number){
	bool found=false;
	if(arr != NULL && row > 0 && column >0){
		int i=0;
		int j=column-1;
		while(i < row && j >=0){ 
			int cur=arr[i*column+j]; //选取二维数组右上角的数字
			if(cur==number){ //相等，查找成功
				found=true;
				break;
			} else if(cur<number) 
				i++; //选取数字小于查找数字，剔除选取数字的当前行
			else
				j--; //选取数字大于查找数字，剔除选取数字的当前列
		}
	}
	return found; 
}

/******************************************************/
 void test(char *testname,int *arr,int row,int column,int number,bool expected){
 	if(testname!=NULL){
 		printf("%s : ",testname);

 		bool result=find(arr,row,column,number);
 		if(result==expected)
 			printf("Passed.\n");
 		else
 			printf("Failed.\n");
 	}
 }

 /**
  * 测试用例：
  * 包含查找的数字(边界值-最大和最小数字、正常数字)
  * 没有查找的数字(边界条件-大于最大和小于最小、属于最小和最大范围内而不在数组中)
  * 特殊输入：二维数组为空-鲁棒性测试，输入空指针
 **/

void test_case1(){
	int arr[][4]={{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
	test("Case 1 test",(int *)arr,4,4,7,true);
}

void test_case2(){
	int arr[][4]={{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
	test("Case 2 test",(int *)arr,4,4,1,true);
}

void test_case3(){
	int arr[][4]={{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
	test("Case 3 test",(int *)arr,4,4,15,true);
}

void test_case4(){
	int arr[][4]={{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
	test("Case 4 test",(int *)arr,4,4,5,false);
}

void test_case5(){
	int arr[][4]={{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
	test("Case 5 test",(int *)arr,4,4,-1,false);
}

void test_case6(){
	int arr[][4]={{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
	test("Case 6 test",(int *)arr,4,4,16,false);
}

void test_case7(){
	test("Case 7 test",NULL,0,0,7,false);
}




void simple_test(){
	int arr[]={1,2,8,9,2,4,9,12,4,7,10,13,6,8,11,15};
	printf("%d \n",find(arr,4,4,7));
	printf("%d \n",find(arr,4,4,1));
	printf("%d \n",find(arr,4,4,15));
	printf("%d \n",find(arr,4,4,0));
	printf("%d \n",find(arr,4,4,5));
	printf("%d \n",find(arr,4,4,16));
}

int main(){
	//simple_test();
	test_case1();
	test_case2();
	test_case3();
	test_case4();
	test_case5();
	test_case6();
	test_case7();
	return 0;
}
