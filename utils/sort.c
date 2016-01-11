/** 
 * sort.c implementation
 *
 *
 *
 */

#include <stdio.h>
#include "sort.h"

/**
 * ֱ�Ӳ�������ʱ�临�Ӷ�ΪO(n^2),�ռ临�Ӷ�ΪO(1)
 * ����������Ԫ�ػ������򣬴�ʱÿ����һ��Ԫ�أ�ֻ��Ƚϼ��ζ������ƶ���ʱ�临�Ӷ�ΪO(n)
 * �ȶ���: ��֤���Ԫ�صĲ������λ�ò���仯���ȶ�����ķ���
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


