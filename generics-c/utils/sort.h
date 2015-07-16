#ifndef _SORT_H_
#define _SORT_H_

#include <stdbool.h>

/*插入排序*/
void insertion_sort_int(int *arr,int n);
void shell_sort_int(int *arr,int n);

/*交换排序*/
void bubble_sort_int(int *arr,int n);

int partition(int *arr,int left,int right);
void quick_sort_int(int *arr,int left,int right);

/*选择排序*/
void selection_sort_int(int *arr,int n);

void sink_down(int *arr,int k,int len);
void build_max_heap(int *arr,int len);
void heap_sort_int(int *arr,int n);

/*归并排序*/
void merge_sort_int(int *arr,int *help,int left,int right);
void merge_sort_inplace(int *arr,int left,int right);

/*非比较排序*/
void counting_sort_int(int *arr,int n);
void radix_sort_int(int *arr,int n);

/*辅助函数*/
void swap(int *a,int *b);

#endif