import java.util.*;

import com.stdlib.*;


public class MinPQ<Key> implements Iterable<Key> {
	private Key[] pq; //队列内部数组元素
	private int N; //队列内部实际存储元素个数
	private Comparator<Key> comp;
	
	@SuppressWarnings("unchecked")
	public MinPQ(int capacity){
		pq=(Key[]) new Object[capacity+1];
		N=0;
	}
	
	public MinPQ(){
		this(1);
	}
	
	@SuppressWarnings("unchecked")
	public MinPQ(Key[] a){
		pq=(Key[]) new Object[a.length+1];
		for(int i=0;i<a.length;i++)
			pq[i+1]=a[i];
		buildMinHeap();
		
	}
	
	@SuppressWarnings("unchecked")
	public MinPQ(int capacity,Comparator<Key> comp){
		this.comp=comp;
		pq=(Key[]) new Object[capacity+1];
		N=0;
	}
	
	public MinPQ(Comparator<Key> comp){
		this(1,comp);
	}
	
	public boolean isEmpty(){
		return N==0;
	}
	
	public int size(){
		return N;
	}
	
	
	/****************important operations*********************/
	public void insert(Key x){
		if(N==pq.length-1) resize(2*pq.length);
		pq[++N]=x;
		swim(N);
	}
	
	public Key minimum(){
		if(isEmpty()) throw new NoSuchElementException("空优先级队列！");
		return pq[1];
	}
	
	public Key delMin(){
		if(isEmpty()) throw new NoSuchElementException("空优先队列，不能删除！");
		Key min=pq[1];
		swap(1,N--);
		sink(1);
		pq[N+1]=null; //防止对象游离
		
		if(N>0 && (N==(pq.length-1)/4) ) resize(pq.length/2); //删除最小元素时动态调整优先队列数组大小
		return min;
	}
	
	/**
	 * 将队列数组的第i个位置的关键字减小到x,要求x不能比原来的关键字大
	 */
	public void decreaseKey(int i,Key x){
		if(i<0 ||i>N ) throw new IllegalArgumentException("队列元素下标位置应为1-N");
		if(greater(x,pq[i])) throw new IllegalArgumentException("关键字x应大于i位置的元素");
		x=pq[i];
		swim(i);
	}
	
	/**
	 * 将堆顶元素的关键字变大，重新进行堆的有序化
	 * 注意不能随便改变堆中的元素值，它支持decreaseKey和increaseTopKey(建议不要使用swim+sink任意修改元素的关键字)
	 */
	public void  increaseTopKey(Key x){
		pq[1]=x;
		sink(1);
	}
	
	public boolean isMinHeap(){
		return isMinHeap(1);
	}
	
	/********************************************************/
	
	/****************helper functions************************/
	/**元素的比较接口和比较器使用**/
	@SuppressWarnings("unchecked")
	private boolean greater(int i,int j){
		if(comp==null){
			return ((Comparable<Key>) pq[i]).compareTo(pq[j]) > 0;
		} else {
			return comp.compare(pq[i], pq[j]) > 0 ;
		}
	}
	
	@SuppressWarnings("unchecked")
	public boolean  greater(Key x, Key y){
		if(comp==null){
			return ((Comparable<Key>)x).compareTo(y) >0;
		} else {
			return comp.compare(x, y) > 0;
		}
	}
	
	private void swap(int i,int j){
		Key t=pq[i];
		pq[i]=pq[j];
		pq[j]=t;
	}
	
	private void sink(int k){
		while(2*k <=N){
			int j=2*k;
			if(j<N && greater(j,j+1)) j++;
			if(!greater(k,j))  break; //这两步缺一不可，判断条件是2*k <= N
			swap(k,j);
			k=j;
		}
	}
	
	private void swim(int k){
		while(k >1 && greater(k/2,k)){
			swap(k/2,k);
			k=k/2;
		}
	}
	
	private void buildMinHeap(){
		for(int k=N/2;k>=1;k--)
			sink(k);
	}
	
	private void resize(int capacity){
		if(capacity >N) {
			@SuppressWarnings("unchecked")
			Key[] temp=(Key[]) new Object[capacity];
			for(int i=1;i<=N;i++)
				temp[i]=pq[i];
			pq=temp;
		}
	}
	
	
	
	private boolean isMinHeap(int k){
		if(k>N) return true;
		int left=2*k;
		int right=2*k+1;
		if(left <=N && greater(k,left)) return false;
		if(right <=N && greater(k,right)) return false;
		return isMinHeap(left) && isMinHeap(right);
	}
	/********************************************************/
	/***************iterator functions************************/
	@Override
	public Iterator<Key> iterator() {
		// TODO Auto-generated method stub
		return new HeapIterator();
	}
	
	private class HeapIterator implements Iterator<Key>{
		private MinPQ<Key>  cur;
		
	
		public HeapIterator(){
			if(comp==null) cur=new MinPQ<Key>(size());
			else cur=new MinPQ<Key>(size(),comp);
			for(int i=1;i<=N;i++)
				cur.insert(pq[i]);
		}
		@Override
		public boolean hasNext() {
			return !cur.isEmpty();
		}

		@Override
		public Key next() {
			if(!hasNext()) throw new NoSuchElementException();
			return cur.delMin();
		}

		@Override
		public void remove() {
			throw new UnsupportedOperationException();
		}
		
	}
	
	public static void main(String[] args) {
		MinPQ<String> queue=new MinPQ<String>();
		In input=new In("tinyPQ.txt");
		while(!input.isEmpty()){
			String element=input.readString();
			if(!element.equals("-")) queue.insert(element);
			else if(!queue.isEmpty()) StdOut.println(queue.delMin());
		}
		StdOut.println("("+ queue.size()+" left on queue)");
		
		for(String t: queue)
			StdOut.println(t);

	}

}
