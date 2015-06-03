package algo.search;

import java.util.NoSuchElementException;

import com.stdlib.In;
import com.stdlib.StdIn;
import com.stdlib.StdOut;

import algo.basic.LinkedQueue;

public class BinSearchST<Key extends Comparable<Key>,Value>  {
	private static final int INIT_CAPACITY=2;
	private Key[] keys;
	private Value[] vals;
	private int N; //键值对个数
	
	public BinSearchST(int capacity) {
		keys=(Key[]) new Comparable[capacity];
		vals=(Value[]) new Object[capacity];
		N=0;
	}
	
	public BinSearchST(){
		this(INIT_CAPACITY);
	}
		
	public int size(){
		return N;
	}
	
	public boolean isEmpty(){
		return N==0;
	}
	
	public boolean contains(Key key){
		return get(key)!=null;
	}
	
	/**
	 * 如果符号表为空，返回null
	 * 找到key的排名rank,如果位置合法并且给定的键值与对应位置的键值相等，返回对应的实值
	 * 否则返回null
	 */
	public Value get(Key key){
		if(isEmpty()) return null;
		int pos=rank(key);
		if(pos<N && key.compareTo(keys[pos])==0) return vals[pos];
		return null;
	}
	
	/**
	 * 插入键值对，查找键找到就更新值，后面的元素整体右移结点个数加1
	 */
	public void put(Key key,Value val){
		if(val==null){
			delete(key);
			return;
		}
		/*小于key的键的数量，*/
		int i=rank(key);
		
		/*如果键在表中，更新键值对*/
		if(i<N&&key.compareTo(keys[i])==0){
			vals[i]=val;
			return ;
		}
		
		/*元素个数已满，等于容量大小*/
		if(N==keys.length) resize(2*keys.length);
		
		for(int j=N;j>i;j--){
			keys[j]=keys[j-1];
			vals[j]=vals[j-1];
		}
		keys[i]=key;
		vals[i]=val;
		N++;
		
		assert check();
	}
	
	public void delete(Key key){
		if(isEmpty()) return;
		int i=rank(key);
		if(i==N ||key.compareTo(keys[i])!=0){
			return ;
		}
		
		for(int j=i;j<N-1;j++){
			keys[j]=keys[j+1];
			vals[j]=vals[j+1];
		}
		N--;
		keys[N]=null;
		vals[N]=null;
		
		if(N>=0&& N==keys.length/4) resize(keys.length/2);
		
		assert(check());
	}
	
	/*********************************
	 * 有序性操作:
	 * 最大键、最小键(删除最大、最小键)
	 * 对于给定的键，向下取整(floor)操作: 找出小于等于该键的最大键
	 * 对于给定的键，向上取整(ceiling)操作: 找出大于等于该键的最小键
	 * 排名操作(rank): 找出小于指定键的键的数量
	 * 选择操作(select): 找出排名为k的键
	 * 范围查找: 在两个给定的键之间有多少键，分别是哪些 
	 *********************************/
	
	/**
	 * rank采用了类似于二分查找的操作，rank返回的范围是0..N
	 * 如果表中存在该键,rank()应该返回该键的位置，也就是表中小于该键的数量
	 * 如果不存在该键，rank()还是应该返回表中小于它的键的数量
	 */
	public int rank(Key key){
		int low=0,high=N-1;
		while(low<=high){
			int mid=low+ (high-low)/2;
			int cmp=key.compareTo(keys[mid]);
			if(cmp<0) high=mid-1;
			else if(cmp>0) low=mid+1;
			else return mid;
		}
		return low;
	}
	
	public Key select(int i){
		if(i<0 || i>=N) return null;
		return keys[i];
	}
	
	public Key min(){
		if(isEmpty()) return null;
		return keys[0];
	}
	
	public Key max(){
		if(isEmpty()) return null;
		return keys[N-1];
	}
	
	/**
	 * floor、ceiling、rank()-最多是对数级别的操作
	 * rank()- 找到键的排名
	 * select(): 取排名为k的键(O(1)复杂度)
	 * @param key
	 * @return
	 */
	/*取大于或等于它的最小键，要么是当前的键或者应该插入的位置()*/
	public Key ceiling(Key key){
		int i=rank(key);
		if(i==N) return null;
		return keys[i];
	}
	
