#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * 把字符串中的每个空格替换成“%20” 
 * 思路：借助两个工作指针：一个指向原始字符串的末尾，一个指向空格替换后字符串的末尾
 * 从后向前遍历根据当前字符情形决定是复制还是替换
 */
void replace_blank(char str[],int len){ //len表示字符数组的容量
	if( str==NULL && len<=0)
		return;

	/*计算字符数组的实际长度、统计出现空格的次数和空格替换后的数组的实际长度*/
	int actuallen=0;
	int blanknum=0;
	char *pstr=str;
	while(*pstr!='\0'){ //这里用数组下标访问
		actuallen++;
		if(*pstr==' ')
			blanknum++;
		pstr++;
	} //程序退出时*pstr='\0'
	int replace_newlen=actuallen+blanknum*2;
	if(replace_newlen>len) //要求能够在原来的字符串上做替换，足够长
		return ;

	int p1=actuallen; //原始字符串的末尾
	int p2=replace_newlen; //空格替换后字符串的末尾
	while(p1>=0 && p2 >p1) { //借助两个工作指针
		 if(str[p1]==' '){ //当前字符为空格
		 	str[p2--]='0';
		 	str[p2--]='2';
		 	str[p2--]='%';
		} else { //不为空格，将当前原始字符直接复制到替换后的位置
			str[p2--]=str[p1];
		}
		p1--;
	} //退出条件为：要么遍历字符数组结束，要么两工作指针指向相同字符，表明空格替换已经完成
}


/******************************************************/
void test(char *testname,char str[],int len,char expected[]){
 	if(testname!=NULL){
 		printf("%s: ",testname);
 		replace_blank(str,len);
 		if(str==NULL && expected==NULL)
 			printf("Passed.\n");
 		else if(str!=NULL && expected==NULL)
 			printf("Failed.\n");
 		else if(strcmp(str,expected)==0)
 			printf("Passed.\n");
 		else
 			printf("Failed.\n");
	}
 }

/**
 * 测试用例：
 * 包含空格(字符串的最开始和最后面、字符串的中间、有多个不连续的空格、有多个连续的空格)
 * 不包含空格
 * 特殊输入测试(空指针、空字符串、只有多个连续的空格)
**/

//空格在中间
void test_case1(){
	char str[100]="Hello world.";
	test("Case 1 test",str,100,"Hello%20world.");
}

//空格在最前面
void test_case2(){
	char str[100]=" Helloworld.";
	test("Case 2 test",str,100,"%20Helloworld.");
}

//空格在最后面
void test_case3(){
	char str[100]="Helloworld. ";
	test("Case 3 test",str,100,"Helloworld.%20");
}

//有多个不连续的空格
void test_case4(){
	char str[100]="We are happy.";
	test("Case 4 test",str,100,"We%20are%20happy.");
}

//有多个连续的空格
void test_case5(){
	char str[100]="Hello   world.";
	test("Case 5 test",str,100,"Hello%20%20%20world.");
}

//没有空格
void test_case6(){
	char str[100]="Helloworld.";
	test("Case 6 test",str,100,"Helloworld.");
}

//空指针
void test_case7(){
	test("Case 7 test",NULL,0,NULL);
}

//空字符串
void test_case8(){
	char str[100]="";
	test("Case 8 test",str,100,"");
}

//只有多个连续空格
void test_case9(){
	char str[100]="    ";
	test("Case 9 test",str,100,"%20%20%20%20");
}




void simple_test(){
	char str1[100]="we are happy.";
	replace_blank(str1,100);
	int len=0;
	char *pstr=str1;
	while(*pstr!='\0') {
		len++;
		pstr++;
	}
	int i=0;
	for(;i<len;i++)
		printf("%c",str1[i]);
	printf("\n");
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
	test_case8();
	test_case9();
	return 0;
}