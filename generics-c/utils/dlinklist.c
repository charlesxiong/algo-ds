#include "dlinklist.h"
#include <stdio.h>


/**
 * 为双向循环链表分配内存，
 * 两种思路:
 * 不带头节点，通过判断l->head是否为NULL来删除链表
 * 带头节点，只需判断cur=l->head->next与l->head的是否相等(l->head==l->head->next才为链表空)
 *
 * 单链表实现中使用了不带头节点的办法(注释说明的头结点只是链表头指针)，双向链表我使用带头节点的思路
 * 也是为了比较这两种方法哪个适合简化插入和删除操作
 */
dlist_t *dlist_alloc(int (*comp)(const void *,const void *)){
	dlist_t *l=malloc(sizeof(dlist_t));
	l->head=new_dlist_node(NULL); 
	l->n=0;
	l->comp=comp;
	return l;
}

/*释放整个链表的内存*/
void dlist_free(dlist_t *l){
	dlist_node_t *cur,*tmp;
	cur=l->head->next;
	while(cur!=l->head){
		tmp=cur;
		cur=cur->next;
		free(tmp);
	}
	free(l->head); //务必释放头节点内存
	free(l);
}


int dlist_size(dlist_t *l){
	return l->n;
}

/*遍历访问链表中的每个元素*/
void dlist_foreach(dlist_t *l,void (*visit)(dlist_node_t *)){
	dlist_node_t *cur=l->head->next;
	while(cur!=l->head){
		visit(cur);
		cur=cur->next;
	}
}

/*在双向循环链表中查找元素，如果存在，返回对应的节点，否则返回NULL*/
dlist_node_t *dlist_find(dlist_t *l,void *item){
	dlist_node_t *cur=l->head->next;
	int (*comp)(const void *,const void *);
	comp=l->comp;
	while(cur!=l->head){ //一定要记住判空标志为cur==l->head
		int cmp_res=comp(item,cur->item);
		if(cmp_res==0)
			return cur;
		cur=cur->next;
	}
	return NULL;
}

/*查找双链表第pos个位置的节点，pos从0开始*/
dlist_node_t *dlist_find_pos(dlist_t *l,int pos){
	if(pos<0 ||pos>l->n){
		printf("Invalid position to find!\n");
		return NULL; 
	} 

	if(pos==0){
		return l->head; //头部插入，关键点，使得所有插入统一化了
	}

	dlist_node_t *cur=l->head->next;
	int j=1;//计数从1开始表示
	while(cur!=l->head){ //链表为空的标志
		if(j==pos){
			break;
		}
		cur=cur->next;
		j++;
	}
	return cur;
}

/**
 * 在双向循环链表某位置添加元素，可插入的pos范围: 0-l->n
 * pos为0时表示头部插入，pos为l->n时表示尾部插入
 * 
 * tmp要插在cur后,要么两节点前驱后后继同时链上，要么先链一个方向再链另外一个方向
 * 技巧就在于基于位置查找的函数当pos==0时返回头指针，使得插入任何位置都使用统一的代码
 **/
void dlist_insert(dlist_t *l,void *item,int pos){
	if(pos<0|| pos>l->n){
		printf("Invalid position");
		return;
	}
	dlist_node_t *cur=dlist_find_pos(l,pos);//定位到pos位置的节点
	dlist_node_t *tmp=new_dlist_node(item); ;//插入到pos位置的新节点
	tmp->next=cur->next;
	cur->next->prev=tmp;
	tmp->prev=cur;
	cur->next=tmp;
	l->n++;
}

/*在双向循环链表尾部添加元素*/
void dlist_push_back(dlist_t *l,void *item){
	dlist_insert(l,item,l->n);
}

/*在双向链表头部添加元素*/
void dlist_push_front(dlist_t *l,void *item){
	dlist_insert(l,item,0);
}

/*在双向循环链表中删除pos位置节点并输出当前值，pos从1到l->n*/
void *dlist_delete(dlist_t *l,int pos){
	if(pos<1|| pos>l->n){
		printf("Invalid position");
		return NULL;
	}
	dlist_node_t *cur=dlist_find_pos(l,pos-1);//找到删除位置的前驱节点
	dlist_node_t *tmp=cur->next; //被删除位置的节点

	cur->next=tmp->next;
	tmp->next->prev=cur;
	void *res_item=tmp->item;
	free(tmp);
	l->n--;
	return res_item;
}

/*在双向循环链表尾部删除元素,若存在，返回被删除的元素键值，否则返回NULL*/
void *dlist_pop_back(dlist_t *l){
	return dlist_delete(l,l->n);
}

/*在双向循环链表头部删除元素，若存在返回被删除的元素键值，否则返回NULL*/
void *dlist_pop_front(dlist_t *l){
	return dlist_delete(l,1);
}



