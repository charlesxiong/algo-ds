package algo.string;

import com.stdlib.StdOut;

public class KMPImprove {
	private String pat;
	private int[] next; //记录模式指针j字符不匹配时应该回退到的下标位置
	
	/**
	 * 
	 * 改进版: 仅仅花费O(M)的空间，而不依赖于字母表
	 * 如何由模式串构造next数组：前缀串与当前串的后缀串字符匹配比较
	 * 记j=next[i],它表示的是前缀串pat[0..j+1]与当前模式串串尾的匹配的最大情形
	 * 即要判断前缀串尾pat[j+1]字符是否与当前串的后缀串尾pat[i]是否相等()
	 * 如果相等，j++继续下一个前缀串尾与下一个当前串尾比较
	 * 如果不等，j应该继续回退直到能够有合适的前缀串与当前串尾匹配
	 * 然后再更新当前串位置的next值
	 * (显然也可能存在前缀串与后缀串完全不匹配的情况此时对应的next[i]=-1,例如next[0]始终为-1,其他的诸如next[5]也为-1)
	 *        0  1  2  3  4  5  6
	 * 如     a  b  a  b  a  c   b
	 * next  -1 -1  0  1  2  -1  -1
	 * 解释思路
	 * next[0]=-1,next[1]=-1,无前缀串与后缀串匹配
	 * next[2]=0: 因为前缀串pat[0]与后缀串pat[2]相同 
	 * next[3]=1: 因为前缀串pat[0..1]与后缀串pat[2..2]相同 
	 * next[4]=0: 因为前缀串pat[0..2]与后缀串pat[2..4]相同 
	 * next[5]=-1,next[6]=-1,无前缀串与后缀串匹配
	 * @param pat
	 */
	public KMPImprove(String pat) {
		int M=pat.length();
		this.pat=pat;
		next=new int[M];
		int i,j=-1;
		next[0]=-1;
		for(i=1;i<M;i++){
			/**
			 * 条件1的退出条件为j=-1，说明是空串，前后缀无匹配，必须结束；
			 * 条件2表示只有当前缀串尾字符与后缀串尾字符相等时才更新next值否则要一直回退到合适的匹配位置，如果回退位置为j=-1就必须退出
			 */
			while(j>-1&&pat.charAt(j+1)!=pat.charAt(i)) j=next[j];
			if(pat.charAt(j+1)==pat.charAt(i)) j++; //字符匹配时更新前缀串的串尾索引
			next[i]=j; //更新当前串位置的next值
		}
		
		for(i=0;i<M;i++)
			StdOut.println("next["+i+"] = "+next[i]);
	}
	
	/**
	 * 搜索思路类似于next数组的构造
	 * 即判断正文串当前字符是否于模式串的前缀串串尾字符是否匹配
	 * 根据匹配的情况进行合适的回退直到前缀串为整个串，已经完全匹配
	 * @param txt
	 * @return
	 */
	public int search(String txt){
		int N=txt.length();
		int M=pat.length();
		int i,j=-1;
		for(i=0;i<N;i++){
			while(j>-1 && pat.charAt(j+1)!=txt.charAt(i))
				j=next[j]; //回退到合适的前缀串匹配位置
			if(pat.charAt(j+1)==txt.charAt(i)) j++;
			if(j==M-1) return i-j;
		}
		return N;
	}

	public static void test(String pat,String txt){
		KMPImprove kmp=new KMPImprove(pat);
		int offset1=kmp.search(txt);
		StdOut.println(txt);	
		for(int i=0;i<offset1;i++)
			StdOut.print(" ");
		StdOut.println(pat);
	}

	public static void main(String[] args) {
		test("ababacb","abababaababacb");
		test("abracadabra","abacadabrabracabracadabrabrabracad");
		test("rab", "abacadabrabracabracadabrabrabracad");
		test("rabrabracad","abacadabrabracabracadabrabrabracad");
		test("bcara","abacadabrabracabracadabrabrabracad");
		test("abacad","abacadabrabracabracadabrabrabracad");

	}

}
