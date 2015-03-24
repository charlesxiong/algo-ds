#include <stdio.h>
#include <stdlib.h>
#include "uf.h"

#define MAX_LEN 30000

/*利用并查集检测图是否有环*/

/*图的边表示*/
typedef struct {
	int src;
	int dst;
} edge_t;

typedef struct {
	int v;
	int e;
	edge_t *edge;
} graph_t;

graph_t *graph_create(int v,int e){
	graph_t *graph=malloc(sizeof(graph_t));
	graph->v=v;
	graph->e=e;
	graph->edge=malloc(e*sizeof(edge_t));
	return graph;
}

void graph_free(graph_t *graph){
	free(graph->edge);
	free(graph);
}

int test_iscycle(graph_t *graph){
	uf_t *t=uf_alloc(graph->v);
	int i;
	for(i=0;i < graph->e;i++){
		int x=uf_find(t,graph->edge[i].src);
		int y=uf_find(t,graph->edge[i].dst); 
		if(x==y) return 1; //图中两顶点对应的根相同，则有环
		uf_union(t,x,y);
	}
	return 0;
}

void test(){
	graph_t *graph=graph_create(4,4);

	/*add edge 0-1*/
	graph->edge[0].src=0;
	graph->edge[0].dst=1;

	/*add edge 1-2*/
	graph->edge[1].src=1;
	graph->edge[1].dst=2;

	/*add edge 1-3*/
	graph->edge[2].src=1;
	graph->edge[2].dst=3;

	/*add edge 0-3*/
	graph->edge[3].src=0;
	graph->edge[3].dst=3;

	if(test_iscycle(graph)==1)
		printf("图中存在环!\n");
	else
		printf("图中没有环!\n");
	graph_free(graph);
}



void test1(){
	int n,m,k;	
	while(scanf("%d %d",&n,&m)!=EOF && n > 0){
		uf_t *t=uf_alloc(MAX_LEN);
		while(m--){
			scanf("%d",&k);
			int p,q; //两个学生
			k--;
			scanf("%d",&p);
			while(k--){
				scanf("%d",&q);
				uf_union(t,p,q);
			}
		}
		printf("%d\n",uf_set_size(t,0));
		uf_free(t);
	}
}

int main(){
	//test1();
	test();
	return 0;
}