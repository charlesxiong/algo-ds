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


/**
 * 基于队列的层次序遍历，跟先序遍历一样，区别就是栈换成了队列
 * 这里没有使用表示队列的函数，而是采用了类似于队列操作的实现方式
 */
void bt_levelorder(btree_t *t,cb visit){
	if(t->root){
		int maxsize=t->n;
		btree_node_t **queue=malloc(sizeof(btree_node_t *)*(t->n));
		btree_node_t *cur;
		int front=0;
		int rear=0;
		rear=(rear+1)%maxsize;
		queue[rear]=t->root;
		while(front!=rear){ //判断队列是否为空
			front=(front+1)%maxsize;
			cur=queue[front];//出队
			visit(cur);
			if(cur->left){
				rear=(rear+1)%maxsize;
				queue[rear]=cur->left;	//入队
			}
			if(cur->right){
				rear=(rear+1)%maxsize;
				queue[rear]=cur->right;//入队
			}
		}
		free(queue);
	}
}

/**
 * Morris遍历只需要O(1)的空间复杂度，这种算法跟线索化二叉树很像
 * 不过Morris遍历是一边建立线索一边访问数据，访问完后直接销毁线索，保持二叉树的不变
 * 它的原则比较简单：借助所有叶结点的右指针(空指针)指向其后继节点，组成一个环
 * 但由于第二次遍历到这个结点时，由于左子树已经遍历完了，就访问该结点
 */


/*Morris先序遍历*/
void bt_morris_preorder(btree_t *t, cb visit){
	if(t->root){
		btree_node_t *cur=t->root;
		btree_node_t *pre; //前驱线索
		while(cur){
			if(cur->left==NULL){
				visit(cur);
				pre=cur;
				cur=cur->right; //记录直接前驱，转向右孩子
			} else{
				btree_node_t *tmp=cur->left;
				while(tmp->right&&tmp->right!=cur)
					tmp=tmp->right;

				if(tmp->right==NULL){ //表明右子树未被访问，访问当前节点，更新线索，转向左孩子
					visit(cur); //仅这一行位置与中序不同
					tmp->right=cur;
					pre=cur;//标记当前节点被访问过(这个与visit函数在同一个代码都安内)
					cur=cur->left;
				} else { //表明左子树已被访问，重置线索，转向右孩子
					tmp->right=NULL;
					/*pre=cur; 不能有这句，因为cur早早被访问*/			
					cur=cur->right;
				}
			}
		}
	}
}


/**
 * 初始化当前节点cur为root节点
 * 若当前cur没有左孩子，直接访问当前结点，cur转向右孩子
 * 若cur有左孩子，先寻找到cur的前驱节点
 * 如果前驱节点右孩子为空，记录前驱节点右孩子为当前结点，cur转向左孩子
 * 如果前驱节点右孩子为当前节点，表明左孩子已被访问，将前驱节点右孩子重设为空
 * 直接访问当前结点，cur转向右孩子
 */
void bt_morris_inorder(btree_t *t, cb visit){
	if(t->root){
		btree_node_t *cur=t->root;
		btree_node_t *pre; //前驱线索
		while(cur){
			if(cur->left==NULL){
				visit(cur);
				pre=cur; //记录已被访问的前驱
				cur=cur->right;
			} else{
				/*先找到cur的前驱节点*/
				btree_node_t *tmp=cur->left;
				while(tmp->right&&tmp->right!=cur)
					tmp=tmp->right;

				if(tmp->right==NULL){ //表明左子树未访问，先建立线索再访问左子树
					tmp->right=cur; 
					cur=cur->left;//没有访问，无需记录pre指针
				} else { //左子树已被访问，则访问当前节点，恢复二叉树,遍历右子树
					visit(cur);
					tmp->right=NULL;
					pre=cur;
					cur=cur->right;
				}
			}
		}
	}
}

/*****************Morris后序遍历的辅助函数****************/

/*逆转一条分支节点的路径: 逆置节点上的右孩子*/
void reverse_node(btree_node_t *from,btree_node_t *to){
	btree_node_t *cur=from;
	btree_node_t *next=cur->right;
	if(from==to) return;

	while(cur!=to) {
		btree_node_t *tmp=next->right;
		next->right=cur;
		cur=next;
		next=tmp;
	}
}

/*访问逆转后的路径上所有的节点*/
void reverse_branch(btree_node_t *from,btree_node_t *to,cb visit){
	btree_node_t *cur=to;//记录下逆置后的起始节点
	reverse_node(from,to);
	while(1){
		visit(cur);
		if(cur==from)
			break;
		cur=cur->right;
	}
	reverse_node(to,from); //恢复原有路径指向
}


/**
 * Morris后续遍历稍微麻烦点：
 * 它必须保证在访问某个当前节点时，左右子树的所有左孩子必须先被访问;而右孩子的输出从底部往顶部逆向访问就行
 * 思路：设置一个虚拟根结点，记它的左孩子为root,即当前cur为该虚拟根结点
 * 如果cur的左孩子为空，先记录会被访问的当前节点再转向右孩子分支
 * 如果cur的左孩子不为空，找到cur的前驱
 *     如果前驱的右孩子为空，建立线索化，记录会被访问的当前节点再转向左孩子分支
 *     如果前驱的右孩子为当前节点，表示已经线索化，因而逆向输出当前节点左孩子到该前驱节点路径上的所有节点
 *     转向当前节点右孩子分支
 */
void bt_morris_postorder(btree_t *t, cb visit){
	if(t->root){
		btree_node_t *rec=malloc(sizeof(btree_node_t));
		rec->left=t->root; //创建一个dummy结点，它的左孩子指向根结点
		btree_node_t *cur=rec;//从虚拟根结点开始遍历
		btree_node_t *pre;
		while(cur){
			if(cur->left==NULL){
				pre=cur;//和前两个morris遍历不同，这种方法是先线索化后保证一侧子树都被访问完后直接逆向输出
				cur=cur->right;//一般是先访问后再记录被访问的节点，这次相反先记录将被访问的节点后再访问
			} else {
				btree_node_t *tmp=cur->left;
				while(tmp->right&&tmp->right!=cur)
					tmp=tmp->right;

				if(tmp->right==NULL){ //还未线索化，未被访问，先建立线索
					tmp->right=cur;//保证下一次循环时回到后继节点，此时已被线索化
					pre=cur;//必须要有，先记录
					cur=cur->left;
				} else{ //已建立线索
					reverse_branch(cur->left,tmp,visit);
					pre->right=NULL;
					pre=cur; //必须要有
					cur=cur->right;
				}

			}
		}
		free(rec);
	}
}

