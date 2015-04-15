#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>

#define DEFAULT_CAPACITY 16

/**
 * 循环队列结构定义
 * 如果是固定长度的循环数组，一般建议牺牲一个单元来区分队空和队满
 * 入队时少一个单元，因而一般设定front指向队头的上一个元素，
 * rear指向队尾元素
 */
typedef struct {
	void *data;
	int capacity;
	int front; //指向队头元素的上一个元素
	int rear; //指向队尾元素
	int type_size;
} queue_t;


/*为队列分配一定容量的内存*/
queue_t *queue_alloc(int capacity,int type_size);
queue_t *queue_alloc_default(int type_size);

/*释放队列内存*/
void queue_free(queue_t *qt);

int queue_size(queue_t *qt);
bool queue_empty(queue_t *qt);
bool queue_full(queue_t *qt);

/*入队*/
void enqueue(queue_t *qt,void *elt);

/*出队*/
void *dequeue(queue_t *qt);

/*读取队列顶部元素*/
void *queue_peek(queue_t *qt);

#endif