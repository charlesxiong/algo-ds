import java.util.*;
import com.stdlib.*;

/**
 * 设计一个数据结构用于动态查找中位数，它支持以下几种操作
 * 对数时间内插入元素，常数时间内找到中位数并在对数时间内删除中位数
 * 
 * 思路：针对所有比中位数小的元素维持一个最大堆，所有比中位数大的元素维持一个最小堆
 * 通过如下的插入操作设计保证最大堆和最小堆的元素个数之差保持在1内，中位数即在两个堆顶元素里面产生
 * 如果两堆大小相同，取两堆顶元素的平均值；否则，取元素个数更大的堆的堆顶元素
 * @author charles
 *
 */
public class DynamicMedian {
	private MaxPQ<Integer> maxHeap;
	private MinPQ<Integer> minHeap;
	
	
	public DynamicMedian() {
		maxHeap=new MaxPQ<Integer>();
		minHeap=new MinPQ<Integer>();
		
	}

	public boolean isEmpty(){
		return maxHeap.isEmpty()&&minHeap.isEmpty();
	}
	
	/**
	 * 对数时间内插入
	 */
	public void insert(int x){
		int maxsize=maxHeap.size();
		int minsize=minHeap.size();
		
		/**
		 * 这两步保证初始化时小于中位数的数组成最大堆，大于中位数的数组成最小堆
		 * 有先后顺序，保证先插入最大堆
		 * 当前元素小于最大堆最大元素，需要交换两个堆
		 */
		if(maxsize==0){ 
			maxHeap.insert(x);
			return;
		} 
		if(minsize==0){ //
			if(greater(maxHeap.maximum(),x)){ 
				Integer max=maxHeap.delMax();
				minHeap.insert(max);
				maxHeap.insert(x);
			} else {
			   minHeap.insert(x);
			}
			return ;
		} 
		
		if(greater(maxHeap.maximum(),x)){ 
			/**
			 * 当前插入元素小于最大堆最大元素时
			 * 最大堆的元素个数与最小堆元素个数之差为1，把最大堆堆顶元素移除到最小堆中，再将当前元素插入最大堆中
			 * 差为0或-1时，直接将当前元素插入最大堆中
			 */
			if(maxsize-minsize==1){ 
				Integer max=maxHeap.delMax();
				minHeap.insert(max);
				maxHeap.insert(x);
			} else { 
				maxHeap.insert(x);
			}
		} else if(greater(x,minHeap.minimum())){
			/**
			 * 当前插入元素大于最小堆最小元素时
			 * 最小堆的元素个数与最大堆元素个数之差为1，把最小堆堆顶元素移除到最大堆中，再将当前元素插入最小堆中
			 * 差为0或-1时，直接将当前元素插入最小堆中
			 */
			if(minsize-maxsize==1) {
				Integer min=minHeap.delMin();
				maxHeap.insert(min);
				minHeap.insert(x);
			} else {
				minHeap.insert(x);
			}	 
		} else {
			/**
			 * 当前插入元素大于等于最大堆最大元素且小于等于最小堆最小元素时
			 * 最大堆的元素个数与最小堆元素个数之差为1，将当前元素插入最小堆中
			 * 差为0或-1时，将当前元素插入最大堆中
			 */
			if(maxsize-minsize==1){
				 minHeap.insert(x);
			} else {
				 maxHeap.insert(x);
			}
		 }
	}
	
	
	/**
	 * 常数时间内得到中位数
	 * @return
	 */
	public double median(){
		if(isEmpty()) throw new NoSuchElementException("集合元素为空");
		if(maxHeap.size()==minHeap.size())
			return (double)((maxHeap.maximum() + minHeap.minimum()))/2;
		else if(maxHeap.size() > minHeap.size())
			return maxHeap.maximum();
		else 
			return minHeap.minimum();
	}
	
	/**
	 * 对数时间删除中位数
	 * @return
	 */
	public double delMedian(){
		if(isEmpty()) throw new NoSuchElementException("集合元素为空");
		double median;
		if(maxHeap.size()==minHeap.size()) {
			median=((double)(maxHeap.maximum() + minHeap.minimum()))/2;
			maxHeap.delMax();
			minHeap.delMin();
		}
		else if(maxHeap.size() > minHeap.size()) {
			median=maxHeap.maximum();
			maxHeap.delMax();
		}
		else {
			median=minHeap.minimum();
			minHeap.delMin();
		}
		return median;
	}
	
	
	
	private boolean greater(Integer x1,Integer x2){
		return ((Comparable<Integer>)x1).compareTo(x2)>0;
	}

	public static void main(String[] args) {
		DynamicMedian dm=new DynamicMedian();
		In input=new In("median-data.txt");
		while(!input.isEmpty()){
			int val=input.readInt();
			dm.insert(val);
		}
		System.out.println(dm.median());
		dm.delMedian();
		System.out.println(dm.median());
	}

}
