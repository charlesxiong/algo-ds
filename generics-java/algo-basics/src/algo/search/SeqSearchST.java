package algo.search;

import java.util.Queue;

import com.stdlib.*;

import algo.basic.LinkedQueue;

public class SeqSearchST<Key,Value> {
	private int N; //键值对个数
	private Node first;
	
	/*内置的链表节点类，每个节点含有一个键值对和一个指向下一个节点指针*/
	private class Node {
		private Key key;
		private Value val;
		private Node next;
		
		public Node(Key key,Value val,Node next){
			this.key=key;
			this.val=val;
			this.next=next;
		}
	}
	
	/*初始化空符号表*/
	public SeqSearchST() {
		
	}
	
	public int size(){
		return N;
	}
	
	public boolean isEmpty(){
		return N==0;
	}
	
	/*返回键为key的值*/
	public Value get(Key key){
		for(Node x=first;x!=null;x=x.next)
			if(key.equals(x.key)) return x.val;
		return null;
	}
	
	/*该符号表包含这个键么*/
	public boolean contains(Key key){
		return get(key)!=null;
	}
	
	public void put(Key key,Value val){
		if(val==null){
			delete(key); return;
		}
		/*先判断该键是否存在，若存在直接用新值更新*/
		for(Node x=first;x!=null;x=x.next)
			if(key.equals(x.key)) {
				x.val=val;
				return;
			}
		/*直接头部插入*/
		first=new Node(key,val,first);
		N++;
	}
	
	/*从符号表中移除该键值*/
	public void delete(Key key){
		first=delete(first,key);
	}
	
	/*在以节点x开始的链表中删除键key*/
	public Node delete(Node x,Key key){
		if(x==null) return null;
		if(key.equals(x.key)){
			N--;
			return x.next;
		}
		x.next=delete(x.next,key); //采用递归方式递归删除
		return x;
	}
	
	public Iterable<Key> keys(){
		LinkedQueue<Key> queue=new LinkedQueue<Key>();
		for(Node x=first;x!=null;x=x.next)
			queue.enqueue(x.key);
		return queue;
	}

	/** tiny.txt
	 * S E A R C H E X A M P L E
	 */
	public static void main(String[] args) {
		SeqSearchST<String,Integer> st=new SeqSearchST<String,Integer>();
		for(int i=0;!StdIn.isEmpty();i++){
			String key=StdIn.readString();
			st.put(key, i);
		}
		for(String s:st.keys())
			StdOut.println(s+" "+st.get(s));
	}

}
