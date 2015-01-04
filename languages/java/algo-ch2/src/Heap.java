import com.stdlib.*;

public class Heap {
	@SuppressWarnings("rawtypes")
	public static void sort(Comparable[] a){
		int N=a.length;
		buildMaxHeap(a);//Stage 1,建立最大堆
		while(N > 1){  //Stage2，下沉排序中销毁堆
			swap(a,1,N--);//只需要交换N-1次，N=2时前N-1个已经排好序
			sink(a,1,N);
		}
	}
	
	/*构造堆，不适宜从左向右向堆中添加元素，使用自底向上的方法建堆*/
	@SuppressWarnings("rawtypes")
	public static void buildMaxHeap(Comparable[] a) {
		int N=a.length;
		for(int i=N/2;i>=1;i--)
			sink(a,i,N);
	}
	
	@SuppressWarnings("rawtypes")
	public static void sink(Comparable[] a,int k,int N){
		while(2*k <= N){
			int j=2*k;
			if(j <N && less(a,j,j+1)) j++;
			if(!less(a,k,j)) break;
			swap(a,k,j);
			k=j;
		}
	}
	
	/*堆中标号为i的元素对应数组位置为i-1的元素，堆从1开始算起*/
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public static boolean less(Comparable[] a,int i,int j){
		return a[i-1].compareTo(a[j-1])<0;
	}
	
	/*同上，堆中元素交换分别对应下标小1的数组元素交换*/
	@SuppressWarnings("rawtypes")
	public static void swap(Comparable[] a,int i,int j){
		Comparable temp=a[i-1];
		a[i-1]=a[j-1];
		a[j-1]=temp;
	}
	

	public static void main(String[] args) {
	   In input=new In("tiny.txt");
	   String[] a=input.readAllStrings();
	   Heap.sort(a);
	   for(int i=0;i<a.length;i++)
		   StdOut.println(a[i]);

	}

}
