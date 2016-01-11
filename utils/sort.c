/** 
 * sort.c implementation
 *
 *
 *
 */

#include <stdio.h>
#include "sort.h"

/**
 * 直接插入排序时间复杂度为O(n^2),空间复杂度为O(1)
 * 最好情况下是元素基本有序，此时每插入一个元素，只需比较几次而无需移动，时间复杂度为O(n)
 * 稳定性: 保证相等元素的插入相对位置不会变化，稳定排序的方法
 */
void insertion_sort_int(int *arr,int n) {
	for(int i = 1;i < n;i++) {
		int key = arr[i];
		int j = i - 1;
		for(; j >= 0 && arr[j] > key;j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}

void binary_insertion_sort_int(int *arr,int n) {
	for(int i = 1;i < n;i++) {
		int key = arr[i];
		int left = 0;
		int right = i - 1;
		while(left <= right) {
			int mid = (left + right) / 2;
			if(key < arr[mid]) 
				right = mid - 1;
			 else
			 	left = mid + 1;
		}
		for(int j = i - 1; j >= left; j--)
			arr[j + 1] = arr[j];
		arr[left] = key;
	}
}


