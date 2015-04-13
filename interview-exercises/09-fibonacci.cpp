#include <stdio.h>

/**
 * 递归解法实现Fibonacci数列
 * 问题: 递归中存在大量重复计算的子问题、递归栈深度较大时容易造成栈溢出
 * 改进办法: 用循环，保存中间计算的值，达到用空间换取时间的目的
 */
long long fib_solution1(unsigned int n){
	if(n<=0){
		return 0;
	} else if(n==1){
		return 1;
	} else{
		return fib_solution1(n-1)+fib_solution1(n-2);
	}
}

/*基于循环的解法*/
long long fib_solution2(unsigned int n){
	int result[]={0,1};
	if(n<2)
		return result[n];

	long long f1=0;
	long long f2=1;
	long long fib=0;
	for(unsigned int i=2;i<=n;++i){
		fib=f1+f2;
		f1=f2;
		f2=fib;
	}
	return fib;
}

/**
 * (f(n) f(n-1))=((f(1) f(0)) * A^(n-1)
 * A=
 * 1 1
 * 1 0
 * 思路: 先定义一个2*2的矩阵类，然后再实现矩阵乘法操作和矩阵方幂操作函数
 */

struct matrix2by2 {
 	long long m00;
 	long long m01;
 	long long m10;
 	long long m11;

 	matrix2by2(
		long long a=0,
 		long long b=0,
 		long long c=0,
 		long long d=0
	) : m00(a),m01(b),m10(c),m11(d){
		
	}
} ;


matrix2by2 matrix_multiply(matrix2by2 m,matrix2by2 n){
	return matrix2by2(
		m.m00*n.m00+m.m01*n.m10,
		m.m00*n.m01+m.m01*n.m11,
		m.m10*n.m00+m.m11*n.m10,
		m.m10*n.m01+m.m11*n.m11
		);
}

matrix2by2 matrix_power(matrix2by2 m,unsigned int n){
	if(n==1){
		return m;
	} 

	/**
	 * &和==运算符优先级务必要区分清楚，==优先级更高，故而需要添加括号!!!　
	 * 直接使用n&1==0,这是错误的
	 */
	if( (n&1) ==0){ //偶数次方 (n&1)和==运算符优先级
		matrix2by2 result=matrix_power(m,n/2);
		return matrix_multiply(result,result);
	} else { //奇数次方
		matrix2by2 temp=matrix_power(m,(n-1)/2);
		matrix2by2 result=matrix_multiply(temp,temp);
		return matrix_multiply(result,m);
	}
}

long long fib_solution3(unsigned int n){
	if(n<=0)
		return 0;
	else if(n==1)
		return 1;
	else {
		matrix2by2 base=matrix2by2(1,1,1,0);
		matrix2by2 result=matrix_power(base,n-1);
		return result.m00;
	}
}

void test(const char *testname,unsigned int n,long long expected){
	if(testname !=NULL) {
		printf("\n%s: \n",testname);
		if(fib_solution1(n)==expected) {
			printf("solution 1 using recursion method passed \n");
		} else {
			printf("solution 1 using recursion method failed \n");
		}
		if(fib_solution2(n)==expected){
			printf("solution 2 using iteration(loop) method passed \n");
		} else {
			printf("solution 2 using iteration(loop) method failed \n");
		}

		if(fib_solution3(n)==expected){
			printf("solution 3 using matrix multipower & divide/conquer method passed \n");
		} else {
			printf("solution 3 using matrix multipower & divide/conquer method failed \n");
		}
	}
}

/**
 *　功能测试(如输入3/５/10)
 * 边界值测试(如输入0/1/2)
 * 性能测试(如输入40/50/100等)
 * 输入值比较好测试，直接写在main函数里
 */
int main(){
	test("Case 1 test",0,0);
	test("Case 2 test",1,1);
	test("Case 3 test",2,1);
	test("Case 4 test",3,2);
	test("Case 5 test",4,3);
	test("Case 6 test",5,5);
	test("Case 7 test",6,8);
	test("Case 8 test",7,13);
	test("Case 9 test",8,21);
	test("Case 10 test",9,34);
	test("Case 11 test",10,55);

	test("Case 12 test",40,102334155);

	return 0;
}