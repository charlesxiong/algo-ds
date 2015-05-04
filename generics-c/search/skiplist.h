#ifndef _SKIP_LIST_H_
#define _SKIP_LIST_H_


/**
 * 跳跃链表节点的结构定义
 * 为了灵活性，节点指向某个含有键值对的表项而非整数键
 * item： 节点的数据项
 * forward: 长度为1的柔性数组，每个节点对应的forward长度可以不同
 * 柔性的边长数组可以节省空间
 */
typedef struct skiplist_node {
	void *item;
	struct skiplist_node *forward[1];
} skiplist_node_t;

/**
 * 跳跃链表的数据结构定义
 * head: 为了插入和删除的方便，定义一个虚拟头结点
 * update数组: 用于在插入、删除、查找操作中更新每个层级被查找节点的前驱指针
 * 在跳表初始化时就被创建，它防止了每次在进行插入等操作时需要分配和释放该数组的内存
 * prob: 某节点被创建时出现在某个层次概率
 * 它的概率分布类似于丢硬币实验，连续i次出现同种情形(如正面)对应i的次数的分布
 * 很显然它满足参数为p的集合分布，期望值为1/p
 * 根据William Pugh的分析,我们理想中开始查找的层次为L(N)=log(N)/log(1/p)
 * 只要保证我们生成的层次的最大值max_level为L(N),N为跳表中元素个数的上界
 * 例如p=1/2,处理至多含有2^16个数据的跳表的最大的合适层级是16
 * level: 跳表当前的最大层次
 * comp: 比较跳表中表项大小的函数
 * n: 当前存储在跳表中的元素个数
 */
typedef struct {
	skiplist_node_t *head;
	skiplist_node_t **update;
	double prob;
	int max_level;
	int level;
	int (*comp)(const void *,const void *);
	int n;
} skiplist_t;


typedef void (*cb)(skiplist_node_t *);

/**
 * 分配一个跳表的内存并返回它的指针
 * capactity: 可存储在跳表中的最大期望容量
 * prob: 随机生成节点层次的概率
 * comp: 元素大小的比较函数
 */
skiplist_t *skiplist_alloc(int capacity,double prob,int (*comp)(const void *,const void *));


void skiplist_free(skiplist_t *l);

/*要求跳表中的元素的键值必须唯一，如果键值已经在链表中，返回当前项即可否则返回NULL,表示插入成功*/
void *skiplist_insert(skiplist_t *l,void *item);

void *skiplist_find(skiplist_t *l,void *key_item);

void *skiplist_find_min(skiplist_t *l);

/*删除在跳表中第一个找到的item表项，找到了返回当前表项的指针否则返回NULL*/
void *skiplist_delete(skiplist_t *l,void *item);

/*从跳表中删除具有最小键值的表项*/
void *skiplist_delete_min(skiplist_t *l);

void skiplist_foreach(skiplist_t *l,cb visit);



#endif