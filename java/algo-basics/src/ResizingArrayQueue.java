import java.util.*;

import com.stdlib.*;

public class ResizingArrayQueue<Item>  implements Iterable<Item> {
	private Item[] a;
	private int N;//元素个数
	private int front; //队头指针，队列头元素
	private int rear; //队尾指针，下一个有效队尾位置
	
	@SuppressWarnings("unchecked")
	public ResizingArrayQueue() {
		a=(Item[])new Object[2];
		N=0;
		front=0;
		rear=0;
	}
	
	public boolean isEmpty(){
		return N==0;
	}
	
	public int size(){
		return N;
	}
	
	
	@SuppressWarnings("unchecked")
	private void resize(int capacity){
		assert capacity >=N;
		Item[] temp=(Item[])new Object[capacity];
		for(int i=0;i<N;i++)
			temp[i]=a[(front+i)% a.length];
		a=temp;
		front=0;
		rear=N;
	}
	
	public void enqueue(Item item){
		if(N==a.length) resize(a.length*2);
		a[rear++]=item;
		rear=rear%a.length;
		N++;
		//if(rear==a.length) rear=0; //当到达数组的尾部时，重新指向下一个
	}
	
	public Item dequeue(){
		if(isEmpty()) throw new NoSuchElementException("队列为空");
		 Item key=a[front++];
		 a[front-1]=null;//防止对象游离
		 front=front%a.length; //重新回到下标为0的位置
		 N--;
		 if(N>0 && N==a.length/4) resize(a.length/2);
		 return key;
	}
	
	public Item peek(){
		if(isEmpty()) throw new NoSuchElementException("队列为空");
        return a[front];
	}
	
	@Override
	public Iterator<Item> iterator() {
		// TODO Auto-generated method stub
		return new ArrayIterator();
	}
	
	private class ArrayIterator implements Iterator<Item>{
		private int i=0;
		
		@Override
		public boolean hasNext() {
			return i <N;
		}

		@Override
		public Item next() {
			if(!hasNext()) throw new NoSuchElementException();
			Item key=a[(front+i)%a.length];
			i++;
			return key;
		}

		@Override
		public void remove() { //不支持删除操作
			throw new UnsupportedOperationException();
		}
		
	}
	
	
	
	

	public static void main(String[] args) {
		ResizingArrayQueue<String> q=new ResizingArrayQueue<String>();
		while(!StdIn.isEmpty()){
			String item=StdIn.readString();
			if(!item.equals("-"))  q.enqueue(item);
			else if(!q.isEmpty()) StdOut.print(q.dequeue()+ " ");
		}
		StdOut.println("("+q.size()+" left on stack)");
	}

	

}
