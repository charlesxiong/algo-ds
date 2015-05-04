#include "skiplist.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/***********************辅助函数*********************/
/*注意节点内部本身含有一个指向下一个节点的指针，结合后面的level共有level+1层*/
skiplist_node_t *new_skiplist_node(int level,void *item){
	skiplist_node_t *node=(skiplist_node_t *)malloc(sizeof(skiplist_node_t)+level*sizeof(skiplist_node_t *));
	/*可以更新该节点每个level的前向指针forward，非必须的*/
	if(node==NULL){
		printf("内存不足，无法初始化跳表节点\n");
		exit(1);
	}
	node->item=item;
	return node;
}

/**
 * 定义跳表最大层次数max_level,
 * 随机生成节点层次的概率为prob
 * level值为1..max_level
 * 这种随机数生成效果并不是很好，可能会出现中间某些层次干脆
 */
int rand_level(double prob,int max_level){
	int level;
	int rand_mark=prob*RAND_MAX;
	for(level=0; rand()<rand_mark && level<max_level;level++) ;
	return level;

}

int rand_level1(int max_level){
	static int bits=0;
	static int reset=0;
	int h,found=0;

	for(h=0;!found;h++){
		if(reset==0){
			bits=rand();
			reset=sizeof(int)*8;
		}

		found= bits&1;
		bits=  bits>>1;
	}

	if(h>max){
		return max;
	}
	return h;
}

/**********************************************/


/**
 * 初始化内存分配
 * 链表头结点有max_level个前向指针，从0开始计算
 * 对应层次i的前向指针为NULL表示该层级上的虚拟链表为空
 * 链表的层次为i,表示若随机生成的level大于i则i层次以上的前向指针均指向为NULL
 */
skiplist_t *skiplist_alloc(int capacity,double prob,int (*comp)(const void *,const void *)){
	skiplist_t *l=malloc(sizeof(skiplist_t));
	l->prob=prob;
	l->comp=comp;
	/*注gcc的数学函数定义在libm.so文件例，需链接上数学库，编译时添加 -lm选项*/
	int max_level= -log(capacity)/log(prob);//这个指的是最高的层级max_level,例如8个节点的话有0,1,2,3层
	l->max_level=max_level; //例如max_level为16
	l->level=0;
	l->head=new_skiplist_node(max_level,NULL);
     
	/*更新头结点的forward数组为NULL*/
	for(int i=0;i<=max_level;i++){
		l->head->forward[i]=NULL;
	}

	/*为防止每次插入或删除操作时要重复分配update数组*/
	l->update=malloc((max_level+1)*sizeof(skiplist_node_t *));
	l->n=0;
	return l;
}



void skiplist_free(skiplist_t *l){
	if(!l)
		return ;
	skiplist_node_t *cur,*tmp;
	cur=l->head->forward[0]; //这才是第一个节点
	while(cur){
		tmp=cur;
		cur=cur->forward[0];
		free(tmp);
	}
	free(l->head); //最后再释放虚拟头结点
	free(l->update);
	free(l);
}

/**
 * 跳表的插入操作要点
 * 1 找到带插入的位置(在当前元素的前向指针的键与元素的键相等或者大于的适合退出)，然后再更新在每个层次的update数组
 * 2 随机生成新节点的level
 * 3 调整指向，插入新节点
 */
