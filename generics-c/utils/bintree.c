#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"


/*为二叉树分配内存*/
btree_t *bt_alloc(int (*comp)(const void *,const void *)){
	btree_t *t=malloc(sizeof(btree_t));
	t->root=NULL;
	t->n=0;
	t->comp=comp;
	return t;
}

/*借助栈释放每个结点内存，然后再释放二叉树的内存*/
void bt_free(btree_t *t){
	if(t->root){
		btree_node_t **stack=malloc((t->n)* sizeof(btree_node_t *));
		stack[0]=t->root;
		int top=1;
		while(top){
			btree_node_t *cur=stack[--top];
			if(cur->right)
				stack[top++]=cur->right;
			if(cur->left)
				stack[top++]=cur->left;
			free(cur);
		}
		free(stack);
	}
	free(t);
}

/*分配新结点*/
btree_node_t *new_btree_node(void *item) {
	btree_node_t *node=malloc(sizeof(btree_node_t));
	node->left=node->right=NULL;
	node->item=item;
	return node;
}

/**
 * 创建结点parent的孩子结点- parent不为NULL,可使用二级指针，否则应该为二级指针
 * 若是空子树，parent=NULL,更新当前结点；否则根据tag值设置为左孩子还是右孩子
 * tag=0,左孩子; tag=1,右孩子
 */
void bt_setchild(btree_node_t **parent,void *item,int tag) {
	btree_node_t *node=new_btree_node(item);
	if(*parent !=NULL ){
		if(tag==0)
			(*parent)->left=node;
		if(tag==1)
			(*parent)->right=node;
	} else {
		*parent=node;
	}
}

/**
 * 下面提供5种遍历方法: 前序遍历、中序遍历、后序遍历、层次序遍历、Morris遍历
 * 对应了10个实现函数，其中带后缀rec表示用递归的方法实现，iter表示用迭代(栈)的方法实现
 * cb : 表示为一个以二叉树结点为参数的函数指针类型
 */

/*先序遍历，递归*/
 void bt_preorder(btree_t *t, cb visit){
 	bt_preorder_rec(t->root,visit);
 }

void bt_preorder_rec(btree_node_t *cur, cb visit) {
	if(cur==NULL) return ;
	visit(cur);
	bt_preorder_rec(cur->left,visit);
	bt_preorder_rec(cur->right,visit);
}

/*中序遍历，递归*/
void bt_inorder(btree_t *t, cb visit) {
	bt_inorder_rec(t->root,visit);
}

void bt_inorder_rec(btree_node_t *cur, cb visit) {
	if(cur==NULL) return ;
	bt_inorder_rec(cur->left,visit);
	visit(cur);	
	bt_inorder_rec(cur->right,visit);
}

/*后序遍历，递归*/
void bt_postorder(btree_t *t, cb visit) {
	bt_postorder_rec(t->root,visit);
}
void bt_postorder_rec(btree_node_t *cur, cb visit) {
	if(cur==NULL) return ;
	bt_postorder_rec(cur->left,visit);
	bt_postorder_rec(cur->right,visit);
	visit(cur);
}

