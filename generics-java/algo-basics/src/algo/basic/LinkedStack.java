package algo.basic;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * 
 * @author charles
 *
 * 泛型的LIFO栈实现
 */
public class LinkedStack<Item> implements Iterable<Item> {
	private Node first;
	private int N;
	
	private class Node {
		Item item;
		Node next;
	}
	public LinkedStack() {
		first=null;
		N=0;
	}
	
	
	
	public  boolean isEmpty(){
		return first==null;
	}
	
	public int size(){
		return N;
	}
	

	
	public Item peek(){
		if(isEmpty()) throw new NoSuchElementException("栈为空");
		return first.item;
	}
	
	/*入队，从头部插入*/
	public void push(Item item){
		Node prev=first;
		first=new Node();
		first.item=item;
		first.next=prev;
		N++;
	}
	
	public Item pop(){
		if(isEmpty()) throw new NoSuchElementException("栈为空");
		Item item=first.item;
		first=first.next;
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
		LinkedStack ls=new LinkedStack();
		ls.push("hello");
		ls.push("world");
		System.out.println(ls);
		ls.pop();
		System.out.println(ls);

	}

	

}
