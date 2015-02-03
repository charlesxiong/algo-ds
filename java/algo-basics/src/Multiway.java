import com.stdlib.*;

public class Multiway {
	public static void merge(In[] streams){
		int N=streams.length;
		IndexMinPQ<String> pq=new IndexMinPQ<String>(N);
		
		for(int i=0;i<N;i++)
			if(!streams[i].isEmpty())
				pq.insert(i, streams[i].readString());
		/** 
		 * 删除并打印出队列中最小的字符串，然后再读入该输入的下一个字符串，始终保持优先队列对应的索引最多为N个，并且不重复
		 */
		while(!pq.isEmpty()){
			StdOut.println(pq.minIndex()+ " - " +pq.minimum());
			int i=pq.delMin();
			if(!streams[i].isEmpty())
				pq.insert(i, streams[i].readString());
		}
				
	}
	
	/**
	 * 多向归并问题：将多个有序的输入流归并成一个有序的输出流
	 * 很多应用都会遇到这个问题，例如输入来自多种科学仪器的输出(按时间排序)，来自多个音乐或电影网站的信息列表(按艺术家或名字排序)
	 * 或是商业交易(按照账号或时间排序)
	 * 若有足够的空间，可一次性将它读入数组中并排序(多项归并)；使用索引优先队列，无论输入多长，始终能够把它全部读入并排序
	 * 要求多个输入流必须是有序的
	 */
	public static void main(String[] args) {
		String[] filenames={"m1.txt","m2.txt","m3.txt"};
		int N=filenames.length;
		In[] input=new In[N];
		for(int i=0;i<N;i++)
			input[i]=new In(filenames[i]);
		merge(input);

	}

}
