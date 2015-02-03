#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

/************最长公共子序列的动态规划算法实现****************************/

void construct_lcs(int **c,char *str1, char *str2,int i,int j){
	if(i== 0|| j==0)
		return ;
	if(str1[i-1]==str2[j-1]){
		construct_lcs(c,str1,str2,i-1,j-1);
		printf("%c ",str1[i-1]);
	} else if(c[i-1][j]>=c[i][j-1]){
		construct_lcs(c,str1,str2,i-1,j);
	} else
		construct_lcs(c,str1,str2,i,j-1);
}

void construct_lcs_backtrack();

int compute_lcs(char *str1,char *str2){
	int i,j;
	int m=strlen(str1),n=strlen(str2);

	/*c[i][j]记为两序列的LCS长度，初始化c[i][j]*/
	int **c=new int*[m+1];
	for(i=0;i<=m;i++)
		c[i]=new int[n+1];
	for(i=0;i<=m;i++)
		c[i][0]=0;
	for(j=0;j<=n;j++)
		c[0][j]=0;


	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++){
			if(str1[i-1]==str2[j-1]){
				c[i][j]=c[i-1][j-1]+1;
			} else if(c[i-1][j]>= c[i][j-1]){
				c[i][j]=c[i-1][j];
			} else {
				c[i][j]=c[i][j-1];
			}
		}
	int max=c[m][n];
	construct_lcs(c,str1,str2,m,n);
	printf("\n");
	for(i=0;i<=m;i++)
		delete[] c[i];
	delete[] c;
	return max;
}


/***************************测试**************************************/
/**
 * 提供两类测试
 * A. 提供不同规模的数据集和测试用例，以便调试代码，修正bug
 *       测试用例需要考虑：普通功能测试、边界测试(边界条件如结束标志，整数是否溢出、指针是否为空等)、负面测试(可能的错误输入，异常处理)
 * B. 随机生成实验数据进行测试和完善
 * 根据需求需要改进算法和提高效率，这时候应提供测试运行时间和倍率的函数库
 *
 
 */

void test_lcs(char *str1,char *str2,int expected){
	if(str1==NULL || str2==NULL){
		printf("输入子序列有一个为空\n");
		return ;
	}
	int result=compute_lcs(str1,str2);
    if(expected==result){	
		printf("序列1: %s\n",str1);
		printf("序列2: %s\n",str2);
		printf("两序列的最长公共子序列长度: %d\n",result);
		printf("Test passed!\n");
		
    }
	else{
		printf("序列1: %s\n",str1);
		printf("序列2: %s\n",str2);
		printf("两序列的最长公共子序列长度： %d\n",result);
		printf("Test failed!\n ");	
	}

	printf("\n");
}


void test1(){
	char str1[]="A";
	char str2[]="B";
	test_lcs(str1,str2,0);
}

void test2(){
	char str1[]="AB";
	char str2[]="BA";
	test_lcs(str1,str2,1);
}

void test3(){
	char str1[]="BDCA";
	char str2[]="BCDA";
	test_lcs(str1,str2,3);
}

void test4(){
	char str1[]="ABCBDAB";
	char str2[]="BDCABA";
	test_lcs(str1,str2,4);
}

void test_random_trival(){

}


int main(){
	test1();
	test2();
	test3();
	test4();
	return 0;
}
