#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"

#define MAX_LEN 10

int int_cmp(const void *a,const void *b){
	return *((int *)a) - *((int *)b);
}

int char_cmp(const void *a,const void *b){
	return *((char *)a) - *((char *)b);
}

void visit(btree_node_t *cur){
	if(cur)
		printf("%d ",*(int *)cur->item);
}

int main(){
	btree_t *t=bt_alloc(int_cmp);
	int arr[MAX_LEN]={1,2,5,6,3};
	// bt_setchild(&t->root,&arr[0],0);
	// bt_setchild(&t->root,&arr[1],0);
	// bt_setchild(&t->root,&arr[2],1);
	// bt_setchild(&t->root->left,&arr[3],0);
	// bt_setchild(&t->root->right,&arr[4],1);

	/**
	            1
	           /  \
	          2    5
	              / \
	             6   3
	 */
	t->root=new_btree_node(&arr[0]);
	t->root->left=new_btree_node(&arr[1]);
	t->root->right=new_btree_node(&arr[2]);
	t->root->right->left=new_btree_node(&arr[3]);
	t->root->right->right=new_btree_node(&arr[4]);

	printf("先序遍历(递归): ");
	bt_preorder(t,visit);
	printf("\n");

	printf("中序遍历(递归): ");
	bt_inorder(t,visit);
	printf("\n");

	printf("后序遍历(递归): ");
	bt_postorder(t,visit);
	printf("\n");

	bt_free(t);

	return 0;
}