import java.util.*;

import com.stdlib.*;

/**
 * 以一个二元堆实现泛型化的最大优先级队列，要求泛型类型是可比较的,Comparable
 * 因而如果是Java中的基本引用类型，一般是实现了Comparable接口的，如果是自己设计的类型需要实现Comparable接口 
 * 可用Comparator代替自然顺序
 */

public class MaxPQ<Key> implements Iterable<Key> {
	private Key[] pq;//优先队列元素数组
	private int N; //优先队列元素的个数
	private Comparator<Key> comp;
	
	/*创建一个含初始容量的优先级队列*/
	@SuppressWarnings("unchecked")
	public MaxPQ(int capacity){
		pq=(Key[])new Object[capacity+1];
		N=0;
	}
	
	/*创建一个无参数的优先级队列*/
	public MaxPQ(){
		this(1);
	}
	
	@SuppressWarnings("unchecked")
	public MaxPQ(int capacity,Comparator<Key> comp){
		this.comp=comp;
		pq=(Key[])new Object[capacity+1];
		N=0;
	}
	
	/*创建一个无参数的优先级队列*/
	public MaxPQ(Comparator<Key> comp){
		this(1,comp);
	}
	
	/*用数组中的元素创建一个优先队列*/
	@SuppressWarnings("unchecked")
	public MaxPQ(Key[] a){
		N=a.length;
		pq=(Key[])new Object[N+1];
		for(int i=0;i<N;i++) //堆元素起始位置为1,0号元素不作为堆元素
			pq[i+1]=a[i];
		buildMaxHeap();
		//assert isMaxHeap(); 
	}
	
	/*队列是否为空*/
	public boolean isEmpty(){
		return N==0;
	}
	
	/*队列中的元素个数*/
	public int size(){
		return N;
	}
	
	
	
	/****************important operations*********************/
	
	/**
	 * 插入一个元素
	 * 检测队列大小与数组大小是否差1，判断队列数组是否能容纳新的元素。如果没有，扩容一倍
	 */
	public void insert(Key key){
		if(N+1>=pq.length) resize(2*pq.length);
		pq[++N]=key;
		swim(N);
	}
	
	/*返回优先队列中含最大关键字的元素*/
	public Key maximum(){
		return pq[1];
	}
	
	/**
	 * 删除并返回含最大关键字的元素
	 * 检测队列有效元素大小是否小于数组大小的1/4，如果是数组长度减半，状态约为半满
	 */
	public Key delMax(){
		if(isEmpty()) throw new NoSuchElementException("Priority queue is empty");
		Key max=pq[1];
		swap(1,N--);
		pq[N+1]=null; //防止对象游离
		sink(1);
		if(N>0 && (N==(pq.length-1)/4)) resize(pq.length/2); //pq长度过大，实际存储的元素个数只有它的1/4，
		return max;
	}
	
	/**
	 * 将队列数组的第i个位置的关键字增加到x,要求x不能比原来的关键字小
	 */
	public void increaseKey(int i,Key x){
		if(i<0 ||i>N ) throw new IllegalArgumentException("队列元素下标位置应为1-N");
		if(less(x,pq[i])) throw new IllegalArgumentException("关键字x应大于i位置的元素");
		x=pq[i];
		swim(i);
	}
	
	/**
	 * 将堆顶元素的关键字减小，重新进行堆的有序化
	 * 注意不能随便改变堆中的元素值，支持increaseKey和decreaseTopKey(建议不要使用swim+sink任意修改元素的关键字)
	 */
	public void  decreaseTopKey(Key x){
		pq[1]=x;
		sink(1);
	}
	
	/********************************************************/
	
	/****************helper functions************************/
	/*比较元素大小*/
	@SuppressWarnings("unchecked")
	private boolean less(int i,int j){
		if(comp==null){
			return ((Comparable<Key>)pq[i]).compareTo(pq[j]) <0;
		} else {
			return comp.compare(pq[i], pq[j]) < 0;
		}
	}
	
	
	@SuppressWarnings("unchecked")
	public boolean less(Key x, Key y){
		if(comp==null){
			return ((Comparable<Key>)x).compareTo(y) <0;
		} else {
			return comp.compare(x, y) < 0;
		}
	}
	
