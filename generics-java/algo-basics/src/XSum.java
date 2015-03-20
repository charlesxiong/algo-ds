import java.util.Arrays;

import com.stdlib.StdOut;
import com.stdlib.StdRandom;
import com.stdlib.Stopwatch;

/**
 * X-Sum问题 : 基于二分查找的X个数和为某值的求解
 * @author charles
 *
 */

public class XSum {
	
	
/*****************一般情况： 在N个数中找出和为定值的X个数字并统计个数**********************************/
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
		while(low < high){
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
	public static int ThreeSumUnSorted(int[] a,int key){
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
	public static int FourSumUnSorted(int[] a,int key){
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
	
	
	public static double timeTestXSum(String alg,int[] a,int key){
		Stopwatch timer=new Stopwatch();
		if(alg.equals("TwoSumSorted")) 			TwoSumSorted(a,key);
		if(alg.equals("ThreeSumUnSorted")) 		 ThreeSumUnSorted(a,key);
		if(alg.equals("FourSumUnSorted")) 		 FourSumUnSorted(a,key);
		return timer.elapsedTime();
	}
	
	public static double timeTestRndInput(String alg,int N,int T,int key){
		double total=0.0;
		int[] a=new int[N];
		int MAX=1000;
		for(int t=0;t<T;t++){ //表示进行T次实验，每次生成一个数组并排序
			for(int i=0;i<N;i++){
				a[i]=StdRandom.uniform(-MAX, MAX);
			}
			Arrays.sort(a);
			total += timeTestXSum(alg,a,key);
		}
		return (double)(total/T);
	}
	
	
	public static void SimpleTest(){
		int[] a={1,2,3,4,5,6,7};
		int key=12;
		StdOut.println(timeTestXSum("TwoSumSorted",a,key));
		StdOut.println();
		StdOut.println(timeTestXSum("ThreeSumUnSorted",a,key));
		StdOut.println();
		StdOut.println(timeTestXSum("FourSumUnSorted",a,key));
		StdOut.println();
	}
	
	
	public static void main(String[] args) {
		SimpleTest();

	}

}
