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
    
	/**
	 * 特殊情况： 在N个数中找出三个和为0的整数元组的数量
	 * 
	 * 在N个数中找出三个和为0的整数元组的数量
	 * 立方级别的暴力算法
	 */
	public static int ThreeSumBruteForce(int[] a){
		int N=a.length;
		int cnt=0;
		for(int i=0;i<N;i++)
			for(int j=i+1;j<N;j++)
				for(int k=j+1;k<N;k++)
					if(a[i]+a[j]+a[k]==0){
						cnt++;
						//StdOut.println(a[i]+" "+a[j]+" "+a[k]);
					}
		return cnt;
	}
	
	/**
	 * 在N个数中找出三个和为0的整数元组的数量
	 * 平方对数级别算法N^2*lgN
	 * 要求需要先对数组进行排序，然后再利用有序数组的二分查找进行计算-统计
	 * 
	 */
	public static int ThreeSumFast(int[] a){
		Arrays.sort(a);
		int N=a.length;
		int cnt=0;
		for(int i=0;i<N;i++)
			for(int j=i+1;j<N;j++) {
				int k=BinarySearch.rank(-a[i]-a[j],a);
				if(k>j) {
					cnt++;
					//StdOut.println(a[i]+" "+a[j]+" "+a[k]);
				}
		}
		return cnt;
	}
		

	

	
	
	
	/**
	 * 使用ThreeSumBruteForce:
	 * 很快在1Kints,2Kints得到这样的整数元组数70,528
	 * 4Kints得到4039的元组个数花费时间很长,8Kints得到32074的元组数时间更长
	 * 更大的数据集在1分钟内是计算不出来的，暴力方法是不可取的
	 * 
	 *  使用ThreeSumFast: 
	 *  可以很快在1Kints,2Kints，4Kints,8Kints,16Kints得到这样的整数元组数70,528，4039,32074,255181
	 *	32Kints，1Mints则需要一定时间才能计算出来,相比暴力算法要快很多
	 *
	 * 其他算法待测试
	 */
	public static void testTotal(String alg){
		String[] files={"1Kints.txt","2Kints.txt","4Kints.txt","8Kints.txt","16Kints.txt","32Kints.txt","1Mints.txt"};
		In[] in=new In[files.length];
		for(int i=0;i<in.length;i++)
			in[i]=new In(files[i]);
		int[][] a=new int[in.length][];
		
		for(int i=0;i<in.length;i++){
			a[i]=in[i].readAllInts();
			if(alg.equals("ThreeSumBruteForce")) StdOut.println(ThreeSumBruteForce(a[i]));
			if(alg.equals("ThreeSumFast")) 		 StdOut.println(ThreeSumFast(a[i]));
		}
	}
	
	public static void testAlg(String alg,String testName){
		if(testName!=null) {
			StdOut.printf("%s test begins: ",testName);
			StdOut.println();
			In in=new In(testName);
			int[] a=in.readAllInts();
			Stopwatch timer=new Stopwatch();
			if(alg.equals("ThreeSumBruteForce")) StdOut.println(ThreeSumBruteForce(a));
			if(alg.equals("ThreeSumFast")) 		 StdOut.println(ThreeSumFast(a));
		    StdOut.println("time cost: "+timer.elapsedTime()+"s");
		    StdOut.println();
		}
	}
	
	
	public static void testAlgs(){
		testAlg("ThreeSumBruteForce","1Kints.txt");
		testAlg("ThreeSumBruteForce","2Kints.txt");
		testAlg("ThreeSumBruteForce","4Kints.txt");
		testAlg("ThreeSumBruteForce","8Kints.txt");
		//testAlg("ThreeSumBruteForce","16Kints.txt");
		StdOut.println();
		testAlg("ThreeSumFast","1Kints.txt");
		testAlg("ThreeSumFast","2Kints.txt");
		testAlg("ThreeSumFast","4Kints.txt");
		testAlg("ThreeSumFast","8Kints.txt");
		testAlg("ThreeSumFast","16Kints.txt");
		//testAlg("ThreeSumFast","32Kints.txt"); 
	}
	
	/**
	 * 为ThreeSum产生实验数据，它会随机生成一系列输入数组--可重现可重复的实验，预测-验证的循环
	 * 每一步中讲数组长度加倍，并打印出ThreeSumFast(alg).count()处理各种输入规模的运行时间
	 * 处理N个随机的六位整数的ThreeSumFast的近似运行时间
	 * 
	 */
	public static double timeTrial(String alg,int N){
		int MAX=1000000;
		int[] a=new int[N];
		for(int i=0;i<N;i++)
			a[i]=StdRandom.uniform(-MAX, MAX);
		Stopwatch timer=new Stopwatch();
		if(alg.equals("ThreeSumBruteForce")) ThreeSumBruteForce(a);
		if(alg.equals("ThreeSumFast")) 		 ThreeSumFast(a);
		return timer.elapsedTime();
	}
	
	/**
	 * 倍率定理：T(N)=a*N^b*lgN,则T(2*N)/T(N)~ 2^b,也就是说运行时间比例最后收敛于2^b
	 * 在有性能压力的情况下应该考虑对编写过的所有程序进行倍率实验，记录前后运行时间之比-估计运行时间增长数量级的方法
	 * 注意：刚开始测试需要进行热身实验，一般重复2-3次才开始记录倍率结果(前面不准，数据初始在内存中未命中带来计算误差)
	 */
	public static void testRunTimeRatio(String alg){
		double prev=timeTrial(alg,125);
		StdDraw.setXscale(0, 128);
		StdDraw.setYscale(0, 200);
		StdDraw.setPenRadius(.008);
		StdDraw.setPenColor(StdDraw.RED);
		for(int N=500;true;N+=N) {
			double time=timeTrial(alg,N);
			StdOut.printf("%6d %7.1f", N,time);
			StdDraw.point(N/1000, time);
			//StdDraw.point((double)(Math.log(N)/Math.log(2)), time);
			StdOut.printf("%5.1f\n", time/prev);
			prev=time;
		}
	}
	
	
	
	
	
	
	
	public static void main(String[] args) {
		/*和为0的时间测试和运行时间比率测试*/
		StdOut.println(timeTrial("ThreeSumFast",100));
		testRunTimeRatio("ThreeSumFast");
		//testTotal("ThreeSumFast");
		//testAlgs();
		
	}
}
