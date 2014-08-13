#include "arraylist.h"



int main(){
    array_t *t=array_create(2);
    array_push(t,1);
    array_push(t,2);
    array_push(t,3);
    //printf("%d\n",array_isempty(t));
	array_for_each(t);
	array_push(t,230);
	array_push(t,-1);
	array_for_each(t);
	array_sort(t);
	array_for_each(t);
	array_pop(t);
	array_push(t,7887);
	array_sort(t);
	array_for_each(t);
	// array_clear(t);
	// printf("%d\n",array_isempty(t));

	


	
	return 0;
}