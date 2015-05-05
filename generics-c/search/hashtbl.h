#ifndef _HASH_TBL_H_
#define _HASH_TBL_H_

/*散列表结点元素的定义*/
typedef struct hash_tbl_node {
	void *item;
	struct hash_tbl_node *next;
} hash_tbl_node_t;

/**
 * num_elements: 散列表中元素(结点)的个数(用于动态调整表格大小，重建表格而用)
 * buckets_num: 散列表的表格大小(表中的每个元素项称为桶),在STL中以质数来设计表格大小
 * STL中甚至提供一个函数，用于查询在这28个作为表格大小的质数中，最接近某数并大于某数的质数
 * buckets: 由指向链表的结点指针构成的数组
 * hash_fcn: 针对元素表项键值的散列函数指针
 * comp_fcn: 比较元素表项大小的函数指针
 */
typedef struct {
	int num_buckets;
	int num_elements;
	hash_tbl_node_t **buckets;
	int (*hash_fcn)(const void *,int);
	int (*comp_fcn)(const void *,const void *);
} hash_tbl_t;

typedef void (*cb)(hash_tbl_node_t *);


hash_tbl_t *hashtbl_alloc(int num_buckets,
	                       int (*hash_fcn)(const void *,int),
	                       int (*comp_fcn)(const void *,const void *));

void hashtbl_free(hash_tbl_t *tbl);

/**
 * 插入元素项item
 * 如果在散列表中有元素项含有相同的键，可以选择返回当前那个元素项或者更新元素项的value值(更新item)
 * 否则没有相同的键则成功插入，返回NULL
 */
void *hashtbl_insert(hash_tbl_t *tbl,void *item);

/*查找成功时返回该元素项否则返回NULL*/
void *hashtbl_find(hash_tbl_t *tbl,void *key_item);

/*删除和item具有相同键值的表项，成功删除时返回该表项否则没有表项被删除，返回NULL*/
void *hashtbl_delete(hash_tbl_t *tbl,void *item);

/*访问散列表的每个元素*/
void hashtbl_foreach(hash_tbl_t *tbl,cb visit);

#endif