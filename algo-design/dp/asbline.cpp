#include <stdio.h>

using namespace std;

/************装配线调度的动态规划算法实现****************************/

void construct_assembline(int n,int lastl,int *l1,int *l2,int j){
	if(j==n){
		if(lastl==1){
			construct_assembline(n,lastl,l1,l2,j-1);
			printf("station %d,line %d\n",n,1);
		} else {	
			construct_assembline(n,lastl,l1,l2,j-1);
			printf("station %d,line %d\n",n,2);
		} 
	} else if(j<n && j>0){
		if(lastl==1){
			construct_assembline(n,l1[j],l1,l2,j-1);
			printf("station %d,line %d\n",j,l1[j]);
		} else {
			construct_assembline(n,l2[j],l1,l2,j-1);
			printf("station %d,line %d\n",j,l2[j]);
		}
	} else {
		return ;
	}
}

/**
 * 输入数据：
 * 停留在装配线i的第j个装配站的装配时间a[i][j](i=0..2,j=0..n-1)
 * 进入装配线i的时间为e[i]、离开装配线i的时间为x[i](i=0..1)
 * 在装配站(s[i][j])移动到另外一条线花费的时间为t[i][j](i=0..1,j=0..n-1)
 *
 * 问题要求：确定应该在装配线1内选择哪些站，在装配线2内选择哪些站，使得汽车通过工厂的总时间最小 
 * 动态规划公式：
 * f1[j]记装配线1通过装配站s[0][j]的最快路线，f2[j]记装配线2通过装配站s[1][j]的最快路线
 * l1[j]记到达站j时前j-1的装配线编号, l2[j]记到达站j时前j-1的装配线编号
 * f=min(f1[n]+x1,f2[n]+x2),取最小值，对应相应的装配线
 *
 * 细节1：参数是指针的指针，实际上对应的是指针数组而非二维数组；而二维数组实际上对应的是一维数组的指针
 * (int **p- int *p[6];int (*p)[6]- int p[][])
 */

int compute_assembline(int **a,int **t,int *e,int *x,int n){

	/*分配辅助变量内存并初始化*/
	int *f1=new int[n];//到达1号装配线的各个装配站的最优时间，装配站标号从0开始(表示第1个装配站)
	int *f2=new int[n];//到达1号装配线的各个装配站的最优时间，装配站标号从0开始(表示第1个装配站)
	int *l1=new int[n]; //这两行表示到达某装配站前经过的装配线编号，有效编号从1开始(表示第2个装配站)
	int *l2=new int[n];
	int lastl,final; //完成装配时经过的装配线和通过整个工厂的最快时间

	f1[0]=e[0]+a[0][0];
	f2[0]=e[1]+a[1][0];

	/**
	 * 自底向上以迭代递增的方式计算出通过工厂的最快路线及所选的配送站，时间复杂度为O(n)
	 * 通过记录表格，保存已经求解的子问题，而后只需通过查表确定，典型的以空间换时间思路
	 *
	 */
	int j;
	for(j=1;j<=n-1;j++){
		if(f1[j-1]+a[0][j] <= f2[j-1]+t[1][j-1]+a[0][j]){
			f1[j]=f1[j-1]+a[0][j];
			l1[j]=1; //选择从装配线1的j-1站传送到j站
		} else {
			f1[j]=f2[j-1]+t[1][j-1]+a[0][j];
			l1[j]=2; //选择从装配线2的j-1站移动到j站
		}

		if(f2[j-1]+a[1][j] <= f1[j-1]+t[0][j-1]+a[1][j]){
			f2[j]=f2[j-1]+a[1][j];
			l2[j]=2; //选择从装配线1的j-1站移动到j站
		} else {
			f2[j]=f1[j-1]+t[0][j-1]+a[1][j];
			l2[j]=1; //选择从装配线2的j-1站传送到j站
		}
	}

	if(f1[n-1]+x[0]<= f2[n-1]+x[1]){ //从装配线1退出时间更快
		final=f1[n-1]+x[0];
		lastl=1; //从装配线1离开
	} else {
		final=f2[n-1]+x[1];
		lastl=2; //从装配线1离开
	}
	construct_assembline(n,lastl,l1,l2,n);
	delete[] f1;
	delete[] f2;
	delete[] l1;
	delete[] l2;
	return final;
}

void test_assembline(const char *filename){
	FILE *input=fopen(filename,"r");
	if(!input){
		printf("open %s failed\n",filename);
		return;
	}
	int n;
	fscanf(input,"%d",&n);

	//分配装配时间数组、移动花费时间数组、进入和退出装配线数组内存，并从文件中读入数据
	int **a=new int*[2];
	int **t=new int*[2];
	int *e=new int[2];
	int *x=new int[2];
	int i,j;
	for(i=0;i<2;i++)
		a[i]=new int[n];
	for(i=0;i<2;i++)
		t[i]=new int[n-1];


	for(i=0;i<2;i++){
		for(j=0;j<n;j++)
			fscanf(input,"%d",&a[i][j]);
	}
	for(i=0;i<2;i++){
		for(j=0;j<n-1;j++)
			fscanf(input,"%d",&t[i][j]);
	}
	for(i=0;i<2;i++)
	 	fscanf(input,"%d",&e[i]);
	for(i=0;i<2;i++)
	 	fscanf(input,"%d",&x[i]);

	printf("%d\n",compute_assembline(a,t,e,x,n)); 

	for(i=0;i<2;i++) {
		delete[] a[i];
		delete[] t[i]; 
	}
	delete[] a;
	delete[] t;
	delete[] e;
	delete[] x;
}


int main(){

	/**
	 * ast1.txt 数据
	 * 6
     	 * 7 9 3 4 8 4 8 5 6 4 5 7
         * 2 3 1 3 4 2 1 2 2 1
         * 2 4 3 2
	 */
	test_assembline("ast1.txt");
	return 0;
}
