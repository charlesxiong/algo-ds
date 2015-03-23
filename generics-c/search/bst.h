#ifndef _BST_H_
#define _BST_H_

/*二叉查找树的结点定义*/
typedef struct bst_node {
	void *item;
	struct bst_node *left;
	struct bst_node *right;
} bst_node_t;



/*二叉查找树的结构定义*/
typedef struct bst {
	bst_node_t *root;
	int n;
	int (*comp)(const void *,const void *);
} bst_t;

/*为二叉查找树分配内存，comp是一个比较两元素大小的函数指针*/
bst_t *bst_alloc(int (*comp)(const void *,const void *));

/*释放二叉查找树的内存*/
void bst_free(bst_t *t);


/**
 * bst_insert(): 要求插入的元素项的键不能和树中元素键相同，键独一无二
 *　思路: 首先检查该元素是否已经存在，若查找成功，直接返回该位置
 * 否则查找不成功，把新元素插入到查找停止的地方
 */
void *bst_insert(bst_t *t,void *item);

/**
 * bst_find():  查找树中的某个关键字
 *　思路: 先与根结点比较，若相同则查找结束
 *　否则根据比较结果，沿着左子树或右子树向下继续查找
 * 如果没有找到，返回NULL
 */
void *bst_find(bst_t *t,void *item);


/*返回二叉查找树中的含最小键值的结点*/
void *bst_find_min(bst_t *t);


/**
 * bst_delete : 删除树中的某个结点，还必须保证BST树的排序不会丢失
 * 思路: (1) 被删除结点是叶结点，直接删除，不会影响BST的性质
 * (2) 若结点z只有一颗左子树或者右子树，让z的子树成为z父结点的子树，替代z位置
 * (3) 若结点有两个子树，令它的直接后继(直接前驱)替代z,
 *  再从BST树中删除该直接后继(直接前驱)，这样转换成了前两个情况
 */
void *bst_delete(bst_t *t,void *item);


/*删除BST树中最小的键值结点*/
void *bst_delete_min(bst_t *t);


#endif