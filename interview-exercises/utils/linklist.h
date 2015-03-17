#ifndef _LINKLIST_H_
#define _LINKLIST_H_

typedef struct list_node {
	int data;
	struct list_node *next;
} list_node_t;

　typedef struct slist {
	list_node_t *head;
	//int size;
} slist_t;

typedef void (*cb)(list_node *cur);

/*设置虚拟头节点*/
list_node *init_slist(); 

/*分配一个新节点内存，默认可用new list_node()创建*/
list_node *new_node(int val, list_node *next); 

/*访问链表中的每个节点*/
void print_node(list_node *cur); 

/*访问整个链表*/
void print_list(slist_t *slist); 

/*释放整个链表的内存*/
void destroy_list(list_node *slist);
　







#endif