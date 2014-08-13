#include "linklist.h"
#include <stdio.h>

void test1(){
	linknode* list=init_list();
	create_random_list(list,10);
	display(list,visit);
}

void test2(){
	linknode* list=init_list();
	insert_at_begin(list,35);
	printf("%d\n",getsize(list));
	display(list,visit);

	insert_at_end(list,24);
	insert_at_begin(list,12);
	printf("%d\n",getsize(list));
	display(list,visit);

	insert_at_middle(list,0,3);//select pos 0..3
	display(list,visit);
	
	//printf("%d \n",delete_from_begin(list));
	//printf("%d \n",delete_from_middle(list,1));
	// printf("%d \n",delete_from_end(list));
	// destroy_list(list);
	// printf("%d\n",getsize(list));

	//reverse(list);
	

    insert_at_begin(list,5);
    insert_at_begin(list,2);
    display(list,visit);
    insertion_sort(list);
    display(list,visit);


	// callback f=visit;
	// f(find_last_kth(list,5));
	// printf("\n");
	// f(find_last_kth(list,0));
	// printf("\n");
	// f(find_last_kth(list,1));
	// printf("\n");
	// f(find_last_kth(list,4));
	// printf("\n");
	// f(find_last_kth(list,2));
	// printf("\n");




}

int main() {
	test2();
	return 0;
}