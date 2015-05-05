#include "hashtbl.h"
#include <stdio.h>
#include <stdlib.h>

hash_tbl_t *hashtbl_alloc(int num_buckets,
	                       int (*hash_fcn)(const void *,int),
	                       int (*comp_fcn)(const void *,const void *)){
	hash_tbl_t *tbl=malloc(sizeof(hash_tbl_t));
	tbl->num_buckets=num_buckets;
	tbl->num_elements=0;
	tbl->buckets=malloc(tbl->num_buckets* sizeof(hash_tbl_node_t *));
	tbl->hash_fcn=hash_fcn;
	tbl->comp_fcn=comp_fcn;
	return tbl;

}

void hashtbl_free(hash_tbl_t *tbl){
	int i,n;
	hash_tbl_node_t *cur,*tmp,**buckets;
	n=tbl->num_buckets;
	buckets=tbl->buckets;
	for(i=0;i<n;i++){
		if((cur=buckets[i])){ //如果某桶不为空，释放每个桶(链表)的内存
			while(cur){
				tmp=cur;
				cur=cur->next;
				free(tmp);
			}
		}
	}
	free(buckets);
	free(tbl);
}


/*******************辅助函数********************/
enum { num_primes = 33 };

static unsigned long prime_list[num_primes] =
{ 13ul,          17ul,         23ul,       37ul,        47ul,
  53ul,         97ul,         193ul,       389ul,       769ul,
  1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
  49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
  1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
  50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul, 
  1610612741ul, 3221225473ul, 4294967291ul
};

/*在有序数组中查找value应该插入的位置*/
int compute_lower_bound(unsigned long *arr,int size,unsigned long value){
	int low=0,high=size-1,mid;
	while(low<high){
		mid=low+((high-low)>>1);
		if(arr[mid] < value){ //中间元素小于目标值
			low=mid+1;
		} else {
			high=mid;
		}
	} //找到数组中大于或等于该值的目标位置即插入位置
	return low;
}

/*计算在这33个质数中最接近并大于等于value值的那个质数*/
unsigned long next_prime(unsigned long value){
	int pos=compute_lower_bound(prime_list,num_primes,value);
	return prime_list[pos];
}

hash_tbl_node_t *new_node(void *item,hash_tbl_node_t *next){
	hash_tbl_node_t *node=malloc(sizeof(hash_tbl_node_t));
	node->item=item;
	node->next=next;
	return node;
}


/*暂时不实现*/
//void resize(int new_size){}


/**
 * 插入元素项item
 * 如果在散列表中有元素项含有相同的键，可以选择返回当前那个元素项或者更新元素项的value值(更新item)
 * 否则没有相同的键则成功插入，返回NULL
 */
void *hashtbl_insert(hash_tbl_t *tbl,void *item){
	int (*comp)(const void *,const void *);
	comp=tbl->comp_fcn;
	int pos=tbl->hash_fcn(item,tbl->num_buckets);
	hash_tbl_node_t **buckets=tbl->buckets;

	hash_tbl_node_t *first,*tmp,*node;
	first=buckets[pos];
	if(first){ //需要判断在该桶链表中是否存在相同的键
		tmp=first;
		while(tmp){
			int res=comp(tmp->item,item);
			if(res==0)
				return tmp->item;
			tmp=tmp->next;
		}
		node=new_node(item,first);
	} else{
		node=new_node(item,NULL);
	}
	buckets[pos]=node;
	tbl->num_elements++;
	return NULL;
}

/*查找成功时返回该元素项否则返回NULL*/
void *hashtbl_find(hash_tbl_t *tbl,void *key_item){
	int (*comp)(const void *,const void *);
	comp=tbl->comp_fcn;
	int pos=tbl->hash_fcn(key_item,tbl->num_buckets);
	hash_tbl_node_t **buckets=tbl->buckets;
	hash_tbl_node_t *cur=buckets[pos];
	
	while(cur&&comp(cur->item,key_item)!=0)
		cur=cur->next;
	if(cur)
		return cur->item;
	else
		return NULL; //没有找到该元素或者该桶为空
}

/*删除和item具有相同键值的表项，成功删除时返回该表项否则没有表项被删除，返回NULL*/
void *hashtbl_delete(hash_tbl_t *tbl,void *item){
	int (*comp)(const void *,const void *);
	comp=tbl->comp_fcn;
	int pos=tbl->hash_fcn(item,tbl->num_buckets);
	hash_tbl_node_t **buckets=tbl->buckets;

	/*查找到具有相同键值的表项，再插入*/
	hash_tbl_node_t *cur=buckets[pos];
	hash_tbl_node_t *pre=NULL;//前驱指针
 	while(cur&&comp(cur->item,item)!=0){
 		pre=cur;
		cur=cur->next;
 	}

 	if(!cur)
 		return NULL; //不存在

 	if(pre){ //在中间找到某个匹配值
 		pre->next=cur->next;
	} else { //第一个节点匹配
		buckets[pos]=cur->next;
 	}

 	free(cur);
	tbl->num_elements--;
	return cur->item;
}

/*访问散列表的每个元素*/
void hashtbl_foreach(hash_tbl_t *tbl,cb visit){
	int i,n;
	hash_tbl_node_t *cur,**buckets;
	n=tbl->num_buckets;
	buckets=tbl->buckets;
	for(i=0;i<n;i++){
		cur=buckets[i];
		if(cur){ //如果某桶不为空，释放每个桶(链表)的内存
			printf("bucket %d: ",i);
			while(cur){
				visit(cur);
				cur=cur->next;
			}
			printf("\n");
		}
	}
}
