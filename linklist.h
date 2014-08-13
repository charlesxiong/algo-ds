#ifndef _LINKLIST_H_
#define _LINKLIST_H_
/* C Linkedlist :
*
*  This is about how to implement commonly used linkedlist operations
*   such as prepend,append,insert,delete,traverse,count,reverse,sort,etc.
*  
*/
typedef int T;
typedef struct linknode {
	T data;
	struct linknode *next;
} linknode;
typedef void (*callback)(linknode *node);


linknode* init_list();
linknode* new_node(T val,linknode* next);

linknode* find(linknode *list, int pos);
linknode* find_last_kth(linknode* list,int k);


void append(linknode *list,T val);
void insert_at_begin(linknode *list,T val);
void insert_at_middle(linknode *list, T val ,int pos);
void insert_at_end(linknode *list, T val);


T delete_from_begin(linknode *list);
T delete_from_middle(linknode *list, int pos);
T delete_from_end(linknode *list);

int getsize(linknode *list);

void create_random_list(linknode *list,unsigned int size);
void destroy_list(linknode *list);

void visit(linknode* node);
void display(linknode* list,callback f);

void reverse(linknode *list);
void insertion_sort(linknode *list);



#endif
