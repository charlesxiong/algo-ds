package algo.search;

import com.stdlib.In;
import com.stdlib.StdOut;

import algo.basic.LinkedQueue;

public class LinearProbingHashST<Key,Value> {
	private static final int INIT_CAPACITY=4;
	
	private int N; //键值对个数
	private int M; //线性探测表的大小
	private Key[] keys;
	private Value[] vals; //维护键-值两数组实际存放的键值
	
	
	public LinearProbingHashST() {
		this(INIT_CAPACITY);
	}
	
	/**
	 * 用大小为M的散列表保存N个键值对，其中M>N
	 * 我们要依靠数组中的空位解决碰撞冲突：有线性探测、二次探测等解法
	 * 基于这种策略的所有方法统称为开放地址散列表
	 * @param M
	 */
	@SuppressWarnings("unchecked")
	public LinearProbingHashST(int M) {
		this.M=M;
		keys=(Key[])new Object[M];
		vals=(Value[])new Object[M];
	}
	
	public int size(){
		return this.N;
	}
	
	public boolean isEmpty(){
		return N==0;
	}
	
	/*散列表是否存在该键值对*/
	public boolean contains(Key key){
		return get(key)!=null;
	}
	
	/**
	 * 动态调整散列表数组的大小，保证线性探测的散列表的使用率永远都不会超过1/2
	 * 
	 * 在put方法中，一旦使用率N/M达到1/2，立即将散列表的大小扩容1倍
	 * 在delete方法中，为防止散列表空间过于浪费，只要使用率降到了1/8,立即将散列表大小缩小1倍
	 * 
	 * 保证散列表最多处于半满状态，使用率不超过1/2(使用的内存量和表中的键值对数组比例控制在一定范围内)
	 * 命题：当使用率约为1/2，查找命中需要的探测次数约为3/2，未命中所需要的约为5/2((探测的预计次数在1.5和2.5)
	 * 越接近于1，探测次数越来越大
	 */
	private void resize(int cap){
		LinearProbingHashST<Key,Value> temp=new  LinearProbingHashST<Key,Value>(cap);
		for(int i=0;i<M;i++){
			if(keys[i]!=null){
				temp.put(keys[i], vals[i]);
			}
		}
		this.M=cap;
		this.keys=temp.keys;
		this.vals=temp.vals;
	}
	
	private boolean check(){
		if(M<2*N){
			System.err.println("Hash table size M= "+M+ "; array size N= "+N);
			return false;
		}
		
		//检测每个键是否能被找到
		for(int i=0;i<M;i++){
			if(keys[i]==null) continue;
			else if(get(keys[i])!=vals[i]){
				System.err.println("get[" + keys[i] + "] = " + get(keys[i]) + "; vals[i] = " + vals[i]);
			}
		}
		return true;
	}
	
	private int hash(Key key){
		return (key.hashCode() & 0x7fffffff)% M;
	}
	
	/*查找该键是否存在，从键对应的散列索引开始判断,若找到返回对应值否则返回null*/
	public Value get(Key key){
		for(int i=hash(key);keys[i]!=null;i=(i+1)%M){
			if(key.equals(keys[i]))
				return vals[i];
		}
		return null;
	}
	
	/**
	 * 如果线性探测命中要查找的键的话，更新当前键对应的的值
	 * 如果未命中，即为空，在空位置插入该键值对
	 */
	public void put(Key key,Value val){
		if(val==null){ //值为空，相当于删除当前键值对
			delete(key);
			return;
		}
		//最多保持半满状态
		if(N >=M/2) resize(2*M);
		int i;		
		for(i=hash(key);keys[i]!=null;i=(i+1)%M){ 
			if(key.equals(keys[i])){
				vals[i]=val;
				return ;
			}
		}
		keys[i]=key;
		vals[i]=val;
		N++;
	}
	
	/**
	 * 删除指定的键: 首先找到对应的散列索引位置
	 * 由于该键可能存储在这一簇键的某个位置，首先需要遍历到该键的位置，将其置为NULL
	 * 然后再继续下一个位置，判断是否为空，若不空重新更新插入散列表中
	 */
	public void delete(Key key){
		if(!contains(key)) return ;
		int i=hash(key);
		while(!key.equals(keys[i])){
			i=(i+1)% M;
		}
		keys[i]=null;
		vals[i]=null;
		i=(i+1)%M;
		while(keys[i]!=null){
			Key keyRedo=keys[i];
			Value valRedo=vals[i];
			keys[i]=null;
			vals[i]=null;
			N--;
			put(keyRedo,valRedo);
			i=(i+1)%M;
		}
		N--;
		if(N>0&&N==M/8) resize(M/2); 
		check();
	}
	
	public Iterable<Key> keys(){
		LinkedQueue<Key> queue=new LinkedQueue<Key>();
		for(int i=0;i<M;i++){
			if(keys[i]!=null)
				queue.enqueue(keys[i]);
		}
		return queue;
		
	}
	
	
	public static void main(String[] args) {
		LinearProbingHashST<String,Integer> st=new LinearProbingHashST<String,Integer>();
		In input=new In("tiny.txt");
		for(int i=0;!input.isEmpty();i++){
			String key=input.readString();
			st.put(key, i);
		}
		
		for(String s: st.keys())
			StdOut.println(s+ " "+st.get(s));

	}

}
