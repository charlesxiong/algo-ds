#include "genarraylist.h"

array_t *array_create(int capacity,int sz){
	array_t *arr=array_init(capacity);
	arr->type_sz=sz;
	arr->data=malloc(arr->type_sz*arr->size);
	if(NULL==arr->data) {
		printf("Allocating data failed...");
		return NULL;
	}
	return arr;
}

array_t *array_create_default(int sz){
	return array_create(DEFAULT_SZ,sz);
}

void array_push(array_t *arr, void *elt) {
	if(arr->index==arr->size) { //increasing to 2*size
		/*method 1: manually copy data */
		int size=arr->size*2;
		void *new_data=malloc(arr->type_sz*size);
		if(NULL==new_data) {
			printf("Memory allocation error...");
			return ;
	    }
	    printf("Allocating success...\n");
	    // T *src=arr->data;
	    // T *dest=new_data;
	    // int n=arr->size;
	    // while(n--){
	    // 	*dest++=*src++;
	    // }
	    // free(arr->data);
	    // arr->data=new_data;
	    // arr->size=size;


	    /*method 2: using realloc*/
	    // arr->size *=2;
	    // arr->data=realloc(arr->data,sizeof(int)*arr->size);
	    
	    /*method 3: implement my realloc function*/

	    void *src,*dst;
	    int i;
	    for(i=0;i<arr->size;i++) {
	    	src=(char *)arr->data+i*arr->type_sz;
	    	dst=(char *)new_data+i*arr->type_sz;
	    	assign(src,dst,arr->type_sz);
	    }
	    free(arr->data);
	    arr->data=new_data;
	    arr->size=size;
	    
	}
	//arr->data[arr->index]=elt;
	void *new_elt=(char *)arr->data+arr->index*arr->type_sz;
	assign(elt,new_elt,arr->type_sz);
	arr->index++;
}

int array_isempty(array_t *arr){
	return (arr->size==0)?1:0;
}

void array_clear(array_t *arr){
	// while(--arr->index){
	// 	arr->data[arr->index]=0;
	// }
	// arr->size=0;
}

void *array_pop(array_t *arr) {
	void *elt=(char *)arr->data+(--arr->index)*arr->type_sz;
	return elt;
}

void array_set(array_t *arr,void *elt,int pos){
	if(pos<0 || pos >=arr->index ) {
		printf("Invalid position");
		return;
	}
	//arr->data[pos]=elt;
	void *new_elt=(char *)arr->data+pos*arr->type_sz;
	assign(elt,new_elt,arr->type_sz);
}

void *array_get(array_t *arr,int pos){
	if(pos<0 || pos >=arr->index ) {
		printf("Invalid position");
		exit(1);
	}
	//return arr->data[pos];
	void *elt=(char *)arr->data+pos*arr->type_sz;
	return elt;
}




