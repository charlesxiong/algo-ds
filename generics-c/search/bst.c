#include <stdlib.h>
#include "bst.h"

/**
 * bst.c - Binary Search Tree Implementation
 * 
 */

/*为二叉查找树分配内存，comp是一个比较两元素大小的函数指针*/
bst_t *bst_alloc(int (*comp)(const void *,const void *)){
	bst_t *t=malloc(sizeof(bst_t));
	t->root=NULL;
	t->n =0;
	t->comp=comp;
	return t;
}

/*释放二叉查找树的内存*/
void bst_free(bst_t *t) {
	bst_node_t *cur;
	bst_node_t **stack; //维护一个指向bst_node结点的的指针数组栈

	/**
	 * 释放每个结点的内存: 通过VRL的访问方式，根结点首先入栈
	 * 如果栈不空，结点出栈，若结点的孩子不空，子结点入栈(先右后左),再释放当前根结点空间
	 * 只要栈不空采用DFS遍历的方式重复上面的操作
	 * 和VRL遍历方式类似
	 */
	if(t->root){ //根结点不空
		//分配n个指针元素的内存
		stack=malloc((t->n) * sizeof(bst_node_t *));
		stack[0]= t->root; //根结点入栈
		int top=1;
		while(top) {
			cur=stack[--top]; //出栈
			if(cur->right){ //以先右后左方式入栈保存子结点，出栈则以先左后右
				stack[top++]=cur->right;
			}
			if(cur->left){
				stack[top++]=cur->left;
			}
			free(cur);
		}
		free(stack); //注意不释放栈内存则产生内存泄露
	}
	free(t);
}


/**
 * bst_insert(): 要求插入的元素项的键不能和树中元素键相同，键独一无二
 *　思路: 首先检查该元素是否已经存在，若查找成功，直接返回该位置
 * 否则查找不成功，把新元素插入到查找停止的地方
 */
void *bst_insert(bst_t *t,void *item) {
	int (*comp)(const void *,const void *);
	bst_node_t *prev=NULL; //保存待插入结点的父结点
	int cmp_res;
	if(t->root){
		bst_node_t *cur=t->root;
		comp=t->comp;
		while(cur){
				cmp_res=comp(item,cur->item);
				if(cmp_res < 0){
					prev=cur;
					cur=cur->left;
				} else if(cmp_res > 0) {
					prev=cur;
					cur=cur->right;
				} else
					return cur->item; //找到了并返回关键字item,不再插入
		}
	} 


	/*构造新结点*/
	bst_node_t *node=malloc(sizeof(bst_node_t));
	node->left=node->right=NULL;
	node->item=item;

	if(!prev){
		t->root=node;
	} else {
		cmp_res=comp(item,prev->item);
		if(cmp_res < 0){
			prev->left=node;
		} else {
			prev->right=node;
		}
	}

	t->n++;

	return NULL;//插入成功返回NULL
}
	

/**
 * bst_find():  查找树中的某个关键字
 *　思路: 先与根结点比较，若相同则查找结束
 *　否则根据比较结果，沿着左子树或右子树向下继续查找
 * 如果没有找到，返回NULL
 * 注: 这里的item是指关键字的值，而非结点
 */

void *bst_find(bst_t *t ,void *item){
	bst_node_t *cur;
	int (*comp)(const void *,const void *);
	cur=t->root;
	comp=t->comp;
	while(cur){
			int cmp_res=comp(item,cur->item);
			if(cmp_res < 0){
				cur=cur->left;
			} else if(cmp_res > 0) {
				cur=cur->right;
			} else
				return cur->item; //找到了并返回关键字item
	}
	return NULL;
}
	



/*返回二叉查找树中的含最小键值的结点*/
void *bst_find_min(bst_t *t) {
	bst_node_t *cur;
	if(t->root){
		cur=t->root;
		while(cur->left){
			cur=cur->left;
		}
		return cur->item;
	} else {
		return NULL;
	}
}


/**
 * bst_delete : 删除树中的某个结点，还必须保证BST树的排序不会丢失
 * 思路: (1) 被删除结点是叶结点，直接删除，不会影响BST的性质
 * (2) 若结点z只有一颗左子树或者右子树，让z的子树成为z父结点的子树，替代z位置
 * (3) 若结点有两个子树，令它的直接后继(直接前驱)替代z,
 *  再从BST树中删除该直接后继(直接前驱)，这样转换成了前两个情况
 */
void *bst_delete(bst_t *t,void *item) {
	bst_node_t *cur,*prev;
	int (*comp)(const void *,const void *);
	prev=NULL;
	if(t->root){
		cur=t->root;
		comp=t->comp;
		while(cur){
				int cmp_res=comp(item,cur->item);
				if(cmp_res < 0){
					prev=cur;
					cur=cur->left;
				} else if(cmp_res > 0) {
					prev=cur;
					cur=cur->right;
				} else
					break; //找到了并返回关键字item
			}
	} else {
		return NULL;
	}
    
    /*前两个条件可表示三种情形*/
	if(!cur->left){ //左孩子为空，右孩子代替它
		if(!prev){
			t->root=cur->right;
		} else if(cur==prev->left) {
			prev->left=cur->right;
		} else {
			prev->right=cur->right;
		}
	} else if(!cur->right){ //右孩子为空，左孩子代替它
		if(!prev){
			t->root=cur->left;
		} else if(cur==prev->left) {
			prev->left=cur->left;
		} else {
			prev->right=cur->left;
		}
	}  else { //找到当前结点右子树的最左孩子　
		bst_node_t *prev_cur=cur;
		bst_node_t *cur_cur=cur->right;
		while(cur_cur->left){
			prev_cur=cur_cur; 
			cur_cur=cur_cur->left;
		}

		/*更新cur结点的父亲结点prev的孩子链接信息*/
		if(!prev){
			t->root=cur_cur;
		} else if(cur==prev->left){
			prev->left=cur_cur;
		} else {
			prev->right=cur_cur;
		} 

		/*更新cur_cur的左右孩子链接信息*/
		if(prev_cur!=cur){ //最左孩子的父结点不是要删除的结点, cur_cur不是cur的右孩子
			prev_cur->left=cur_cur->right;
			cur_cur->right=cur->right;
		}
		cur_cur->left=cur->left;
	}
	void *res_item=cur->item;
	free(cur);
	t->n--;

	return res_item;
}

/*删除BST树中最小的键值结点*/
void *bst_delete_min(bst_t *t){
	bst_node_t *cur,*prev;
	prev=NULL;
	if(t->root){
		cur=t->root;	
		while(cur->left){
			prev=cur;
			cur=cur->left;
		}
	} else {
		return NULL;
	}

	if(!prev){
		t->root=cur->right;
	} else {
		prev->left=cur->right;
	}

	void *res_item=cur->item;
	free(cur);
	t->n--;

	return res_item;
}
