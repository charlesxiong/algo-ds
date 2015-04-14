#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*为队列分配一定容量的内存*/
queue_t *queue_alloc(int capacity,int type_size){
	queue_t *qt=malloc(sizeof(queue_t));
	qt->data=malloc(capacity*type_size);
	qt->capacity=capacity;
	qt->front=0; //队头元素的上一个元素
	qt->rear=0; //队尾元素
	qt->type_size=type_size;
	return qt;
}

queue_t *queue_alloc_default(int type_size){
	return queue_alloc(DEFAULT_CAPACITY,type_size);
}

/*释放队列内存*/
void queue_free(queue_t *qt){
	free(qt->data);
	free(qt);
}

int queue_size(queue_t *qt){
	return (qt->rear+qt->capacity-qt->front)%(qt->capacity);
}
int queue_empty(queue_t *qt){
	return (qt->front==qt->rear)?1:0;
}

int queue_full(queue_t *qt){
	return ((qt->rear+1)%(qt->capacity)==qt->front)?1:0;
}

/****************辅助函数**********************/
/*使用字节流从src复制size个字节到dst位置上*/
void copy(void *dst,void *src,int size){
	char *buf=malloc(size);
	memcpy(buf,src,size);
	memcpy(dst,buf,size);
	free(buf);
}

/*使用字节流交换v1和v2的size个字节大小*/
void swap(void *v1,void *v2,int size){
	char *buf=malloc(size);
	memcpy(buf,v1,size);
	memcpy(v1,v2,size);
	memcpy(v2,buf,size);
	free(buf);
}

/*入队*/
void enqueue(queue_t *qt,void *elt){
	if(queue_full(qt)){
		printf("Queue is full\n");
		return ;
	}
	qt->rear=(qt->rear+1)%(qt->capacity);
	void *elt_pos=(char *)qt->data+ qt->rear * qt->type_size;
	copy(elt_pos,elt,qt->type_size);
}

/*出队*/
void *dequeue(queue_t *qt){
	if(queue_empty(qt)){
		printf("Queue is full\n");
		return NULL;
	}
	qt->front=(qt->front+1)%(qt->capacity);
	void *elt_pos=(char *)qt->data+ qt->front * qt->type_size;
	return elt_pos;
}


/*读取队列顶部元素*/
void *queue_peek(queue_t *qt){
	void *elt_pos=(char *)qt->data +(qt->front+1)*qt->type_size;
	return elt_pos;
}