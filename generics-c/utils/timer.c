#include <stdio.h>
#include <stdlib.h>
#include "timer.h"


#if USE_HI_RES_TIME
clockval_t (*getclock)(void)=gethrvtime;
const clockval_t CLOCK_TICK= 1000000000;
#else
clockval_t (*getclock)(void)=clock;
const clockval_t CLOCK_TICK= CLOCKS_PER_SEC;
#endif


/************************************************/
void stimer_start() {
	start_time=getclock();
	total_time=0;
}

void stimer_reset(){
	total_time=0;
}

/*停止计时器，返回自上次调用stimer_start后所用的时间，并累积花费的总时间*/
clockval_t stimer_stop(){
	clockval_t stop_time=getclock();
	clockval_t elapsed_time= stop_time - start_time;
	start_time=stop_time;
	total_time +=elapsed_time;
	return elapsed_time;
}

clockval_t stimer_total(){
	return total_time;
}

double stimer_time_total(){
	double scale_time= (((double)stimer_total()) / CLOCK_TICK) * 1000;
	return scale_time;
}

void stimer_print(char *fmt,int trials){
	double scale_time= (((double)stimer_total()/ trials) / CLOCK_TICK) * 1000;
	printf(fmt,scale_time);
}

/************************************************/
mtimer_t *mtimer_alloc(int n){
	mtimer_t *timer=malloc(sizeof(mtimer_t));
	timer->n=n;
	timer->totals=calloc(n,sizeof(clockval_t));
	return timer;
}

void mtimer_free(mtimer_t *t){
	free(t->totals);
	free(t);
}