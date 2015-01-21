import java.util.*;

import com.stdlib.*;
/**
 * 索引队列的实现
 * 利用一个整数索引对应特定的元素引用，每个元素对应一个索引
 * @author charles
 */
public class IndexMinPQ<Key extends Comparable<Key> > implements Iterable<Integer>{
	private int maxN;
    private int N; //PQ中实际的元素个数
    private int[] pq; //索引二叉堆，由1开始-元素位置对应的索引号,索引的取值范围0-maxN-1
    private int[] qp; //索引对应的元素位置，也就是qp[i]的值即i在pq[]中的位置(pq[qp[i]]=qp[pq[i]]=i)
    private Key[] keys; //存储元素的数组
    
	@SuppressWarnings("unchecked")
	public IndexMinPQ(int maxN) {
		if(maxN <0) throw new IllegalArgumentException("The size should be non-negative");
		keys=(Key[])new Comparable[maxN+1]; //0号位置不使用
		this.maxN=maxN;
		pq=new int[maxN+1];
		qp=new int[maxN+1];
		for(int i=0;i<=maxN;i++) qp[i]=-1; //索引i不在队列之中，总是设定为-1
	}
	
	public boolean isEmpty(){
		return N==0;
	}
	
	public int size(){
		return N;
	}
	
    /*是否存在索引i的元素*/
	public boolean contains(int i){
		if(i<0 || i >=maxN) throw new IndexOutOfBoundsException();
		return qp[i]!=-1;
	}
	
	/*返回索引对应的元素*/
	public Key keyOf(int i){
		if(i<0 || i>=maxN) throw new IndexOutOfBoundsException();
		if(!contains(i)) throw new NoSuchElementException("索引不在优先队列中");
		else return keys[i];
	}
	
	/*插入元素x,并和索引i相关联*/
	public void insert(int i,Key x){
		if(i<0 || i>=maxN) throw new IndexOutOfBoundsException();
		if(contains(i)) throw new IllegalArgumentException("索引已在优先队列中");
		pq[++N]=i;
		qp[i]=N;
		keys[i]=x;
		swim(N);
	}
	
	public int minIndex(){
		if(N==0) throw new NoSuchElementException("优先队列为空");
		return pq[1];
	}
	
	public Key minimum(){
		if(N==0) throw new NoSuchElementException("优先队列为空");
		return keys[pq[1]];
	}
	
	/*删除最小元素并返回它的索引*/
	public int delMin(){
		if(isEmpty()) throw new NoSuchElementException("优先队列为空");
		int indexOfMin=pq[1]; //对应的索引号
		swap(1,N--);
		sink(1);
		keys[pq[N+1]]=null;  //删除最小值元素
		qp[pq[N+1]]=-1;
		//qp[indexOfMin]=-1; //该索引不在队列中	
		return indexOfMin;
	}
	
	/*索引为i对应的元素增至x*/
	public void increaseKey(int i,Key x){
		if(i<0 || i>=maxN) throw new IndexOutOfBoundsException();
		if(!contains(i)) throw new NoSuchElementException("索引不在优先队列中");
		if(x.compareTo(keys[i])<0) throw new IllegalArgumentException("要求x不能比原来的关键字小"); 
		keys[i]=x;
		sink(qp[i]);
	}
	
	/*索引为i对应的元素减至x*/
	public void decreaseKey(int i,Key x){
		if(i<0 || i>=maxN) throw new IndexOutOfBoundsException();
		if(!contains(i)) throw new NoSuchElementException("索引不在优先队列中");
		if(x.compareTo(keys[i])>0) throw new IllegalArgumentException("要求x不能比原来的关键字大"); 
		keys[i]=x;
		swim(qp[i]);
	}
	
	/*把索引为k的元素改为x*/
	public void changeKey(int i,Key x){
		if(i<0 || i>=maxN) throw new IndexOutOfBoundsException();
		if(!contains(i)) throw new NoSuchElementException("索引不在优先队列中");
		keys[i]=x;
		sink(qp[i]);
		swim(qp[i]); //交换位置可以么？
	}

	/*删除索引i及其相关联的元素*/
	public void delete(int i){
		if(i<0 || i>=maxN) throw new IndexOutOfBoundsException();
		if(!contains(i)) throw new NoSuchElementException("索引不在优先队列中");
		int pos=qp[i];
		swap(pos,N--);
		swim(pos);
		sink(pos);
		keys[i]=null;
		qp[i]=-1;
	}
	
	
	/****************helper functions************************/
	/*i和j是对应的数组下标位置*/
	private boolean greater(int i,int j){
		return ((Comparable<Key>)keys[pq[i]]).compareTo(keys[pq[j]]) >0 ;
	}
	
	/*,*/
	/**
	 * 交换下标对应的索引号和键元素
	 * 例如，5和6两位置对应索引号为1和2，交换后对应索引号为1和2，即此时pq[5]=2,pq[6]=1,但还需要更新索引对应的下标位置
	 * qp[pq[5]]=5,qp[pq[6]]=6
	 */
	private void swap(int i,int j){
		int temp=pq[i]; //交换两下标位置对应的索引号
		pq[i]=pq[j];
		pq[j]=temp;
		
		qp[pq[i]]=i;//更新qp对应的下标位置
		qp[pq[j]]=j;
	}
	
	/*由下至上的上浮*/
	private void swim(int k){
		while(k>1 && greater(k/2,k)) {
			swap(k/2,k);
			k=k/2;
		}
	}
	
	private void sink(int k){
		while(2*k <=N){
			int j=2*k;
			if(j<N && greater(j,j+1)) j++;
			if(!greater(k,j)) break;
			swap(k,j);
			k=j;
		}
	}
	/*********************************************************/
	/***************iterator functions************************/
	@Override
	public Iterator<Integer> iterator() {
		return new HeapIterator();
	}
	
	private class HeapIterator implements Iterator<Integer>{
		private IndexMinPQ<Key> cur;
		
		public HeapIterator(){
			cur=new IndexMinPQ<Key>(pq.length-1);
			for(int i=1;i<=N;i++)
				cur.insert(pq[i], keys[pq[i]]);
		}
		
		@Override
		public boolean hasNext() {
			return !cur.isEmpty();
		}

		@Override
		public Integer next() {
			if(!hasNext()) throw new NoSuchElementException();
			return cur.delMin();
		}

		@Override
		public void remove() {
			throw new UnsupportedOperationException();
			
		}
		
	}
	/*********************************************************/
	


	public static void main(String[] args) {
		String[] strings = { "it", "was", "the", "best", "of", "times", "it", "was", "the", "worst" };

        IndexMinPQ<String> pq = new IndexMinPQ<String>(strings.length);
        for (int i = 0; i < strings.length; i++) {
            pq.insert(i, strings[i]);
        }
        // delete and print each key
        while (!pq.isEmpty()) {
            int i = pq.delMin();
            StdOut.println(i + " " + strings[i]);
        }
        StdOut.println();
        
        
        for(int i=0;i<strings.length;i++)
        	pq.insert(i, strings[i]);
        for(Integer i: pq)
        	 StdOut.println(i + " " + strings[i]);
        
        while(!pq.isEmpty())
        	pq.delMin();
        StdOut.println(pq.size());
        
    }

	

}
