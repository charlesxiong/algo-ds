#ifndef _UF_H_
#define _UF_H_

/*
 * 并查集数据结构,可以采用两种方式:
 * 直接通过树链接的方式表示
 * 使用树的双亲表示法: 结点下标从0开始，根结点的伪指针域为-1, 除了根结点外所有结点都有一个唯一双亲
 * 最后计算不相交的集合分量只需统计数组中负数的个数，大于或等于0的结点均表示对应结点的唯一双亲
 */
typedef struct {
	int *id;
	int count;  //不相交集合的个数
} uf_t;

/*分配并查集的内存并初始化*/
uf_t *uf_alloc(int n);

/*释放并查集内存*/
void uf_free(uf_t *t);

/*查找包含元素p的树的根－集合标号，带路径压缩*/
int uf_find(uf_t *t,int p);

/*合并包含两元素p和q的树集合*/
void uf_union(uf_t *t,int p,int q);

/*返回并查集中不相交集合的分量个数*/
int uf_count(uf_t *t);

/*返回并查集中包含p元素的集合大小*/
int uf_set_size(uf_t *t,int p);


#endif