	/*交换元素*/
	private void swap(int i,int j){
		Key t=pq[i];
		pq[i]=pq[j];
		pq[j]=t;
	}
	

	/**
	 * 保持根为下标k的元素的子树满足最大堆性质 
	 * 如果某个节点比它们的两个子节点或之一更小，则以该节点为根的子树不满足最大堆性质
	 * 调节办法：把更小的元素由上至下下沉，以类似的方式维持其子节点的堆状态性质直到某子节点元素满足最大堆的状态
	 */
	private void sink(int k){
		while(2*k <=N){
			int j=2*k;
			if(j<N && less(j,j+1)) j++;
			if(!less(k,j)) break;
			swap(k,j);
			k=j;
		}
	}
	
	/**
	 *
	 * 如果堆的有序状态因为某个子节点比它的父节点更大而被打破
	 * 调节办法：把更大的元素由下至上上浮，只需要交换子节点和父节点元素即可，直至该节点不再大于父节点
	 * @param k
	 */
	public void swim(int k){
		while(k>1 && less(k/2,k)){ //k不应该为1
			swap(k/2,k);
			k=k/2;
		}
	}
	
	/*以优先队列中的无序数组自底向上构建出一个最大堆，运行时间为O(n)*/
	public void buildMaxHeap(){
		for(int k=N/2;k>=1;k--)
			sink(k);
	}
	
	/*动态调整数组的大小*/
	private void resize(int capacity){
		if(capacity >N){
			@SuppressWarnings("unchecked")
			Key[] temp=(Key[]) new Object[capacity];
			for(int i=1;i<=N;i++)
				temp[i]=pq[i];
			pq=temp;
		}
	}
	
	/*判断 pq[1..N]是否是最大堆*/
	@SuppressWarnings("unused")
	private boolean isMaxHeap(){
		return isMaxHeap(1);
	}
	
	/*判断以下标为k的子树是否满足最大堆性质*/
	private boolean isMaxHeap(int k){
		if(k>N) return true;
		int left=2*k;
		int right=left+1;
		if(left  <=N  && less(k,left))  return false;
		if(right <=N  && less(k,right)) return false;
		return isMaxHeap(left) && isMaxHeap(right);
	}
	/********************************************************/
	
	/***************iterator functions************************/
	/**
	 * 以迭代器的形式-以降序的方式遍历优先队列中的元素
	 */
	@Override
	public Iterator<Key> iterator() {
		// TODO Auto-generated method stub
		return new HeapIterator();
	}
	
	private class HeapIterator implements Iterator<Key> {
		private MaxPQ<Key> cur;
		
		
		/**
		 * 以线性时间把所有项添加到新堆中去，再对新堆做操作
		 */
		public HeapIterator(){
			if(comp==null) cur=new MaxPQ<Key>(size());
			else           cur=new MaxPQ<Key>(size(),comp);
			for(int i=1;i<=N;i++)
				cur.insert(pq[i]);
		}
		
		@Override
		public boolean hasNext() {
			// TODO Auto-generated method stub
			return !cur.isEmpty();
		}

		@Override
		public Key next() {
			// TODO Auto-generated method stub
			if(!hasNext()) throw new NoSuchElementException();
			return cur.delMax();
		}

		@Override
		public void remove() {
			throw new NoSuchElementException();	
		}
		
	}
	
	public  void heapSort(){
		buildMaxHeap();
		while(N>1){
			swap(1,N--);
			sink(1);
		}
		
	}
	
	
	public static void main(String[] args) {
		MaxPQ<String> queue=new MaxPQ<String>();
		In input=new In("tinyPQ.txt");
		while(!input.isEmpty()){
			String element=input.readString();
			if(!element.equals("-")) queue.insert(element);
			else if(!queue.isEmpty()) StdOut.println(queue.delMax()+ " ");
		}
		StdOut.println("(" + queue.size()+ " left on queue)");
		for(String t:queue) //迭代器形式
			StdOut.println(t);
	    

	}

	

}
