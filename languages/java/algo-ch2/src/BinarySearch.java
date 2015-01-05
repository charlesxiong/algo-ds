import java.util.*;
import com.stdlib.*;

/**
 * 二分查找实现及其应用
 * @author charles
 *
 */
public class BinarySearch {

	public static int rank(int key,int[] a){
		int lo=0;
		int hi=a.length-1;
		while(lo<=hi){
			int mid=lo+(hi-lo) /2;
			if(key< a[mid]) hi=mid-1;
			else if(key> a[mid]) lo=mid+1;
			else return mid;
		}
		return -1;
	}
    
	/*****************题目1： 在N个数中找出三个和为0的整数元组的数量**********************************/
	/**
	 * 在N个数中找出三个和为0的整数元组的数量
	 * 立方级别的暴力算法
	 */
	public static int ThreeSumBruteForce(int[] a){
		int N=a.length;
		int cnt=0;
		for(int i=0;i<N;i++)
			for(int j=i+1;j<N;j++)
				for(int k=j+1;k<N;k++)
					if(a[i]+a[j]+a[k]==0)
						cnt++;
		return cnt;
	}
	
	/**
	 * 在N个数中找出三个和为0的整数元组的数量
	 * 平方对数级别算法N^2*lgN
	 * 要求需要先对数组进行排序，然后再利用有序数组的二分查找进行计算-统计
	 * @return
	 */
	public static int ThreeSumFast(int[] a){
		Arrays.sort(a);
		int N=a.length;
		int cnt=0;
		for(int i=0;i<N;i++)
			for(int j=i+1;j<N;j++)
				if(rank(-a[i]-a[j],a)>j)
					cnt++;
		return cnt;
	}
	
	public static void ThreeSumPrintAll(int[] a){
		Arrays.sort(a);
		int N=a.length;
		int cnt=0;
		for(int i=0;i<N;i++)
			for(int j=i+1;j<N;j++) {
				int k=rank(-a[i]-a[j],a);
				if(k>j) {
					cnt++;
					StdOut.println(cnt+"- "+a[i]+" "+a[j]+" "+a[k]);
				}
			}
	}
	
	public static void testBruteForce(String testName){
		if(testName!=null) {
			StdOut.printf("%s test begins: ",testName);
			StdOut.println();
			In in=new In(testName);
			int[] a=in.readAllInts();
			Stopwatch timer=new Stopwatch();
			StdOut.println(ThreeSumBruteForce(a));
		    StdOut.println("time cost: "+timer.elapsedTime()+"s");
		    //ThreeSumPrintAll(a);
		    StdOut.println();
		}
	}
	
	public static void testFast(String testName){
		if(testName!=null) {
			StdOut.printf("%s test begins: ",testName);
			StdOut.println();
			In in=new In(testName);
			int[] a=in.readAllInts();
			Stopwatch timer=new Stopwatch();
			StdOut.println(ThreeSumFast(a));
		    StdOut.println("time cost: "+timer.elapsedTime()+"s");
		    ThreeSumPrintAll(a);
		    StdOut.println();
		}
	}
	
	public static void testTotal(){
		String[] files={"1Kints.txt","2Kints.txt","4Kints.txt","8Kints.txt","16Kints.txt","32Kints.txt","1Mints.txt"};
		In[] in=new In[files.length];
		for(int i=0;i<in.length;i++)
			in[i]=new In(files[i]);
		int[][] a=new int[in.length][];
		
		for(int i=0;i<in.length;i++){
			a[i]=in[i].readAllInts();
			/**
			 * 使用ThreeSumBruteForce，可以很快在1Kints,2Kints得到这样的整数元组数70,528，4Kints得到4039的元组个数花费时间很长
			 * 8Kints得到32074的元组数时间更长，更大的数据集在1分钟内是计算不出来的，暴力方法是不可取的
			 */
			//StdOut.println(ThreeSumBruteForce(a[i]));
			
			/**
			 * 使用ThreeSumFast，可以很快在1Kints,2Kints，4Kints,8Kints,16Kints得到这样的整数元组数70,528，4039,32074,255181
			 * 32Kints，1Mints则需要一定时间才能计算出来,相比暴力算法要快很多2052358
			 */
			StdOut.println(ThreeSumFast(a[i]));
		}
	}
	
	/*
	 *  16K很长时间不出结果
	 * 	1Kints.txt test begins: 
		70
		time cost: 0.2

		2Kints.txt test begins: 
		528
		time cost: 1.453

		4Kints.txt test begins: 
		4039
		time cost: 14.135

		8Kints.txt test begins: 
		32074
		time cost: 125.612

		16Kints.txt test begins:
	 */
	public static void testBruteForce(){
		testBruteForce("1Kints.txt");
		testBruteForce("2Kints.txt");
		testBruteForce("4Kints.txt");
		testBruteForce("8Kints.txt");
//		testBruteForce("16Kints.txt");
	}
	
	
	/*
	 *  1Kints.txt test begins: 
		70
		time cost: 0.064s
		
		2Kints.txt test begins: 
		528
		time cost: 0.243s
		
		4Kints.txt test begins: 
		4039
		time cost: 0.958s
		
		8Kints.txt test begins: 
		32074
		time cost: 4.243s
		
		16Kints.txt test begins: 
		255181
		time cost: 16.048s
		
		32Kints.txt test begins: 
		2052358
		time cost: 77.654s
	 */
	public static void testFast(){
		testFast("1Kints.txt");
		testFast("2Kints.txt");
		testFast("4Kints.txt");
		testFast("8Kints.txt");
		testFast("16Kints.txt");
		//testFast("32Kints.txt");
	}
	
