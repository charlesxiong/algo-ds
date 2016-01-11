/** 
 * sort.h implementation
 *
 *
 *
 */

#ifndef _SORT_H_
#define _SORT_H_

#include <stdbool.h>

#define THRESHOLD 20

/*��������*/
void insertion_sort_int(int *arr,int n);
void binary_insertion_sort_int(int *arr,int n);
void shell_sort_int(int *arr,int n);

/*��������*/
void bubble_sort_int(int *arr,int n);

int partition(int *arr,int left,int right);
void quick_sort_int(int *arr,int left,int right);
void quick_sort_threeway(int *arr,int left,int right);
void quick_sort_threeway_fast(int *arr,int left,int right);

void optimal_sort_int(int *arr,int left,int right);

/*ѡ������*/
void selection_sort_int(int *arr,int n);

void sink_down(int *arr,int k,int len);
void build_max_heap(int *arr,int len);
void heap_sort_int(int *arr,int n);

/*�鲢����*/
void merge_sort_int(int *arr,int *help,int left,int right);
void merge_sort_inplace(int *arr,int left,int right);

/*�ǱȽ�����*/
void counting_sort_int(int *arr,int n);
void radix_sort_int(int *arr,int n);

/*��������*/
void swap(int *a,int *b);


#endif
