#ifndef _DLINKLIST_H_
#define _DLINKLIST_H_

#include <stdlib.h>

/*双向循环链表的结点定义*/
typedef struct dlist_node {
	void *item;
	struct dlist_node *prev;
	struct dlist_node *next;
} dlist_node_t;

/*双向循环链表的结构定义*/
typedef struct {
	dlist_node_t *head;
	int n;
	int (*comp)(const void *,const void *);
} dlist_t;


/*为双向循环链表分配内存*/
dlist_t *dlist_alloc(int (*comp)(const void *,const void *)); 

/*释放整个链表的内存*/
void dlist_free(dlist_t *l);

/*双链表的大小*/
int dlist_size(dlist_t *l);

/*遍历访问链表中的每个元素*/
void dlist_foreach(dlist_t *l,void (*visit)(dlist_node_t *));

/*在双向循环链表中查找元素，如果存在，返回对应的值，否则返回NULL*/
dlist_node_t *dlist_find(dlist_t *l,void *item);

/*在双向循环链表某位置添加元素*/
void dlist_insert(dlist_t *l,void *item,int pos);

/*在双向循环链表尾部添加元素*/
void dlist_push_back(dlist_t *l,void *item);

/*在双向链表头部添加元素*/
void dlist_push_front(dlist_t *l,void *item);

/*在双向循环链表中删除pos位置节点并输出当前值*/
void *dlist_delete(dlist_t *l,int pos);

/*在双向循环链表尾部删除元素,若存在，返回被删除的元素键值，否则返回NULL*/
void *dlist_pop_back(dlist_t *l);

/*在双向循环链表头部删除元素，若存在返回被删除的元素键值，否则返回NULL*/
void *dlist_pop_front(dlist_t *l);

/*创建一个元素节点，让头尾都指向自己并设元素值*/
static inline dlist_node_t *new_dlist_node(void *item){
	dlist_node_t *node=malloc(sizeof(dlist_node_t));
	node->prev=node->next=node;
	node->item=item;
	return node;
}



#endif