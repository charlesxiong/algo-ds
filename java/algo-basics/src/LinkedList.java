import java.util.*;
import com.stdlib.*;

/**
 * 
 */

/**
 * @author charles
 *
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
	}
	
	public Node removeAtHead(){
		if(first==null) 
			throw new NoSuchElementException("不能删除空链表");
		else {//非空链表
			Node node=first;
			first=first.next;
			return node;
		} 
	}
	
	public Node removeAtEnd(){
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
					
				}
				Node node=last;
				prev.next=null;
				return node;
		}
	}
	
	
	public void print_node(){
		for(Node temp=first;temp!=null;temp=temp.next)
			StdOut.println(temp.item);
	}

	@Override
	public Iterator<Item> iterator() {
		// TODO Auto-generated method stub
		return null;
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
		ll.print_node();
		StdOut.println(ll.removeAtHead().item);;
		//ll.print_node();
	}

	


}
