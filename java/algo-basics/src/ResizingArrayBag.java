import java.util.*;

import com.stdlib.StdIn;
import com.stdlib.StdOut;


/**
 * Resizing Array  Bag/Multiset(利用动态数组实现背包)
 * 背包：不支持删除元素的集合数据类型，帮助用例收集并迭代遍历所收集到的元素
 * 重要API：void add(Item item)- 添加一个元素
 */
public class ResizingArrayBag<Item> implements Iterable<Item> {
	private Item[] a; //表项数组
	private int N; //元素个数
	
	public ResizingArrayBag() {
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
		assert capacity>=N;
		Item[] temp=(Item[])new Object[capacity];
		for(int i=0;i<N;i++)
			temp[i]=a[i];
		a=temp;
	}
	
	public void add(Item item){
		if(N==a.length) resize(2*a.length);
		a[N++]=item;
	}
	
	@Override
	public Iterator<Item> iterator() {
		// TODO Auto-generated method stub
		return new ArrayIterator();
	}
	
	private class ArrayIterator implements Iterator<Item> {
		private int i=0;
		
		@Override
		public boolean hasNext() {
			return i<N;
		}

		@Override
		public Item next() {
			if(!hasNext()) throw new NoSuchElementException();
			return a[i++];
		}

		@Override
		public void remove() {
			throw new UnsupportedOperationException();
		}
		
	}
	
	public static void test(){
		ResizingArrayBag<String> bag=new ResizingArrayBag<String>();
		bag.add("Hello");
		bag.add("World");
		bag.add("how");
		bag.add("are");
		bag.add("you");
		
		for(String s: bag)
			StdOut.println(s);
	}
	
	public static void stats(){
		ResizingArrayBag<Double> numb=new ResizingArrayBag<Double>();
		while(!StdIn.isEmpty()){
			numb.add(StdIn.readDouble());
		}
		int N=numb.size();
		double sum=0.0;
		for(double x: numb)
			sum +=x;
		double mean= sum/N;
		
		sum=0.0;
		for(double x: numb)
			sum += (x-mean)*(x-mean);
		double std=Math.sqrt(sum/(N-1));
		StdOut.printf("Mean: %.2f\n",mean);
		StdOut.printf("Std dev: %.2f\n",std);
		
	}
	
	public static void main(String[] args) {
		test();
		stats();
	}

	

}
