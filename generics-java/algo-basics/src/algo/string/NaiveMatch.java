package algo.string;

import com.stdlib.*;

public class NaiveMatch {
	
	/**
	 * 字符串版本的匹配
	 * @param pat 模式串
	 * @param txt 文本串
	 * @return 在文本串返回第一次匹配模式串的位置
	 * 匹配串在文本中的可能位置为0-n-m
	 * 对于每个位置i,重置j为0并不断将它增大，直至找到一个不匹配的字符或者模式结束(j==m)为止!
	 */
	public static int search1(String pat,String txt){
		int n=txt.length();
		int m=pat.length();
		for(int i=0;i<=n-m;i++){
			int j=0;
			while(j<m){
				if(pat.charAt(j)==txt.charAt(i+j))
					j++;
				else
					break;
			}
			if(j==m) return i;
		}
		return n;
	}
	
	/**
	 * 指针i跟踪文本，指针j跟踪模式。当i和j指向的字符匹配时，同时右移一位
	 * 否则不匹配时，需要回退这两个指针值：
	 * j重新指向模式的开头，i回退到指向本次匹配开始位置的下一个字符(i -=j;i++)
	 */
	public static int search2(String pat,String txt){
		int n=txt.length();
		int m=pat.length();
		int i,j;
		for(i=0,j=0;i<n&&j<m;i++){
			if(txt.charAt(i)==pat.charAt(j)) j++;
			else {
				i -=j;
				j=0; 
			}
		}
		if(j==m) return i-m;
		else return n;
	}
	
	
	
	public static void test(String pat,String txt){
		int offset1=search1(pat,txt);
		int offset2=search2(pat,txt);
		StdOut.println(txt);
		
		for(int i=0;i<offset1;i++)
			StdOut.print(" ");
		StdOut.println(pat);
		
		for(int i=0;i<offset2;i++)
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
