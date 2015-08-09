#include "bigint.h"

/*打印大整数，低位在低地址*/
void bigint_print(int *res,const int len);

/*将输入的字符数组转化为大整数*/
void bigint_input(const char *str,int *res);

/*大整数加法*/
void bigint_add(int *num1,int *num2,int *res);

/*大整数减法*/
void bigint_sub(int *num1,int *num2,int *res);