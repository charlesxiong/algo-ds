package algo.basic;
import java.util.*;

/**
 * 
 * @author charles
 * 泛型的FIFO队列实现
 * 
 */
public class LinkedQueue<Item> implements Iterable<Item> {
	private Node first;
	private Node last;
	private int N;
	private class Node {
		Item item;
		Node next;
	}
	
	/*初始化空FIFO队列*/
	public LinkedQueue() {
		first=null;
		last=null;
		N=0;
	}
	
	public boolean isEmpty(){
		return first==null;
	}
	
	public int size(){
		return N;
	}
	

	
	public Item peek(){
		if(isEmpty()) throw new NoSuchElementException("队列为空");
		return first.item;
	}
	
	/*入队，从尾部插入，*/
	public void enqueue(Item item){
		/*修改last节点，当队列为空，同时也需要修改first指针*/
		Node prev=last;
		last=new Node();//开辟一个新节点
		last.item=item;
		last.next=null;
		if(isEmpty()) first=last;
		else prev.next=last;//重新链接上旧的尾节点
		N++;
	}
	
	/*出队，从头部删除*/
	public Item dequeue(){
		/*修改first节点，当队列为空，同时也需要修改last指针*/
		if(isEmpty()) throw new NoSuchElementException("队列为空");
		Item item=first.item;
		first=first.next;
		if(isEmpty()) last=null;
		N--;
		return item;
	}
	
	@Override
	public Iterator<Item> iterator() {
		// TODO Auto-generated method stub
		return new ListIterator();
	}
	
	private class ListIterator implements Iterator<Item>{
		private Node cur=first;
		@Override
		public boolean hasNext() {
			return cur!=null;
		}

		@Override
		public Item next() {
			 if (!hasNext()) throw new NoSuchElementException();
	         Item item = cur.item;
	         cur=cur.next; 
	         return item;
			}

		@Override
		public void remove() {
			throw new UnsupportedOperationException();
		}
	}
	
	public String toString(){
		StringBuilder sb=new StringBuilder();
		for(Item item: this)
			sb.append(item+" ");
		return sb.toString();
	}
	
	public static void main(String[] args) {
		LinkedQueue<String> lq=new LinkedQueue();
		lq.enqueue("hello");
		lq.enqueue("world");
		lq.enqueue("panda");
		System.out.println(lq);
		lq.dequeue();
		System.out.println(lq);
		lq.enqueue("great");
		System.out.println(lq);
	}

	

}
