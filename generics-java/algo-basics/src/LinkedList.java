import java.util.*;

/**
 * 
 */

/**
 * @author charles
 * 泛型的单链表实现
 */
public class LinkedList<Item> implements Iterable<Item> {
	private Node first;//链表头节点
	private int N=0; //列表中的元素
	
	private class Node {
		Item item;
		Node next;
	}
	
	/**
	 * 初始化空列表
	 */
	public LinkedList() {
		first=null;
		N=0;
	}
	
	public boolean isEmpty(){
		return first==null;
	}
	
	public int size(){
		return N;
	}
	
	public void insertAtHead(Item x){
		Node oldfirst=first;
		Node cur=new Node();
		cur.item=x;
		cur.next=oldfirst;
		first=cur;
		N++;
	}
	
	public void insertAtEnd(Item x){
		if(first==null){ //空链表，插入的尾元素为首节点
			Node cur=new Node();
			cur.item=x;
			cur.next=null;
			first=cur;
		} else{ // 非空链表，遍历到链表中最后一个节点执行插入
			 Node temp=first;
			 while(temp.next!=null){
				 temp=temp.next;
			 } //退出时找到链表中最后一个节点
			 
			 Node cur=new Node();
			 cur.item=x;
			 cur.next=null;
			 temp.next=cur;
		}
		N++;
	}
	
	public void removeAtHead(){
		if(first==null) 
			throw new NoSuchElementException("不能删除空链表");
		else {//非空链表
			Node node=first;
			first=first.next;
			N--;
		} 
	}
	
	public void removeAtEnd(){
		if(first==null) 
			throw new NoSuchElementException("不能删除空链表");
		else {
				Node last=first;
				Node prev=null;
				while(last.next!=null){
					prev=last;
					last=last.next;
				} //找到尾节点及尾节点的前一个节点
				if(prev==null){ //只有一个节点
					first=null;
				} else{
					prev.next=null;
				}
				N--;
				
		}
	}
	
	/*删除链表中的第k个节点，如果存在的话*/
	public void removeAtkPos(int k){
		if(k<=0 || k>N)
			throw new IllegalArgumentException("k必须在１－Ｎ范围内！");
		
		int num=1;//计数初始为１
		Node cur=first;
		/*找到第k-1个节点*/
		while(cur!=null && num < k-1) {
			cur=cur.next;
			num++;
		}//返回的cur即第k－１个节点
		cur.next=cur.next.next;
		N--;
	}
	
	/*查找第k个节点，如果存在的话*/
	public Node find(int k){
		if(k<=0 || k>N)
			throw new IllegalArgumentException("k必须在１－Ｎ范围内！");
		int num=0;
		Node cur=first;
		while(cur!=null){
			num++;
			if(num==k)
				break;
			cur=cur.next;
		}
		return cur;
	}
	
	/*查找链表中某节点的数据域是否存在给定值，若存在，返回true,否则返回false*/
	public boolean find(Item key){
		boolean result=false;
		Node cur=first;
		while(cur!=null){
			if(cur.item==key){
				result=true;
				break;
			}
			cur=cur.next;
		}
		return result;
	}

	@Override
	public Iterator<Item> iterator() {
		
		return new LinkedListIterator();
	}
	
	private class LinkedListIterator implements Iterator<Item> {
		private Node cur=first;
		@Override
		public boolean hasNext() {
			return cur!=null;
		}

		@Override
		public Item next() {
			if(!hasNext()) throw new NoSuchElementException();
			Item key=cur.item;
			cur=cur.next;
			return key;
		}

		@Override
		public void remove() {
			throw new UnsupportedOperationException();
		}
		
	} 
	
	
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		LinkedList<String> ll=new LinkedList<String>();
		ll.insertAtHead("to");
		ll.insertAtHead("hello");
    	ll.insertAtEnd("world");
		ll.insertAtEnd("i");
		ll.insertAtEnd("to");
		ll.insertAtEnd("hello");
		for(String i: ll)
			System.out.println(i);
		ll.removeAtkPos(3);
		for(String i: ll)
			System.out.println(i);
	}

	


}
