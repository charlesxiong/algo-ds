#ifndef _BINTREE_H_
#define _BINTREE_H_

typedef struct btree_node {
	void *item;
	struct btree_node *left;
	struct btree_node *right;
} btree_node_t;

typedef struct  {
	btree_node_t *root;
	int n;
	int (*comp)(const void *,const void *);
} btree_t;

typedef void (*cb)(btree_node_t *);

/*为二叉树分配内存*/
btree_t *bt_alloc(int (*comp)(const void *,const void *));

/*释放二叉树的内存*/
void bt_free(btree_t *t);

/*分配新结点*/
btree_node_t *new_btree_node(void *item);

/**
 * 创建结点parent的孩子结点- parent不为NULL,可使用二级指针，否则应该为二级指针
 * 若是空子树，parent=NULL,更新当前结点；否则根据tag值设置为左孩子还是右孩子
 * tag=0,左孩子; tag=1,右孩子
 */
void bt_setchild(btree_node_t **parent,void *item,int tag);


/**************************Traversal**********************************/
/**
 * 下面提供5种遍历方法: 前序遍历、中序遍历、后序遍历、层次序遍历、Morris遍历
 * 对应了10个实现函数，其中带后缀rec表示用递归的方法实现，iter表示用迭代(栈)的方法实现
 * cb : 表示为一个以二叉树结点为参数的函数指针类型
 */

/*先序遍历，递归*/
void bt_preorder(btree_t *t, cb visit);
void bt_preorder_rec(btree_node_t *cur, cb visit);

/*中序遍历，递归*/
void bt_inorder(btree_t *t, cb visit);
void bt_inorder_rec(btree_node_t *cur, cb visit);

/*后序遍历，递归*/
void bt_postorder(btree_t *t, cb visit);
void bt_postorder_rec(btree_node_t *cur, cb visit);

/*先序遍历，栈*/
void bt_preorder_iter(btree_t *t, cb visit);

/*中序遍历，栈*/
void bt_inorder_iter(btree_t *t, cb visit);

/*后序遍历，栈*/
void bt_postorder_iter(btree_t *t, cb visit);

/*层次序遍历，栈*/
void bt_levelorder(btree_t *t,cb visit);

/*Morris先序遍历*/
void bt_morris_preorder(btree_t *t, cb visit);

/*Morris中序遍历*/
void bt_morris_inorder(btree_t *t, cb visit);

/*Morris后序遍历*/
void bt_morris_postorder(btree_t *t, cb visit);



#endif