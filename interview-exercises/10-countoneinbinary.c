#include <stdio.h>

/*统计某值二进制中1的个数*/

/**
 * 仅适用于无符号数，因为负数的二进制表示右移时在高位补1,
 * 如果一直做右移运算，最终这个数字会变成0xFFFFFFFF而陷入死循环
 */
int num_one_binary(unsigned int v){
	int cnt=0;
	while(v){
		if(v&1)
			++cnt;
		v >>=1;
	}
	return cnt;
}

/**
 * 考虑不右移输入的数字v,而是借助一个无符号的flag，初始化为1
 * 在不断左移flag的过程中，判断n的当前位是否为1,统计1的个数
 * 循环的次数等于整数二进制的位数，即需要循环32次
 */
int num_one_binary_improve(int v){
	int cnt=0;
	unsigned int flag=1;
	while(flag){
		if(flag&v)
			++cnt;
		flag <<=1;
	}
	return cnt;
}

/**
 * v&(v-1)的效果是把整数的二进制表示最右边一个1变成0
 * 则一个整数的二进制中有多少个1,则多少次这样的操作
 * 循环的次数等于整数二进制中1的次数
 *
 * 用于判断整数是不是2的整数次方，只需(v&(v-1))==0即可
 * 注意0不为2的次幂，因而需要判断v&&!(v&(v-1))为true即可
 */
int num_one_binary_opt(int v){
	int cnt=0;
	while(v){
		++cnt;
		v &=(v-1);
		
	}
	return cnt;
}

/**
 * 填表法的思路:
 * i为偶数时，对应二进制中1的个数与i/2二进制中1的个数相同(因为i是i/2移位得来的，移位并未增加1的个数)
 * i为奇数时，对应二进制中1的个数等于i/2二进制中1的个数 + 1
 */ 
int num_one_binary_table(int v){
	unsigned char bstable[256]={0};
	for(int i=0;i<256;i++){
		bstable[i]=(i&1)+bstable[i/2];
	}
    
    /*通过类型转换得到每8bit上的二进制表示*/
	unsigned char *p=(unsigned char *)(&v);
	int cnt=bstable[p[0]]+
			bstable[p[1]]+
			bstable[p[2]]+
			bstable[p[3]];
	return cnt;
}

/**
 * 最快的思路: 平行算法(分而治之)
 * 整个程序是一个分治思想
 * b[0]特性是取二进制表示中的所有的偶数位，第一次运算的效果是把二进制表示中偶数位和奇数位相加(相邻位相加)
 * b[1]特性是取二进制每四位的后两位，第二次运算的效果是把二进制表示中每四位的前两位和后两位相加(相邻两位相加)
 * b[2]特性是取二进制每八位的后四位，第三次运算的效果是把二进制表示中每八位的前四位和后四位相加(相邻四位相加)
 * b[3]特性是取二进制每16位的后8位，第四次运算的效果是把二进制表示中每16位的前8位和后8位相加(相邻八位相加)
 * b[4]特性是取二进制每32位的后16位，第五次运算的效果是把二进制表示中每32位的前16位和后16位相加(相邻十六位相加)
 */
int num_one_binary_parallel(int v){
	const int b[]={0x55555555,0x33333333,0x0F0F0F0F,0x00FF00FF,0x0000FFFF};

	v= (v&b[0])+((v>>1)&b[0]);
	v= (v&b[1])+((v>>2)&b[1]);
	v= (v&b[2])+((v>>4)&b[2]);
	v= (v&b[3])+((v>>8)&b[3]);
	v= (v&b[4])+((v>>16)&b[4]);
	return v;
}

/**
 * 利用这种分治思想可以实现二进制逆序
 * 同样利用b数组特性：先相邻位交换，再相邻2位交换，再相邻4位交换直至相邻16位交换
 * 交换办法: 如交换相邻位偶数位左移1位，奇数位右移1位再做或运算
 * 需要构造新数组:所有k位的前k/2位
 * const int c[]={0xAAAAAAAA,0xCCCCCCCC,0xF0F0F0F0,0xFF00FF00,0xFFFF0000}
 * 实现如下:
 * v =((v&b[0])<<1) | ((v&&c[0])>>1);
 * v =((v&b[1])<<2) | ((v&&c[1])>>2);
 * v =((v&b[2])<<4) | ((v&&c[2])>>4);
 * v =((v&b[3])<<8) | ((v&&c[3])>>8);
 * v =((v&b[4])<<16) | ((v&&c[4])>>16);
 */



void test(const char *testname,int v,int expected){
	if(testname!=NULL){
		printf("\n%s for %d : \n",testname,v);
		
		// if(num_one_binary(v)==expected) //不建议使用此方法
		// 	printf("Passed\n");
		// else
		// 	printf("Failed\n");

		if(num_one_binary_improve(v)==expected) 
			printf("Solution 2 using flag method passed\n");
		else
			printf("Solution 2 using flag method failed\n");

		if(num_one_binary_opt(v)==expected) 
			printf("Solution 3 using & operation method passed\n");
		else
			printf("Solution 3 using & operation method failed\n");

		if(num_one_binary_table(v)==expected) 
			printf("Solution 4 using look-up table method passed\n");
		else
			printf("Solution 4 using look-up table method failed\n");

		if(num_one_binary_parallel(v)==expected) 
			printf("Solution 5 using parallel method passed\n");
		else
			printf("Solution 5 using parallel method failed\n");
	}
}

/**
 * 功能测试(正常的整数、负数和0)
 * 边界值测试(1,0x7FFFFFFF,0x80000000,0xFFFFFFFF)
 */
int main(){
	test("Case 1 test",0,0);
	test("Case 2 test",3,2);
	test("Case 3 test",182,5);
	test("Case 4 test",1,1);
	test("Case 5 test",0x7FFFFFFF,31);
	test("Case 6 test",0x80000000,1);
	test("Case 7 test",0xFFFFFFFF,32);
	return 0;
}