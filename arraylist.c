#include "arraylist.h"


array_t *array_create(int capacity){
	array_t *arr=array_init(capacity);
	arr->data=malloc(sizeof(T)*arr->size);
	if(NULL==arr->data) {
		printf("Allocating data failed...");
		return NULL;
	}
	return arr;
}

array_t *array_create_default(){
	return array_create(DEFAULT_SZ);
}

void array_push(array_t *arr, T elt) {
	if(arr->index==arr->size) { //increasing to 2*size
		/*method 1: manually copy data */
		int size=arr->size*2;
		T *new_data=(T *)malloc(sizeof(T)*size);
		if(NULL==new_data) {
			printf("Memory allocation error...");
			return ;
	    }
	    printf("Allocating success...\n");
	    T *src=arr->data;
	    T *dest=new_data;
	    int n=arr->size;
	    while(n--){
	    	*dest++=*src++;
	    }
	    free(arr->data);
	    arr->data=new_data;
	    arr->size=size;


	    /*method 2: using realloc*/
	    // arr->size *=2;
	    // arr->data=realloc(arr->data,sizeof(int)*arr->size);
	    
	    /*method 3: implement my realloc function*/
	    
	}
	arr->data[arr->index]=elt;
	arr->index++;
}

int array_isempty(array_t *arr){
	return (arr->size==0)?TRUE:FALSE;
}

void array_clear(array_t *arr){
	while(--arr->index){
		arr->data[arr->index]=0;
	}
	arr->size=0;
}

T array_pop(array_t *arr) {
	int elt=arr->data[--arr->index];
	return elt;
}

void array_set(array_t *arr,T elt,int pos){
	if(pos<0 || pos >=arr->index ) {
		printf("Invalid position");
		return;
	}
	arr->data[pos]=elt;
}

T array_get(array_t *arr,int pos){
	if(pos<0 || pos >=arr->index ) {
		printf("Invalid position");
		exit(1);
	}
	return arr->data[pos];
}


void array_for_each(array_t *arr){
	int i;
	for(i=0;i< arr->index;i++)
		printf("%d ",arr->data[i]);
	printf("\n");
}



void array_sort(array_t *arr) {
	array_qsort(arr,0,arr->index-1,numcmp);
}