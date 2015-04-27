package algo.basic;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 * @author charles
 *
 *  基于链表的背包实现
 */
public class LinkedBag<Item> implements Iterable<Item>{
	private Node first;
	private int N;
	
	private class Node {
		Item item;
		Node next;
	}
	
	public LinkedBag() {
		first=null;
		N=0;
	}
	
	public  boolean isEmpty(){
		return first==null;
	}
	
	public int size(){
		return N;
	}
	
	public void add(Item item){
		Node prev=first;
		first=new Node();
		first.item=item;
		first.next=prev;
		N++;
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
	

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		LinkedBag<String> lb=new LinkedBag();
		lb.add("hello");
		lb.add("world");
		lb.add("i");
		System.out.println(lb);

	}

}
