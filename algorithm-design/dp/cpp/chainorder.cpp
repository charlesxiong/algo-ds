#include <stdio.h>
#include <limits.h>

using namespace std;


/************矩阵链乘法的动态规划算法实现****************************/



/**
 * 构造出一个最优加全部括号的形式,自顶向下递归求解
 */
void construct_chain_order(int **s,int i,int j){
	if(i==j){
		printf("A%d",i);
	} else{
		printf("(");
		construct_chain_order(s,i,s[i][j]);
		construct_chain_order(s,s[i][j]+1,j);
		printf(")");
	}
}

/**
 * 矩阵链乘算法：确定一个具有最小代价的矩阵相乘顺序，以最小化标量乘法次数的方式加上全部括号
 * 输入数据：n个矩阵相乘，生成输入序列P=<p0,p1,...,pn>，长度len=n+1
 * 
 * 三重循环,矩阵链乘的DP算法时间复杂度为O(n^3)：基于矩阵链乘个数l=2..n来进行计算(m[i][i+1]、...、m[i][i+n-1])
 * 二维DP：一个问题通过选择一个右括号k值产生两个独立的子问题，根据子问题结构最优特点
 * 
 */
int compute_chain_order(int *p,int len){
	/*分配辅助数组内存并初始化*/
	int n=len-1; //矩阵的个数
	int **m=new int*[len]; //保存m[i][j]的最小代价
	int **s=new int*[len]; 
	int i;
	for(i=0;i<len;i++){
		m[i]=new int[len];
		s[i]=new int[len];
	}

	for(i=1;i<=n;i++){ // 仅计算有效的矩阵代价
		m[i][i]=0;
	}

	int l,k;
	for(l=2;l<=n;l++)
		for(i=1;i<=n-l+1;i++){
			int j=i+l-1;
			m[i][j]=INT_MAX;
			for(k=i;k<j;k++){
				if(m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j] <m[i][j]){ //直接计算比较无需先保存值
					m[i][j]=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
					s[i][j]=k;
				}
			}
		}
	int min=m[1][n];
	construct_chain_order(s,1,n);
	printf("\n");
	for(i=0;i<len;i++){
		delete[] m[i];
		delete[] s[i];
	}
	delete[] m;
	delete[] s;
	return min;

}

int main(){
	int p[7]={30,35,15,5,10,20,25};
	printf("%d\n",compute_chain_order(p,7));
	return 0;
}
