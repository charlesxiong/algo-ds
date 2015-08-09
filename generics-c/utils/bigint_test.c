#include <stdio.h>
#include "bigint.h"

/************************************************
 *
 * 大整数加减乘除的快速求法
 *
 ***********************************************/
void add(char *a,char *b,char *res) {
	int alen = strlen(a);
	int blen = strlen(b);
	int max_len = (alen > blen)?alen : blen;
	memset(res,'0',max_len + 1);
	res[max_len + 1] = '\0';

	int carry = 0; //进位标志
	int k = max_len;
	for(int i = alen - 1,j = blen -1; i >= 0 || j >= 0;i--,j--,k--) {
		int tmp = carry;
		if(i >= 0) tmp += a[i] - '0';
		if(j >= 0) tmp += b[j] - '0';
		if(tmp >= 10) {
			res[k] = tmp - 10 + '0';
			carry = 1;		
		} else {
			res[k] = tmp + '0';
			carry = 0;
		}
	}
	res[k] = carry + '0';
	while(res[k] == '0')  k++;
	for(;k <= max_len;k++)
		printf("%c",res[k]);
	printf("\n");
}

/**
 * 大整数的减法，假设前者表示的整数大于后者，不考虑负数
 * 考虑负数的话只需要换过来减，再加上符号
 */
void sub(const char *a,const char *b) {
	
}

/**
 * 被乘数的第i位和乘数的第j位放在乘积的第i+j位
 */
void multiply(char *a,char *b,char *res) {
	int alen = strlen(a);
	int blen = strlen(b);
	int max_len = alen + blen;
	int *c = malloc(sizeof(int) * max_len);
	memset(c,0,sizeof(int) * max_len);

	for(int i = 0;i < alen;i++)
		for(int j = 0;j < blen;j++) {
			c[i+j+1] +=  (a[i] - '0') * (b[j] - '0');
		}

	/*处理进位*/
	for(int k = max_len - 1; k >=0;k--) {
		if(c[k] >= 10) {
			c[k - 1] += c[k] / 10;
			c[k] %= 10; //取模的数
		}
	}

	int i = 0;
	while(c[i] == 0) i++; //跳过先导0
	int j = 0;
	for(;i < max_len;i++,j++)
		res[j] = c[i] + '0';
	res[j] = '\0';
	for(j = 0; j < max_len;j++)
		printf("%c",res[j]);
	printf("\n");
	free(c);
}

void divide(const char *a,const char *b) {
	
}

void test() {
	/*输入的两个大数，用字符串表示，最多可表示204位的大数*/
	char str1[MAX_LEN * RADIX_LEN];
	char str2[MAX_LEN * RADIX_LEN];

	/*用万进制表示的数*/
	int num1[MAX_LEN];
	int num2[MAX_LEN];

	/*用万进制表示加减乘除运算后的结果*/
	int num_add[MAX_LEN + 1];
	int num_minus[MAX_LEN];
	int num_multiply[MAX_LEN * 2];
	int num_divide[MAX_LEN];
}

int main() {
	return 0;
}
