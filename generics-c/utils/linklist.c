#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

/**
 * linklist.c - Linked List Implementation
 *
 */

/*为单链表分配内存*/
slist_t *slist_alloc(int (*comp)(const void *,const void *)){
	slist_t *l=malloc(sizeof(slist_t));
	l->head=NULL;
	l->n=0;
	l->comp=comp;
	return l;
}

/*释放整个链表的内存*/
void slist_free(slist_t *l){
	list_node_t *cur,*tmp;
	if(l->head){ //头节点不为空
		cur=l->head;
		while(cur){
			tmp=cur->next;
			free(cur);
			cur=tmp;
		}
	}
	free(l);
}

/*在单链表中查找元素，如果存在，返回对应的值，否则返回NULL*/
void *slist_find(slist_t *l,void *item) {
	list_node_t *cur;
	int (*comp)(const void *,const void *);
	comp=l->comp;
	cur=l->head;
	while(cur){
		int cmp_res=comp(item,cur->item);
		if(cmp_res == 0) 
			return cur->item;
		else
			cur= cur->next;
	} 
	return NULL; //没找到或者头结点为空均返回空

}

/*在单链表尾部添加元素*/
void slist_insert_end(slist_t *l,void *item) {
	/*构造新结点*/
	list_node_t *node=new_list_node(item);

	if(l->head){
		list_node_t *cur=l->head;
		while(cur->next){
			cur=cur->next;
		}
		cur->next=node;
	} else {
		l->head=node;
	}
	l->n++; 
}

/*在单链表头部添加元素*/
void slist_insert_begin(slist_t *l,void *item) {
	list_node_t *node=new_list_node(item);
	node->next=l->head;
	l->head=node; //无需区分头结点是否为空，情形一样
	l->n++;
}

/*在单链表尾部删除元素,若存在，返回被删除的元素键值，否则返回NULL*/
void *slist_delete_end(slist_t *l) {
	list_node_t *cur,*prev;
	if(l->head){
		void *res_item;
		if(l->head->next){ //不止一个结点
			prev=l->head;
			cur=l->head->next;
			while(cur->next){ 
				prev=cur;
				cur=cur->next;
			}
			prev->next=NULL;
		} else { //只有一个节点
			cur=l->head;
			l->head=NULL;
		}
		res_item=cur->item;
		free(cur);
		l->n--;

		return res_item;
	} else { //空链表，返回NULL
		return NULL;
	}
}

/*在单链表头部删除元素，若存在返回被删除的元素键值，否则返回NULL*/
void *slist_delete_begin(slist_t *l) {
	list_node_t *cur;
	if(l->head){
		cur=l->head;
		l->head=l->head->next;

		void *res_item=cur->item;
		free(cur);
		l->n--;
		return res_item;
	} else {
		return NULL;
	}
}

/*在单链表中找到第一个含item值的节点并删除此节点*/
void *slist_delete_middle(slist_t *l,void *item) {
	list_node_t *cur,*prev;
	int (*comp)(const void *,const void *);
	comp=l->comp;
	if(l->head) {
		prev=NULL;
		cur=l->head;
		while(cur){
			int cmp_res=comp(item,cur->item);
			if(cmp_res==0){
				break;
			} else {
				prev=cur;
				cur=cur->next;
			}
		}
		if(cur==NULL){ //该键值不存在
			return NULL;
		} else {
			if(prev==NULL)
				return slist_delete_begin(l);
			else {
				prev->next=cur->next;
				void *res_item=cur->item;
				free(cur);
				l->n--;
				return res_item;
			}
		}
	} else {
		return NULL;
	}
}








