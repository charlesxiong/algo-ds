#ifndef _LINKLIST_H_
#define _LINKLIST_H_

typedef struct list_node {
	void *item;
	struct list_node *next;
} list_node_t;

typedef struct slist {
	list_node_t *head;
	int n;
	int (*comp)(const void *,const void *);
} slist_t;


/*为单链表分配内存*/
slist_t *slist_alloc(int (*comp)(const void *,const void *)); 

/*释放整个链表的内存*/
void slist_free(slist_t *l);

/*在单链表中查找元素，如果存在，返回对应的值，否则返回NULL*/
void *slist_find(slist_t *l,void *item);

/*在单链表尾部添加元素*/
void slist_insert_end(slist_t *l,void *item);

/*在单链表头部添加元素*/
void slist_insert_begin(slist_t *l,void *item);

/*在单链表某位置pos添加元素*/
void slist_insert_middle(slist_t *l,void *item,int pos);

/*在单链表尾部删除元素,若存在，返回被删除的元素键值，否则返回NULL*/
void *slist_delete_end(slist_t *l);

/*在单链表头部删除元素，若存在返回被删除的元素键值，否则返回NULL*/
void *slist_delete_begin(slist_t *l);

/*在单链表中找到第一个含item值的节点并删除此节点*/
void *slist_delete_middle(slist_t *l,void *item);


static inline list_node_t *new_list_node(void *item){
	list_node_t *node=malloc(sizeof(list_node_t));
	node->next=NULL;
	node->item=item;
	return node;
} 

#endif