	/**
	 * 为ThreeSum产生实验数据，它会随机生成一系列输入数组--可重现可重复的实验，预测-验证的循环
	 * 每一步中讲数组长度加倍，并打印出ThreeSumFast.count()处理各种输入规模的运行时间
	 * 处理N个随机的六位整数的ThreeSumFast的近似运行时间
	 * @return
	 */
	public static double timeTrial(int N){
		int MAX=1000000;
		int[] a=new int[N];
		for(int i=0;i<N;i++)
			a[i]=StdRandom.uniform(-MAX, MAX);
		Stopwatch timer=new Stopwatch();
		//ThreeSumBruteForce(a);
		ThreeSumFast(a);
		return timer.elapsedTime();
	}
	
	
	/**
	 * 倍率定理：T(N)=a*N^b*lgN,则T(2*N)/T(N)~ 2^b,也就是说运行时间比例最后收敛于2^b
	 * 在有性能压力的情况下应该考虑对编写过的所有程序进行倍率实验，记录前后运行时间之比-估计运行时间增长数量级的方法
	 * 注意：刚开始测试需要进行热身实验，一般重复2-3次才开始记录倍率结果(前面不准，数据初始在内存中未命中带来计算误差)
	 */
	public static void testRunTimeRatio(){
		double prev=timeTrial(125);
		StdDraw.setXscale(0, 128);
		StdDraw.setYscale(0, 200);
		StdDraw.setPenRadius(.008);
		StdDraw.setPenColor(StdDraw.RED);
		for(int N=500;true;N+=N) {
			double time=timeTrial(N);
			StdOut.printf("%6d %7.1f", N,time);
			StdDraw.point(N/1000, time);
			//StdDraw.point((double)(Math.log(N)/Math.log(2)), time);
			StdOut.printf("%5.1f\n", time/prev);
			prev=time;
		}
	}
	
	/*****************题目2： 在N个数中找出和为定值的两个数字并统计个数**********************************/
	public static boolean isSorted(int[] a){
		for(int i=0;i<a.length-1;i++){
			if(a[i]>a[i+1]) return false;
		}
		return true;
	}
	
	
	/**
	 * TwoSum问题-要求数组有序，所需时间复杂度为O(n),结合二分查找的时间复杂度需要O(n*lgn)
	 * 这两个数做首尾指针遍历
	 */
	public static int TwoSumSorted(int[] a,int key){
		if(a.length<2) throw new IllegalArgumentException("数组长度至少为2！");
		if(!isSorted(a)) throw  new IllegalArgumentException("数组必须有序！");
		if(key<Integer.MIN_VALUE || key >Integer.MAX_VALUE) throw new IllegalArgumentException("给定值溢出！");
		int low=0,high=a.length-1;
		int cnt=0;
		while(low< high){
			if(a[low]+a[high] > key) high--;
			else if(a[low]+a[high] < key) low++;
			else {
				StdOut.println(a[low]+" "+a[high]);
				cnt++;
				low++;
				high--;
			}
		}
		return cnt;
	}
	
	
	/**
	 * ThreeSum问题-无需要求数组有序，所需时间复杂度为O(n^2)
	 * 第一个数迭代取出，后两个数做首尾指针遍历
	 */
	public static int ThreeSumSorted(int[] a,int key){
		if(a.length<3) throw new IllegalArgumentException("数组长度至少为3！");
		if(key<Integer.MIN_VALUE || key >Integer.MAX_VALUE) throw new IllegalArgumentException("给定值溢出！");
		Arrays.sort(a); //O(n*lgn)
		int cnt=0;		
		for(int i=0;i<=a.length-3;i++){
			int low=i+1,high=a.length-1;
			while(low<high){
				if(a[low]+a[high] > key-a[i]) high--;
				else if(a[low]+a[high] < key-a[i]) low++;
				else {
					StdOut.println(a[i]+" "+a[low]+" "+a[high]);
					cnt++;
					low++;
					high--;
				}
			}
	
		}
		return cnt;
	}
	
	
	
	/**
	 * FourSum问题-无需要求数组有序，所需时间复杂度为O(n^3)
	 * 前两个数迭代取出，后两个数做首尾指针遍历
	 * 推广至K-Sum问题，所需时间复杂度为O(n^(K-1))
	 */
	public static int FourSumSorted(int[] a,int key){
		if(a.length<4) throw new IllegalArgumentException("数组长度至少为4！");
		if(key<Integer.MIN_VALUE || key >Integer.MAX_VALUE) throw new IllegalArgumentException("给定值溢出！");
		Arrays.sort(a);//O(nlgn)
		int cnt=0;		
		for(int i=0;i<=a.length-4;i++)
			for(int j=i+1;j<=a.length-3;j++) { 
			int low=j+1,high=a.length-1;
			while(low<high){
				if(a[low]+a[high] > key-a[i]-a[j]) high--;
				else if(a[low]+a[high] < key-a[i]-a[j]) low++;
				else {
					StdOut.println(a[i]+" "+a[j]+" "+a[low]+" "+a[high]);
					cnt++;
					low++;
					high--;
				}
			}
	
		}
		return cnt;
	}
	
	
	
	public static void main(String[] args) {
		 //testFast();
		//testBruteForce();
		//testRunTimeRatio();
		int[] a={1,2,3,4,5,6,7};
		StdOut.println(FourSumSorted(a,12));
		
		
		
		

	}

}
