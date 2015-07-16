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

/**
 * 首先取长度的一半作为增量的步长d1,把表中全部记录分成d1个组
 * 把步长隔d1的记录放在同一组中再进行直接插入排序；
 * 然后再取d1的一半作为步长,重复插入排序操作
 * 一般默认n在某个特定范围时，希尔排序的时间复杂度为O(n^1.3)
 * 稳定性: 当相同关键字映射到不同的子表中，可能会改变相对次序，不稳定排序
 * 例如(3,2,2)就会改变2的相对次序
 */
void shell_sort_int(int *arr,int n) {
	for(int dk = n / 2; dk >= 1; dk >>= 1) {
		for(int i = dk; i < n;i++) {
			int key = arr[i];
			int j = i - dk;
			for(; j >=0 && arr[j] > key; j -= dk) {
				arr[j + dk] = arr[j];
			}
			arr[j + dk] = key;
		}
	}
}

void swap(int *a,int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble_sort_int(int *arr,int n) {
	for(int i = 0; i < n - 1; i++) { //n-1趟冒泡,每次确定一个元素，每次确定小值元素
		bool flag = false;
		for(int j = n- 1; j > i; j--) {
			if(arr[j - 1] > arr[j]) { //有逆序
				swap(&arr[j - 1],&arr[j]);
				flag = true; //发生交换
			}
		}
		if(flag == false)
			return ; //表明本次遍历没有交换，则表已经有序
	}
}

/**
 * 两指针分别从首尾向中间扫描
 *　这里主要考虑的是选取pivot的策略，可能是首元素或尾元素，甚至是三数取中策略或者随机取某个数的策略
 * 思路是将数据以pivot作划分，右侧小于pivot移到左侧，左侧大于pivot移到右侧
 * 此方法可以用来确定第k大或第k小的元素
 */
int partition(int *arr,int left,int right) {
	int pivot = arr[left];
	while(left < right) {
		while(left < right && pivot <= arr[right])
			right--;
		arr[left] = arr[right]; //比pivot值小的移到左端
		while(left < right && pivot >= arr[left])
			left++;
		arr[right] = arr[left]; //比pivot值大的移到右端
	}
	arr[left] = pivot; //left == right
	return left;
}

/**
 * 另外一种划分策略是: 
 * 把左右端不满足条件的元素交换,最后循环终止的元素应该与开始元素进行交换
 * 结合前后两个策略: 既双向遍历又使用了交换操作
 */
int partition1(int *arr,int left,int right) {
	int start = left;
	int pivot = arr[left];
	while(left < right) {
		while(left < right && pivot <= arr[right])
			right--;
		while(left < right && pivot >= arr[left])
			left++;
		swap(&arr[left],&arr[right]); 
	}
	swap(&arr[start],&arr[left]);
	return left;
}

/**
 * 单向遍历: 两指针索引一前一后逐步向后扫描 
 *　策略: 记录一个last指针，用于保存小于或等于pivot的元素
 *　通过从左往右扫描，每遇见一个元素小于等于pivot即将它存储于last指针里
 * 一趟划分过后last之前的元素(包括last,这取决于last的初始化)小于等于pivot,
 * 该划分算法的特点: 从前向后遍历,last记录的是小于等于pivot的元素，这些元素相对顺序不变
 *
 * 若要大于等于pivot的元素相对顺序不变，可从后向前遍历，pivot取首元素
 * 变式题: 
 * 如果pivot不方便取，例如三色旗问题要保证0,1,2三者有序
 * 使用单纯的单向遍历会存在0和1顺序乱的情况，建议用条件判断的形式划分为三个区域
 * 即记录多个指针,left(保存小值),right(保存大值),cur遍历元素判断
 */
int partition2(int *arr,int left,int right) {
	int pivot = arr[right];
	int last = left -1;
	for(int i = left; i < right; i++) {
		if(arr[i] <= pivot) {
			++last;
			swap(&arr[last],&arr[i]);
		}
	}
	swap(&arr[last + 1],&arr[right]);
	return last + 1;
}


/**
 *
 * 时间效率: 快排的运行时间与划分是否对称有关，平均时间复杂度为O(nlgn),最坏为O(n^2)
 * 快排是所有内部排序算法中平均性能最好的
 * 提高算法效率: 在元素基本有序时采取直接插入排序(STL就这么干，给定一个阈值)
 * 保证划分的平衡性,例如三数取中位数或者随机选择pivot元素，这样使得最坏情况不太可能发生
 *
 * 空间效率: 采用递归工作栈，空间复杂度最好情况下为O(lgn),最坏为O(n)
 * 稳定性: 在划分算法中，若右侧有两个相同的元素，在小于pivot时交换到左侧相对位置就会发生变化
 * 表明快排是一种不稳定排序，每趟排序能将一个元素位置确定下来(pivot)
 */
void quick_sort_int(int *arr,int left,int right) {
	if(left < right) {
		int pos = partition1(arr,left,right); //划分
		quick_sort_int(arr,left,pos - 1);
		quick_sort_int(arr,pos + 1,right);
	}
}

/**
 * 选择排序的基本思路: 每一趟要在后面的元素中确定一个最值元素，重复n - 1趟
 * 时间效率: 注意元素的比较次数与初始序列无关，始终要比较n(n-1)/2,时间复杂度为O(n^2)
 * 空间效率为O(1)
 * 稳定性:不稳定排序，例如6/8/6/5
 */
void selection_sort_int(int *arr,int n) {
	int min;
	for(int i = 0; i < n - 1;i++) {//n-1趟选择排序，每次选择一个最小值
		min = i;
		for(int j = i + 1; j < n;j++) {
			if(arr[min] < arr[j]) {
				min = j; //更新最小元素位置
			}
		}
		if(min != i) swap(&arr[i],&arr[min]); //更新到的最小值与i位置交换
	}
}


/**
 * 下标为k的堆的自顶向下操作
 * 保持根为下标k的元素的子树满足最大堆性质 
 * 如果某个节点比它们的两个子节点或之一更小，则以该节点为根的子树不满足最大堆性质
 * 调节办法：把更小的元素由上至下下沉，以类似的方式维持其子节点的堆状态性质直到某子节点元素满足最大堆的状态
 *
 * 向下调整的时间与树高有关为O(h)
 * 此操作用于构造堆，堆排序和删除操作(delMax)
 */
void sink_down(int *arr,int k,int len) {
	while(2 * k <= len) {
		int j = 2 * k;
		if(j <len && arr[j] < arr[j + 1]) j++; //取更大的元素
		if(arr[k] > arr[j]) break; //根元素大于子节点，则满足最大堆性质无需调整
		swap(&arr[k],&arr[j]);
		k = j;
	}
}

/**
 * 下标为k的堆自底向上操作
 * 即该节点的大小比其父节点更大，则需要进行向上调整
 * 注意终止条件是k ＝　1且父节点更大
 */
void swim_up(int *arr,int k) {
	while(k > 1 && arr[k] > arr[k / 2]) {
		swap(&arr[k],&arr[k / 2]);
		k = k / 2;
	}
}


/**
 * 以无序数组自底向上构造出一个最大堆，时间复杂度为O(n)
 * 注意0号不存储元素，实际存储从1开始,数组长度为len + 1
 * 从n＝len/2开始进行自顶向下调整操作
 *
 * 大根堆一般可用于求海量数据中最小的k个数
 * 即先读取k个元素构造最大堆，再依次读入数据
 * 若当前数据比堆顶小,则替换堆顶；若当前数据比较大，不可能是最小的k个数
 * 求最大的k个数一般用小根堆
 */
void build_max_heap(int *arr,int len) {
	for(int i = len / 2; i >= 1;i--)
		sink_down(arr,i,len);
}

/**
 * 堆排序是一种树形选择排序，利用完全二叉树中父节点和子节点的关系选择最值的元素
 *　步骤:
 * 先构造大根堆(这也是一个反复向下调整满足最大堆性质的操作)
 * 然后再把堆顶元素与堆底元素交换，此时根结点不再满足堆的性质
 * 堆顶元素向下调整重复操作，直到堆中剩一个元素为止，要进行n-1趟交换和调整操作
 *
 * 时间效率: 在最好、平均和最坏情况下，堆排序的时间复杂度均为O(nlgn)
 * 空间效率: O(1)
 * 稳定性: 不稳定排序
 */
void heap_sort_int(int *arr,int len) {
	build_max_heap(arr,len);
	for(int i = len; i > 1;i--) {
		swap(&arr[i],&arr[1]); //和堆顶元素交换,并输出堆顶元素
		sink_down(arr,1,i - 1); //注意还剩余i-1个元素调整堆
	}
}