void *skiplist_insert(skiplist_t *l,void *item){
	skiplist_node_t *cur=l->head;
	skiplist_node_t **update=l->update;
	int (*comp)(const void *,const void *);
	comp=l->comp;
	int i;
	/*查找键所属的位置*/
	for(i=l->level;i>=0;i--){
		while(cur->forward[i]!=NULL &&comp(cur->forward[i]->item,item)<0)
			cur=cur->forward[i]; //在当前层次遍历直至前向指针为NULL或者对应的前向指针的元素大于或等于item
		update[i]=cur; //更新插入位置的前驱指针
	}
	cur=cur->forward[0];
	if(cur!=NULL&&comp(cur->item,item)==0)
		return cur->item; //键值已存在，直接返回原来的节点

	int level=rand_level(l->prob,l->max_level); //最大的level控制在max_level
	if(level> l->level){ //如果新生成的层数比跳表层数大，更新下标大于i的update数组指向为头结点
		for(i=l->level+1;i<=level;i++){ //持续到当前生成的level上
			update[i]=l->head;
		}
		l->level=level; //更新自己的层级数
	}
	skiplist_node_t *tmp=new_skiplist_node(level,item);
	printf("%d ",level);

	/**
	 * 调整前向指针的指向，插入新结点
	 * 问题就出现在这里，注意如果生成的level级别较低，只需要在从0..level的级别进行插入，切记不能使用l->level
	 * l->level和level是有不同的，除非level大于当前跳表的level时
	 */
	for(i=0;i<=level;i++){ 
		tmp->forward[i]=update[i]->forward[i];
		update[i]->forward[i]=tmp;
	}
	l->n++;
	return NULL;
}

/*在跳表中进行查找，找到返回当前元素的item否则返回NULL*/
void *skiplist_find(skiplist_t *l,void *key_item){
	/*查找是否含有当前的元素*/
	skiplist_node_t *cur=l->head;
	skiplist_node_t **update=l->update;
	int (*comp)(const void *,const void *);
	comp=l->comp;
	int i,res;
	for(i=l->level;i>=0;i--){
		while(cur->forward[i]!=NULL &&((res=comp(cur->forward[i]->item,key_item))<0))
			cur=cur->forward[i]; //在当前层次遍历直至前向指针为NULL或者对应的前向指针的元素大于或等于item
		update[i]=cur; //更新插入位置的前驱指针
	}
	cur=cur->forward[0];
	if(cur!=NULL&&comp(cur->item,key_item)==0){
		return cur->item;
	}
	return NULL;
}

void *skiplist_find_min(skiplist_t *l){
	skiplist_node_t *cur=l->head->forward[0];
	return (cur!=NULL)?cur->item:NULL;
}



/**
 * 跳表的删除操作要点
 * 1 找到要调整位置的前驱指针
 * 2 自底层向高层进行节点的删除并释放该节点内存
 * 3 （由于某些节点的删除可能会使部分高层次的前向指针为NULL）更新跳表的level
 */
void *skiplist_delete(skiplist_t *l,void *item){
	skiplist_node_t *cur=l->head;
	skiplist_node_t **update=l->update;
	int (*comp)(const void *,const void *);
	comp=l->comp;
	int i;
	int level=l->level;
	for(i=level;i>=0;i--){
		while(cur->forward[i]&&comp(cur->forward[i]->item,item)<0)
			cur=cur->forward[i];
		update[i]=cur;
	}
	cur=cur->forward[0];
	if(cur==NULL||comp(cur->item,item)!=0) return NULL; //键值不存在


	for(i=0;i<=level;i++){
		if(update[i]->forward[i]!=cur) break; //若低层次的前向指针不包括cur，则高层次就不可能存在(高层次的链表是低层次的子链表)
		update[i]->forward[i]=cur->forward[i];
	}
	void *ret_item=cur->item;
	l->n--;
	free(cur);

	while(l->level>0 &&l->head->forward[l->level]==NULL)
		l->level--;
	return ret_item;
}

/*从跳表中删除具有最小键值的表项*/
void *skiplist_delete_min(skiplist_t *l){
	skiplist_node_t *cur=l->head->forward[0];
	if(cur)
		return skiplist_delete(l,cur->item);
	else
		return NULL;
}

void skiplist_foreach(skiplist_t *l,void (*visit)(skiplist_node_t *)){
	skiplist_node_t *cur;
	int i;
	for(i=l->level;i>=0;i--){
		cur=l->head->forward[i];
		printf("level %d: ",i);
		while(cur){
			visit(cur);
			cur=cur->forward[i];
		}
		printf("\n");
	}
}