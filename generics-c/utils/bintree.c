#include <stdio.h>
#include <stdlib.h>
#include "bintree.h"
#include "queue.h"


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

int bt_size(btree_t *t){
	return t->n;
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

/**
 * 基于栈的VLR先序遍历
 * 整体思路：先入栈根节点，然后再判断栈是否为空：不为空，出栈当前元素，并按照左右子树顺序分别入栈
 * 该方法可借助栈的操作，如下类似于栈的实现方式
 * 入栈顺序: VRL
 */
void bt_preorder_iter(btree_t *t, cb visit){
	if(t->root){		
		btree_node_t **stack=malloc(sizeof(btree_node_t *)*(t->n));
		stack[0]=t->root;
		int top=1;
		while(top>0){ //只要栈不为空
			btree_node_t *cur=stack[--top];//出栈
			visit(cur);
			if(cur->right)
				stack[top++]=cur->right;
			if(cur->left)
				stack[top++]=cur->left;
		
		}
		free(stack);
	}
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

/**
 * 基于栈的中序遍历
 * 整体思路：判断条件有两个：栈是否为空或当前节点是否为空
 * 根据中序遍历顺序LVR
 * 栈为空，需不断压栈当前每个非空节点一直遍历到第一个没有左孩子的根结点
 * 此时cur为空，top(栈中的元素大小)只要大于0
 * 开始进行出栈，访问当前节点,再 遍历右子树
 */
void bt_inorder_iter(btree_t *t, cb visit){
	btree_node_t **stack=malloc(sizeof(btree_node_t *)*(t->n));
	btree_node_t *cur=t->root;
	int top=0;
	while(top>0|| cur!=NULL){
		if(cur !=NULL){
			stack[top++]=cur;
			cur=cur->left;
		} else{
			cur=stack[--top];//出栈当前栈顶元素
			visit(cur);
			cur=cur->right;
		}
	}
	free(stack);
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


/**
 * 基于栈的后序遍历
 * 用栈存储节点时，必须分清返回根结点时：是从左子树返回的还是从右子树的返回的
 * 这里用一个pre指针记录最近刚访问过的节点
 * 当一直往左直到左孩子为空时,判断当前节点的右孩子是否为空或者是否已访问过
 * 若右孩子为空或者已被访问过(LV或者LRV),则访问当前节点，并更新最近访问的节点，并重置当前指针为NULL
 * 否则遍历右孩子(压栈)，再转向左
 */
void bt_postorder_iter(btree_t *t, cb visit){
	btree_node_t **stack=malloc(sizeof(btree_node_t *)*(t->n));
	btree_node_t *cur=t->root;
	btree_node_t *pre=NULL; //指向最近访问过的节点
	int top=0;
	while(cur!=NULL||top>0){ //当前节点不为空或者栈不为空
		if(cur){ //压栈，一直往左走
			stack[top++]=cur; 
			cur=cur->left;
		} else {
			cur=stack[top-1];//取栈顶元素
			if(cur->right&&cur->right!=pre){ //如果右子树存在，且未被访问过
				cur=cur->right;
				stack[top++]=cur; //转向右，压栈
				cur=cur->left;//再走向最左，始终保持LRV的遍历顺序
			} else{ //要么右孩子为空，要么右孩子已经被访问过，弹出当前节点
				cur=stack[--top];
				visit(cur);
				pre=cur; //记录最近访问过的节点，节点访问完重置cur指针
				cur=NULL;
			}
		}
	}
	free(stack);
}

/*层次序遍历，队列*/
void bt_levelorder(btree_t *t,cb visit){
	
}

/*Morris先序遍历*/
void bt_morris_preorder(btree_t *t, cb visit){

}

/*Morris中序遍历*/
void bt_morris_inorder(btree_t *t, cb visit){

}

/*Morris后序遍历*/
void bt_morris_postorder(btree_t *t, cb visit){
	
}

