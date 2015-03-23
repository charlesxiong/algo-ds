#include "uf.h"
#include <stdio.h>
#include <stdlib.h>

/*分配并查集的内存并初始化,n-并查集数组的大小*/
uf_t *uf_alloc(int n){
	uf_t *t=malloc(sizeof(uf_t));
	t->count=n;
	t->id=malloc(n*sizeof(int)); //分配一个连续的堆内存
	int i;
	for(i=0;i<n;i++){
		t->id[i]=-1;
	}
	return t;

}

/*释放并查集内存*/
void uf_free(uf_t *t){
	free(t->id);
	free(t);

}

/*查找包含元素p的树的根－集合标号，带路径压缩,并不改变秩*/
int uf_find(uf_t *t,int p){
	int cur=p;
	while(t->id[p] >=0) p=t->id[p]; //找到根结点
	while(cur !=p){ //遍历查找过程的所有结点，将其结点指向根结点
		int temp=t->id[cur];
		t->id[cur]=p;
		cur=temp; 
	}
	return p; 
}

/*合并包含两元素p和q的树集合*/
void uf_union(uf_t *t,int p,int q){
	int r1=uf_find(t,p);
	int r2=uf_find(t,q); //返回的是索引下标，而不是id值

	if(r1==r2) return; //已在同一集合内，无需再合并
	/*id值作为负数时，它的相反数表示该树中结点的个数*/
	if(t->id[r1] > t->id[r2]){ //r2作为根
		t->id[r2] += t->id[r1];
		t->id[r1]=r2;
	} else {
		t->id[r1] += t->id[r2];
		t->id[r2]=r1;
	}
	t->count--;
}

/*返回并查集中不相交集合的分量个数*/
int uf_count(uf_t *t){
	return t->count;

}

/*返回并查集中包含p元素的集合大小*/
int uf_set_size(uf_t *t,int p){
	int root=uf_find(t,p);
	return -t->id[root];
}