#include "linklist.h"
#include <stdio.h> //exit
#include <stdlib.h> //malloc
#include <time.h>

//set dummy header node to simplify
linknode* init_list() {
	linknode *list=(linknode*)malloc(sizeof(linknode));
	list->next=NULL;
	return list;
}

linknode* new_node(T val, linknode* next) {
	linknode *node=(linknode*)malloc(sizeof(linknode));
	if(node==NULL) {
		printf("Creating node failed...");
		exit(0);
	}
	node->next=next;
	node->data=val;
	return node;
}


void insert_at_begin(linknode *list,T val){
	linknode *cur=list->next;
	linknode *node;
	if(cur==NULL){
		node=new_node(val,NULL);
	} else {
		node=new_node(val,cur);
	}
	list->next=node;
}

int getsize(linknode *list){
	linknode *cur=list->next;
	int num=0;
	while(cur!=NULL){
		num++;
		cur=cur->next;
	}
	return num;
}

void insert_at_middle(linknode *list,T val, int pos){
	if(pos <0 || pos > getsize(list)) { // the kth postion 0<=pos<=len(list)
		printf("Invalid position ! \n");
		return;
	}
	linknode *cur=list;
	linknode *node;
	while(cur->next!=NULL && pos){
		cur=cur->next;
		pos--;
	}
	if(cur !=NULL) { //insert after the current node
		node=new_node(val,cur->next);
		cur->next=node;
	}
	
}

void insert_at_end(linknode *list, T val){
	linknode *node=new_node(val,NULL); 
	linknode *cur=list;
	while(cur->next!=NULL)
		cur=cur->next;
	cur->next=node;
}

void append(linknode* list,T val) {
	insert_at_end(list,val);
}


void create_random_list(linknode *list,unsigned int size) {
	srand(time(NULL));
	unsigned int i=0;
	for(;i<size ;i++) {
		append(list,rand()%10);
	}
}

linknode *find(linknode *list, int pos){ //1<=pos<=len(list)
	linknode *cur=list->next;
	if(pos <1 || pos >getsize(list)) return NULL;
	int len=pos-1; 
	while(cur && len){
		cur=cur->next;
		len--;
	}
	return cur;
} 

linknode *find_last_kth(linknode* list, int k) { //1<=k<=len(list)
	if(list->next ==NULL || k <=0 || k >getsize(list)) 
		return NULL;
	linknode *first=list->next;
	linknode *second=list->next;
	int count=0;
	while(first){
		if(count < k)
			count++; //only move p
		else
			second=second->next; //move p,q together
		first=first->next;
	} //the terminate condition is first=NULL,second moves to the the last-kth node
    return second;
}

T delete_from_begin(linknode *list) {
	linknode *cur=list->next;
	if(cur !=NULL) {
		T data=cur->data;
		list->next=cur->next;
		free(cur);
		return data;
	} else {
		return -1;
	}
}



T delete_from_middle(linknode *list, int pos) {
	if(pos <=0 || pos >getsize(list)) {  //1<=pos<=len(list)
		printf("Invalid position ! \n");
		return -1;
	}
	// if(pos==1)
	// 	return delete_from_begin(list);
	// else {
	// 	/*method 1*/
	// 	linknode *prev=find(list,pos-1); //find the previous node of the deleted node
	// 	linknode *cur=prev->next;
	// 	T data=cur->data;
	// 	prev->next=cur->next;
	// 	free(cur);
	// 	return data;
	// }

	/*method 2*/
		linknode *cur=list;
		linknode *prev=NULL;
		while(cur->next!=NULL && pos){
			prev=cur;
			cur=cur->next;
			pos--;
		}
		T data=cur->data;
		prev->next=cur->next;
		free(cur);
		return data;
}


T delete_from_end(linknode *list) { //use two working pointers 
	linknode *cur=list;;
	linknode *prev=NULL; 
	while(cur->next!=NULL){
		prev=cur;
		cur=cur->next;
	}
	if(prev !=NULL)
		prev->next=NULL;
	T data=cur->data;
	free(cur);
	return data;
}

void visit(linknode *node) {
	if(node!=NULL)
		printf(" %d-> ",node->data);
}

void display(linknode *list,callback f) {
	if(list!=NULL) {
		linknode *cur=list->next;
		while(cur!=NULL) {
			f(cur);
			cur=cur->next;
		}
		printf("\n");
	}
}

void destroy_list(linknode *list){
	linknode *cur=list;
	linknode *tmp=NULL;
	if(list !=NULL){
		cur=list->next;
		list->next=NULL;
		while(cur!=NULL){
			tmp=cur->next;
			free(cur);
			cur=tmp;
		}
	}
}

void reverse(linknode *list){
	/*method 1*/
	// linknode *cur=list->next;
	// linknode *r=cur->next;
	// linknode *pre=NULL;
	// cur->next=NULL; //the first node's next field is NULL
	// while(r!=NULL){
	// 	pre=cur;
	// 	cur=r; //deal with the current node
	// 	r=r->next;
	// 	cur->next=pre; //reverse the pointer
	// }
	// list->next=cur; //deal with the last node

	/*method 2*/
	linknode *cur=list->next;
	list->next=NULL;
	linknode *pre=NULL;
	while(cur !=NULL){
		pre=cur->next;
		cur->next=list->next;  // important, insert the first node
		list->next=cur; 
		cur=pre;
	}
}

void insertion_sort(linknode *list) {
/** if it doesn't have dummy header node,it will be complicated ,because we have to
*   discuss the condition when the current element's value is less than the first node,we have to modify the head node
*   Because we define dummy header ,we didn't care the first node's value
*/
	linknode *cur=list->next;
	list->next=NULL;
	linknode *r=NULL,*prev=NULL;
	while(cur !=NULL) { 
		r=cur->next;
		prev=list; 
		while(prev->next && cur->data > prev->next->data) prev=prev->next; //the first node will insert directly 
		cur->next=prev->next; //find the first node next's vaule is bigger than current'data, insert after the prev node
		prev->next=cur;
		cur=r;
	}
}

