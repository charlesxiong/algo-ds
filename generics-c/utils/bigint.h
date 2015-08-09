#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIGIT_LEN 200　/*整数可表示的位数*/
#define RADIX_LEN 4 /*一个数组元素用4位表示*/

/*一个数组元素表示表示4个十进制位，即数组是万进制的*/
#define BIGINT_RADIX 10000　

/*数组表示整数的最大长度*/
#define MAX_LEN (DIGIT_LEN / RADIX_LEN + 1) 


/*打印大整数，低位在低地址*/
void bigint_print(int *res,const int len);

/*将输入的字符数组转化为大整数*/
void bigint_input(const char *str,int *res);

/*大整数加法*/
void bigint_add(int *num1,int *num2,int *res);

/*大整数减法*/
void bigint_sub(int *num1,int *num2,int *res);

/*大整数乘法*/
void bigint_multiply(int *num1,int *num2,int *res);

/*大整数除法*/
void bigint_divide(int *num1,int *num2,int *res);

/*计算n的阶乘，res数组存放结果*/
void bigint_factorial(int n,int *res);

#endif