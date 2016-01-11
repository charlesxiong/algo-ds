#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_
#include <time.h>

/**
 * 提供能进行多次实验的单计时器和多计时器结构的实现: 
 * single_timer(记为stimer) multi_timer(记为mtimer)
 */

#define USE_HI_RES_TIME 0

/**
 * 允许用户指定时钟计时函数
 * USE_HI_RES_TIME：　gethrvtime(),时间数据类型为hrtime_t- 在Solaris系统以纳秒级别提供高分辨率的实时计时
 * 默认为C/C++的计时函数: clock(), 时间数据类型为clock_t- 返回调用所需要的时钟计时单元数(C++里面的时钟，而非CPU时钟)
 * 注意要考虑与操作系统相关的一个转换,要想换算成秒或毫秒，需要除以一个时钟计时数(以秒计)，返回ms级别的计时精度
 */
#if USE_HI_RES_TIME
typedef hrtime_t clockval_t;
#else
typedef clock_t clockval_t;
#endif

/*声明在其他地方定义*/
extern clockval_t (*getclock)(void);
extern const clockval_t CLOCK_TICK;

clockval_t start_time;
clockval_t total_time;

typedef struct {
	int n;
	clockval_t *totals;
} mtimer_t;



/************************************************/

/**
 * 单计时器: 一般用于测试单个算法或功能
 * 倍率测试: 分析问题的规模对于算法的影响，估计运行时间的增长数量级
 * 重复测试: 运行大量的测试，计算所需的平均时间，并减小系统本身的影响
 */

/*开启计时器*/	
void stimer_start();

/*重置计时器，开始时间置为0*/
void stimer_reset();

/*停止计时器，返回自上次调用stimer_start后所用的时间，并累积花费的总时间*/
clockval_t stimer_stop();

/*返回单计时器的计时时间，以clockval_t为时间的输出单位*/
clockval_t stimer_total();

/*以毫秒单位返回计时结果*/
double stimer_time_total();

/*输出计时结果*/
void stimer_print(char *fmt,int trials);



/************************************************/

/**
 * 多计时器: 一般用于比较多个算法策略的运行性能，
 * 可用单计时器代替
 */
mtimer_t *mtimer_alloc(int n);
void mtimer_free(mtimer_t *t);
void mtimer_reset(mtimer_t *t);
void mtimer_reseti(mtimer_t *t, int i);
void mtimer_start();
clockval_t mtimer_stop(mtimer_t *t,int i);
clockval_t mtimer_total(mtimer_t *t,int i);

void mtimer_print(mtimer_t *t,char *fmt,int trials);
void mtimer_printi(mtimer_t *t,char *fmt,int trials,int i);

/************************************************/



#endif
