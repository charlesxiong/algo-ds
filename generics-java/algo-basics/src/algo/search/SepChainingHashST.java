package algo.search;

import com.stdlib.In;
import com.stdlib.StdIn;
import com.stdlib.StdOut;

import algo.basic.LinkedQueue;

public class SepChainingHashST<Key,Value> {
	private static final int INIT_CAPACITY=7;
	private int N; //键值对总数
	private int M; //散列表大小
	
	private SeqSearchST<Key,Value>[] st;//存放链表对象的数组
	
	public SepChainingHashST() {
		this(INIT_CAPACITY);
	}
	
	/*创建包含M个链表的开链散列表*/
	public SepChainingHashST(int M){
		this.M=M;
		st=(SeqSearchST<Key,Value>[])new SeqSearchST[M];
		for(int i=0;i<M;i++)
			st[i]=new SeqSearchST();
	}
	
	/*给定链表个数slots,动态调整链表数组的大小,再重新哈希所有的键值*/
	private void resize(int slots){
		SepChainingHashST<Key,Value> temp=new SepChainingHashST<Key,Value>(slots);
		/*重新散列值*/
		for(int i=0;i<M;i++)
			for(Key key: st[i].keys())
				temp.put(key, st[i].get(key));
		this.M=temp.M;
		this.N=this.N;
		this.st=temp.st;
	}
	
	/*返回散列表的键值对*/
	public int size(){
		return N;
	}
	
	/*散列表是否为空*/
	public boolean isEmpty(){
		return N==0;
	}
	
	/*散列函数:将键值映射到散列表的某个slot中: 0-M-1*/
	private int hash(Key key){
		return (key.hashCode() & 0x7fffffff)%M;
	}
	
	/*返回对应键的值*/
	public Value get(Key key){
		int slot=hash(key);
		return st[slot].get(key);
	}
	
	public boolean contains(Key key){
		return get(key)!=null;
	}
	
	
	public void put(Key key,Value val){
		if(val==null){
			delete(key);
			return ;
		}
		/*如果平均链表长度>=10,容量增长原来的一倍,保证链表长度最多为5-10*/
		if(N >=10*M) resize(2*M);
		
		/*如果此键值对不存在，则不更新键值对个数，但无论存在与否，均更新插入键值对*/
		int slot=hash(key);
		if(!st[slot].contains(key)) N++; 
		st[slot].put(key,val);
	}
	
	/*如果键在散列表中，更新键值对个数，否则不更新。 然后再删除该键值对。*/
	public void delete(Key key){
		int slot=hash(key);
		if(st[slot].contains(key)) N--;
		st[slot].delete(key);
		
		/*重新散列表中的键值对如果链表平均长度<=2*/
		if(M>INIT_CAPACITY && N<=2*M) resize(M/2);
	}
	
	public Iterable<Key> keys(){
		LinkedQueue<Key> queue=new LinkedQueue<Key>();
		for(int i=0;i<M;i++)
			for(Key key: st[i].keys())
				queue.enqueue(key);
		return queue;
	}

	public static void main(String[] args) {
		SepChainingHashST<String,Integer> st=new SepChainingHashST<String,Integer>();
		
//		/*命令行输入*/
//		for(int i=0;!StdIn.isEmpty();i++){
//			String key=StdIn.readString();
//			st.put(key, i);
//		}
		
		/*文件读取*/
		
		In input=new In("tiny.txt");
		for(int i=0;!input.isEmpty();i++){
			String key=input.readString();
			st.put(key, i);
		}
		
		for(String s: st.keys())
			StdOut.println(s+ " "+st.get(s));
		
		

	}

}
