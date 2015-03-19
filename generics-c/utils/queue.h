#ifndef _QUEUE_H_
#define _QUEUE_H_

/*基于动态数组的队列结构定义*/
typedef struct {
	void *item;
	int capacity;
	int top;
	int type_size;
} queue_t;

/*为队列分配一定容量的内存*/
queue_t *queue_alloc(int capacity,int type_size);
queue_t *queue_alloc_default(int type_size);

/*释放队列内存*/
void queue_free(queue_t *st);

/*入队: 若队列没有多余的空间，数组容量加倍*/
void enqueue(queue_t *st,void *item);

/*出队: 出队列后如果数组太大，将长度减半*/
void *dequeue(queue_t *st);

/*读取队列顶部元素*/
void *queue_top(queue_t *st);

#endif