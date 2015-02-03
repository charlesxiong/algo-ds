import java.util.*;

import com.stdlib.*;


/**
 *  利用动态数组实现栈
 *  Java中有Stack,是宽接口，定义了很多不适合栈的方法，不建议使用
 *  以API作为设计高效算法和数据结构的起点，因而设计只含有几个操作的接口明显比设计含有许多操作的接口更简单
 *  坚持窄接口的设计，限制用例代码的行为
 * @author charles
 *
 */
public class ResizingArrayStack<Item> implements Iterable<Item> {
	private Item[] a;
	private int N; //元素个数

	public ResizingArrayStack() {
		a=(Item[])new Object[2];
		N=0;
	}
	
	public boolean isEmpty(){
		return N==0;
	}
	
	public int size(){
		return N;
	}
	
	private void resize(int capacity){
		assert capacity >=N;
		Item[] temp=(Item[]) new Object[capacity];
		for(int i=0;i<N;i++)
				temp[i]=a[i];
		a=temp;
	}
	
	public void push(Item item){
		if(N==a.length) resize(2*a.length);
		a[N++]=item;
	}
	
	public Item pop(){
		if(isEmpty()) throw new NoSuchElementException("栈为空！");
		Item key=a[--N];
		a[N]=null; //避免对象游离
		if(N>=0 && N==a.length/4) resize(a.length/2);
		return key;
	}
	
	public Item peek(){
		if(isEmpty()) throw new NoSuchElementException("栈为空！");
		return a[N-1];
	}

	
	/*******************迭代器实现***********************/
	@Override
	public Iterator<Item> iterator() {
		return new ReverseArrayIterator();
	}
	
	private class ReverseArrayIterator implements Iterator<Item>{
		//支持后进先出的迭代
		private int i;
		
		public ReverseArrayIterator(){
			i=N;
		}
		
		@Override
		public boolean hasNext() {
			
			return i>0;
		}

		@Override
		public Item next() {
			if(!hasNext()) throw new NoSuchElementException();
			return a[--i];
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
		ResizingArrayStack<String> s=new ResizingArrayStack<String>();
		In input=new In("tobe.txt");
		while(!input.isEmpty()){
			String item=input.readString();
			if(!item.equals("-"))  s.push(item);
			else if(!s.isEmpty()) StdOut.print(s.pop()+ " ");
		}
		StdOut.println("("+s.size()+" left on stack)");
		
		for(String key: s)
			StdOut.println(key);

	}

	

}
