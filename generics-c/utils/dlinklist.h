#ifndef _DLINKLIST_H_
#define _DLINKLIST_H_

/*双向循环链表的结点定义*/
typedef struct dlist_node {
	void *item;
	struct dlist_node *prev;
	struct dlist_node *next;
} dlist_node_t;

/*双向循环链表的结构定义*/
typedef struct {
	dlist_node_t *tail;
	int n;
	int (*comp)(const void *,const void *);
} dlist_t;

/*为双向循环链表分配内存*/
dlist_t *dlist_alloc(int (*comp)(const void *,const void *)); 

/*释放整个链表的内存*/
void dlist_free(dlist_t *l);

/*在双向循环链表中查找元素，如果存在，返回对应的值，否则返回NULL*/
void *dlist_find(dlist_t *l,void *item);

/*在双向循环链表尾部添加元素*/
void dlist_insert_end(dlist_t *l,void *item);

/*在双向循环链表某位置添加元素*/
void dlist_insert_middle(dlist_t *l,void *item,int pos);

/*在双向循环链表尾部删除元素,若存在，返回被删除的元素键值，否则返回NULL*/
void *dlist_delete_end(dlist_t *l);


/*在双向循环链表中找到第一个含item值的节点并删除此节点*/
void *dlist_delete_middle(dlist_t *l,void *item);



#endif