#include <stdio.h>
#include <float.h>
#define MAXLINE 1000
using namespace std;

/************最优二叉查找树的动态规划算法实现****************************/

/**
 * 递归算法得到最优二叉查找树的中序遍历结果(可以结合中序和前序遍历结果得出)
 */
void construct_opt_bst1(int **r,int i,int j){
	if(i<=j){
		int k=r[i][j];	
		printf(" %d ",k);
		construct_opt_bst1(r,i,k-1);	
		construct_opt_bst1(r,k+1,j);
	}
	printf("\n");
}

void construct_opt_bst(int **r,int len,int i,int j,int root){	
	if(j==i-1){ //虚拟关键字节点，区分左右孩子
		if(j < root) { 
			printf("d%d 是 k%d 的左孩子\n",j,root);
		} else{
			printf("d%d 是 k%d 的右孩子\n",j,root);
		}
	} else if(j<i-1){
		return ;
	} else {
		int k=r[i][j]; //仅记录有效根节点，从j>=i开始
		if(i==1 && j==len) {
			printf("k%d 是根\n",k); //k记录当前树的根节点的序号，比较k与root[i][j]的大小决定是左右孩子		
		} else {
			if(k < root) { 
				printf("k%d 是 k%d 的左孩子\n",k,root);
			} else {
				printf("k%d 是 k%d 的右孩子\n",k,root);
			}
		}
		construct_opt_bst(r,len,i,k-1,k);
		construct_opt_bst(r,len,k+1,j,k);
	}
}

float compute_opt_bst(float *p,float *q,int n){
	/*这三个数组是由堆分配的，未初始化值都是未定义的，不像定义的全局数组变量1未初始化结果值是0*/
	float **e=new float*[n+2]; //子树期望代价
	float **w=new float*[n+2]; //子树概率总和
	int **root=new int*[n+1]; //记录子树root[1..n,1..n]的根节点
	
	int i;
	for(i=0;i<=n+1;i++) { //代价和概率和这两个二维数组e[n+2][n+1]、w[n+2][n+1]
		e[i]=new float[n+1];
		w[i]=new float[n+1];
	}

	for(i=0;i<=n;i++){ //仅记录root[1..n,1..n]的根节点（有效子树）
		root[i]=new int[n+1];
	}

	for(i=1;i<=n+1;i++){
		e[i][i-1]=q[i-1];
		w[i][i-1]=q[i-1];
	}


	/**
	 * 三重循环，最优二叉查找树的DP算法时间复杂度为O(n^3)
	 * 二维DP：基于数组长度进行累积计算l=1(a[i][i])、l=2(a[i][i+1])
	 * l=3(a[i][i+2])...l=n(a[i][i+n-1]): 由下到上，由左到右逐步计算最小搜索代价
	 * 并利用root[i][j]记录有效子树的根节点(i=1..n,j=1..n)
	 * 一个问题产生两个独立的子问题，可以做出O(n)个选择
	 */
	int l;
	for(l=1;l<=n;l++) { //
		for(i=1;i<=n-l+1;i++) {
			int j=i+l-1;
			e[i][j]=DBL_MAX;
			w[i][j]=w[i][j-1]+p[j-1]+q[j];
			
			for(int r=i;r<=j;r++){
				float temp=e[i][r-1]+e[r+1][j]+w[i][j]; 
				if(temp<e[i][j]){
					e[i][j]=temp;
					root[i][j]=r;
				}
			}
		}
	}
	float min=e[1][n]; //数据类型一定要弄对，尽量不要有强制类型转换
	construct_opt_bst(root,n,1,n,-1);
	for(i=0;i<=n+1;i++){
		delete[] e[i];
		delete[] w[i];
	}
	for(i=0;i<=n;i++){
		delete[] root[i];
	}
	delete[] e;
	delete[] w;
	delete[] root;
	return min;
}

/**
 * DP之四边形不等式和斜率优化
 * 
 *
 *
 */
void compute_opt_bst_improve(float *p,float *q,int n);

void print_array(void *arr,int length){
	float *p=(float *)arr;
	int i=0;
	for(;i<length;i++)
		printf("%.2f ",p[i]);
	printf("\n");
}

void test_bst(const char *filename){
	FILE *input=fopen(filename,"r");
	if(!input){
		printf("open %s failed\n",filename);
		return;
	}
	int n;
	fscanf(input,"%d",&n);
	printf("the length of the key sequence: %d \n",n);
	float *p=new float[n];
	float *q=new float[n+1];
	int i=0;
	for(;i<n;i++)
		fscanf(input,"%f",&p[i]);
	for(i=0;i<n+1;i++)
		fscanf(input,"%f",&q[i]);
	print_array(p,n);
	print_array(q,n+1);

	printf("%.2f\n\n",compute_opt_bst(p,q,n));

}

int main(){
	
	/**
	 * bst1.txt 数据
	 * p: 0.15 0.10 0.05 0.10 0.20
     * q: 0.05 0.10 0.05 0.05 0.05 0.10
	 */
	test_bst("bst1.txt"); 

	/**
	 * bst2.txt数据
	 * 0.04 0.06 0.08 0.02 0.10 0.12 0.14
     * 0.06 0.06 0.06 0.06 0.05 0.05 0.05 0.05
	 */
	test_bst("bst2.txt");

	return 0;
}