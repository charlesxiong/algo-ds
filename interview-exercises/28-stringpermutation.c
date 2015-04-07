#include <stdio.h>
#include <string.h>

/**
 * 全排列非递归解法－字典序法
 * 依照字符集中的字典序关系，从最小字符排列开始，通过循环不断计算当前字符串排列的下一个排列直至达到没有下一个排列
 * 即可得到全排列,求当前排列的下一个排列思路next_premutaion(STL中已有实现):
 *
 * 首先从尾端往前寻找两个相邻元素，记为a、b,找到这样一组相邻元素后
 * 再从尾端开始往前检验，找到第一个比元素a大的元素c, 将元素a、c对调
 * 再将b之后(包括b)的元素颠倒排列，即为所求下一个排列集合
 *
 * 　递归解法(又可称为回溯解法)
 *  回溯解法可处理全排列全组合或类似于八皇后问题或如
 * 　输入两个整数n和m,从数列1,2,3,...,n中随意取几个数，使其和为m,列出所有的组合
 * 　训练: 二分查找和回溯法
 */

void swap_str(char *a,char *b){
	char temp=*a;
	*a=*b;
	*b=temp;
}

/*在字符数组str中，判断在[pbegin,cur)中是否cur指针对应的字符有重复*/
int isDuplicate(char *str,char *pbegin,char *cur){	
	for(char *pstr=pbegin; pstr !=cur;pstr++){
		if(*pstr==*cur)
			return 1;
	}
	return 0;
}

/**
　* 思路是: 将字符串分成两部分－第一个字符和后面的字符部分
 * 求所有可能出现在第一个位置的字符，即第一个字符与所有后面的字符都交换一次,在交换了后面字符后，
 * 再递归处理以下一个位置为起始字符的后面字符的排列
 
 * 通过定义一个辅助函数来实现
 * pstr指向整个字符串，pbegin指向我们做排列操作的字符串的第一个字符
 *

 * 如果考虑到重复元素呢？
 * 例如计算abb的全排列->则第一个字符交换后得到bab\bba,而bab本身又可以交换到bba与前面重复
 * 我们可以考虑到在a与后面第二个字符b交换时，由于第三个字符与第二个字符相等，则不用交换第三个字符b,即去掉了重复元素

 * 故而全排列中去重复的策略是: 从第一个数字起，每个数分别与后面非重复出现的数字交换，
 * 要求在这个范围内没有与交换字符重复的元素，并且第一个字符与后面字符相同时可以不用交换
 */
void permutation(char *str,char *pbegin){
	if(*pbegin =='\0'){ //pbegin为字符串结束标志'\0'时，输出当前字符数组
		printf("%s\n",str);
	} else {
		for(char *cur=pbegin;*cur !='\0';cur++){
			if(isDuplicate(str,pbegin,cur)==0) {
				swap_str(cur,pbegin); 
				permutation(str,pbegin+1);//递归遍历剩余字符串的排列
				swap_str(cur,pbegin);　//*cur==*pbegin时可以省去元素交换操作
			}
		}
	}
}

void all_pert(char *pstr){
	if(pstr==NULL)
		return;
	permutation(pstr,pstr);
}

void test(char *testname,char *str){
	if(testname!=NULL){
		printf("%s string: ",testname);
		if(str==NULL)
			printf("NULL string:\n ");
		else
			printf("%s\n",str);
		all_pert(str);
		printf("\n");
	}
}

/**
 * 测试用例：
 * 功能测试(含有1个字符或多个字符)，是否考虑重复字符呢？
 * 特殊输入测试(空指针、空字符串)
**/

//空字符串
void test_case1(){
	char str[]="";
	test("Case 1 test",str);
}

//一个字符
void test_case2(){
	char str[]="a";
	test("Case 2 test",str);
}

//两个字符
void test_case3(){
	char str[]="ab";
	test("Case 3 test",str);
}

//多个字符
void test_case4(){
	char str[]="aabab";
	test("Case 4 test",str);
}

//空指针
void test_case5(){
	test("Case 5 test",NULL);
}


/* 方法２:
 * 上面的实现有一缺点就是指针操作容易出错，我们可以改用为下标操作来实现
 *
 * begin表示字符串中的首字符，将字符串分为两部分
 * 交换首字符和后面的字符；递归方式处理后面字符串；恢复交换前的字符状态
 *
 * 细节1: 后面字符与首字符相同，可不用交换
 * 细节2: 通过判定在[begin,i)中若有元素与str[i]相同，则无需计算重复排列
 * 全排列的非递归:由尾部到头部向前找第一组满足大小关系的两个元素a、b，
 * 然后再由后向前找到第一个比元素a大的数c,再颠倒自b后的所有数据
 * 即通过计算当前排列的下一个排列借助一个循环输出元素的所有全排列
 */


int exist_dup(char *str,int begin,int cur){
	for(int i=begin;i !=cur;i++){
		if(str[i]==str[cur])
			return 1;
	} 
	return 0;
}

void permutation_improve(char *str,int begin,int len){
	if(begin ==len-1){
		printf("%s\n",str);
	} else {
		for(int i=begin;i<=len-1;i++){
			if(exist_dup(str,begin,i)==0){ 
				if(i!=begin) 
					swap_str(&str[begin],&str[i]); 
				permutation_improve(str,begin+1,len);
				if(i!=begin) 
					swap_str(&str[begin],&str[i]);
			}
		}
	}
}

void all_permut(char *str){
	if(str==NULL)
		return ;
	permutation_improve(str,0,strlen(str));
}

void simple_test(){
	char str[]="aaaaa";
	all_permut(str);
}




int main(){
	// test_case1();
	// test_case2();
	// test_case3();
	// test_case4();
	// test_case5();
	simple_test();
	return 0;
}