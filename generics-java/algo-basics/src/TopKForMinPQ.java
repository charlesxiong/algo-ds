import com.stdlib.*;

/**
 * TopK应用：有时候我们会遇到处理海量数据比如10亿的数据，想获取其中最大的100个数据。
 * 我们知道通过内存排序海量数据的方法是不可取的，它甚至无法装进内存。这时候只需要维持一个Top K的最小堆，堆顶是K个元素中最小的值
 * 我们无需同时获取所有的数据，只需要从优先队列中取出并处理一部分，再根据结果决定新数据是否加入优先队列
 * 
 * 解题思路
 * 如果优先队列大小小于K时，直接插入新数据；否则，比较新数据与当前堆顶元素数据，小于等于不作任何处理，大于替换当前堆顶元素，执行自顶向下的堆序化操作
 * 相比算法教科书提供的用例，它的实现有一个缺点是先插入一个元素再根据情况删除一个不必要的元素，没有上面思路简洁
 * @author charles
 *
 */

public class TopKForMinPQ {
	
	public static void TopKTransactions(){
		 int K=StdIn.readInt();
		 In input=new In("tinyBatch.txt");
		 MinPQ<Transaction> pq=new MinPQ<Transaction>(K+1); //按默认：Amount比较排序
		 //MinPQ<Transaction> pq=new MinPQ<Transaction>(K+1,new Transaction.WhoOrder()); //按顾客比较排序
		 //MinPQ<Transaction> pq=new MinPQ<Transaction>(K+1,new Transaction.WhenOrder()); //按日期比较排序
		 //MinPQ<Transaction> pq=new MinPQ<Transaction>(K+1,new Transaction.AmountOrder()); //按Amount比较排序
		 
		  Stopwatch timer=new Stopwatch();
		  while(input.hasNextLine()){
	    	 String line=input.readLine(); 
	    	 Transaction item=new Transaction(line);
	    	    	
		    /**
		     * 始终多插入了一个元素然后再移除一个最小元素，不可取
		     * K=5时完成TopK需要0.007s,如果处理的数据集更大，则所需时间更长
		     */
//		    pq.insert(item);
//		    if(pq.size()>K)
//		    	pq.delMin();
		     	
		    /**
		     * 始终保持优先级队列中只有K个元素，只有当新元素比当前最小元素更大才替换当前堆顶元素
		     * K=5时完成TopK需要0.006-0.009s，在处理更大的数据集花费时间随即显示出优势
		     */
		    if(pq.size() < K)
		    	pq.insert(item);
		    else if(pq.greater(item,pq.minimum())) { 
		    	pq.increaseTopKey(item);
		    } 
		 }
		 StdOut.println(timer.elapsedTime());
		 StdOut.println();
		    
		 for(Transaction t: pq)
		    StdOut.println(t);
    }
	
	/*8K和1M的数据集*/
	public static void TopKInteger(){
		 int K=StdIn.readInt();
		 MinPQ<Integer> pq=new MinPQ<Integer>(K+1);
		 In input=new In("8Kints.txt");
		 Stopwatch timer=new Stopwatch();
		 while(!input.isEmpty()){
	    	    int m=input.readInt();
		    	Integer item=new Integer(m);
		    	
		    	/**
		    	 * 始终多插入了一个元素然后再移除一个最小元素，不可取 -8K的数据
		    	 * K=5时完成TopK大致需要0.192s,K=10时需要0.190s左右，K=20需要0.199s
		    	 * K=50需要0.19xs,K=100需要0.200s左右
		    	 */
//		    	pq.insert(item);
//		    	if(pq.size()>K)
//		    		pq.delMin();
		    	
		    	/**
		    	 * 始终保持优先级队列中只有K个元素，只有当新元素比当前最小元素更大才替换当前堆顶元素
		    	 * K=5时完成TopK需要0.186s，K=10需要0.181s左右，K=20需要0.180s
		    	 * K=50需要0.180s，K=100需要0.182s左右
		    	 */
		    	if(pq.size() < K)
		    		pq.insert(item);
		    	else if(pq.greater(item,pq.minimum())) { 
		    		pq.increaseTopKey(item);
		    	} 
		    	
		    }
		    StdOut.println(timer.elapsedTime());
		    StdOut.println();
		    
		  
		    for(Integer t: pq)
		    	StdOut.println(t);
	}
	public static void main(String[] args) {
	    //TopKTransactions();
	    TopKInteger();
	    
	    
	}

}
