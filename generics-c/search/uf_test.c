#include <stdio.h>
#include <stdlib.h>
#include "uf.h"

#define MAX_LEN 30000

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
	test1();
	return 0;
}