	/*取小于或等于该键的最大键*/
	public Key floor(Key key){
		int i=rank(key);
		if(i<N && key.compareTo(keys[i])==0)
			return keys[i];
		if(i==0) return null; //取小于首元素的最大键，必然是null
		return keys[i-1]; //常规是小于当前键的最大键
	}
	
	
	public void deleteMin(){
		if(isEmpty()) throw new NoSuchElementException("符号表下溢错误!");
		delete(min());
	}
	
	public void deleteMax(){
		if(isEmpty()) throw new NoSuchElementException("符号表下溢错误!");
		delete(max());
	}
	
	/*[low..high]的键已排好序*/
	public int size(Key low,Key high){
		if(low.compareTo(high)>0) return 0;
		if(contains(high)) return rank(high)-rank(low)+1;
		else 	return rank(high)-rank(low);
	}
	
	/*表中的所有键的集合，已排序*/
	public Iterable<Key> keys(){
		return keys(min(),max());
	}
	
	/*[low..high]之间的所有键，已排序*/
	public Iterable<Key> keys(Key lo,Key hi){
		LinkedQueue<Key> queue=new LinkedQueue<Key>();
		if(lo==null&&hi==null) return queue;
		if(lo==null|| hi==null) throw  new NoSuchElementException("某键不存在");
		if(lo.compareTo(hi)>0) return queue;
		
		for(int i=rank(lo);i<rank(hi);i++)
			queue.enqueue(keys[i]);
		if(contains(hi)) queue.enqueue(keys[rank(hi)]);
		return queue;
	}
	
	private void resize(int capacity){
		assert capacity>=N;
		Key[] keysTemp=(Key[]) new Comparable[capacity];
		Value[] valsTemp=(Value[]) new Object[capacity];
		for(int i=0;i<N;i++){
			keysTemp[i]=keys[i];
			valsTemp[i]=vals[i];
		}
		
		keys=keysTemp;
		vals=valsTemp;
	}
	/*********************************
	 * 检查内部不变式
	 *********************************/
	
	private boolean check(){
		return isSorted()&& rankCheck();
	}
	
	private boolean isSorted(){
		for(int i=1;i<N;i++)
			if(keys[i].compareTo(keys[i-1])<0)
				return false;
		return true;
	}
	
	//检查选择第i个位置的键值对应的位置是否为i-rank(select(i))=i
	private boolean rankCheck(){
		for(int i=0;i<size();i++)
			if(i!=rank(select(i))) return false;
		for(int i=0;i<size();i++)
			if(keys[i].compareTo(select(rank(keys[i])))!=0) return false;
		return true;
	}
	
	public static void test(String filename){
		BinSearchST<String,Integer> st=new BinSearchST<String,Integer>();
		In  input=new In(filename);
		int i=0;
		while(!input.isEmpty()){
			String key=input.readString();
			st.put(key,i);
			i++;
		}
		
		for(String s: st.keys()){
			StdOut.println(s+ " "+st.get(s));
		}
		
		String key=st.floor("F");
		StdOut.println("E的向下取整键值对(key-val): "+key+" "+st.get(key));
		StdOut.println(st.rank("E")+" "+st.select(1));
		key=st.ceiling("F");
		StdOut.println("E的向上取整键值对(key-val): "+key+" "+st.get(key));
		
		StdOut.println(st.size("E","P"));
		for(String s: st.keys("E","P")){
			StdOut.println(s+ " "+st.get(s));
		}
	}
	
	public static void computeGPA(){
		BinSearchST<String,Double> st=new BinSearchST<String,Double>();
		st.put("A+", 4.33);
		st.put("A",4.00);
		st.put("A-", 3.67);
		st.put("B+",3.33);
		st.put("B",3.00);
		st.put("B-",2.67);
		st.put("C+",2.33);
		st.put("C",2.00);
		st.put("C-",1.67);
		st.put("D",1.00);
		st.put("F",0.00);
		
		int n=0;
		double total=0.0;
		for(n=0;!StdIn.isEmpty();n++){
			String grade=StdIn.readString();
			total +=st.get(grade);
		}
		double gpa=total/n;
		StdOut.println("GPA = "+ gpa);
	}

	public static void main(String[] args) {
		//test("tiny.txt");
		computeGPA();
	}
}
