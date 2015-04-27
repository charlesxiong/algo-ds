package algo.string;

import com.stdlib.StdOut;

/**
 * 基于有限自动机的KMP实现： 
 * 核心在于在匹配失败时将模式指针j回退到到多远，设为某个值以使i不回退
 * 在于仅借助模式串通过预处理提前判断如何重新开始查找匹配
 * @author charles
 *
 * KMP算法并不回退文本指针i,而是使用一个自动机数组dfa[][]:
 * 它用来记录dfa[txt.chatAt[i]][j]-
 * 在比较了txt.chatAt[i]与pat.chatAt[j]之后应该和下一个文本字符txt.chatAt[i+1]比较的模式字符位置
 * (回退模式指针j到某个位置而不需回退文本指针i)
 * 如果匹配，继续比较下一个字符设置模式指针j为j+1(即dfa[pat.charAt[j][j]总为j+1)
 * 如果不匹配，通过回退指针j使得原串的尾部与新串的头部字符完全重叠,既保证了跳过了部分已匹配的字符，又无需回退指针i
 * dfa数组就是要构造出这样的回退值，并且dfa[txt.chatAt[i][j]]这个值就是重叠字符的数量)
 * (从左向右滑动已匹配的j-1个字符直到所有重叠的字符都互相匹配或者没有相匹配的字符)
 */
public class KMP {
	
	private final int R; //字母表中的字符种类，奇数
	private int[][] dfa; //KMP的dfa数组
	private String pat; //模式串
	
	
	/**
	 * 如何由长度为M的pattern构造出DFA
	 * 要求就是对于每个可能匹配失败的位置都能预先找到重启DFA的可能状态
	 * 有限自动机DFA定义如下： 从文本的开头进行查找，起始状态为0，它停留在状态0扫描文本
	 * 如果找到一个和模式的首字母相同的字符，则跳转到下一个状态并等待下一个字符的判断
	 * 持续这个匹配过程直到自动机状态不断前进到状态M
	 * 每次匹配成功都会将DFA带向下一个状态，等价于增加模式串指针j
	 * 每次匹配失败都会使DFA回到较早前的状态(等价于将模式串的指针j变为一个较小的值)
	 * 
	 * 总的说来就是: 正文指针i不断前进，一次一个字符，但索引j会在DFA的指导下在模式串中左右移动
	 * 因而重启的状态X就是当前的文本字符(第j列下)在原始状态X下的值，要么前进要么维持在X中甚至回退更早的状态
	 */
	public KMP(String pat) {
		this.R=256;
		this.pat=pat;
		
		/*从模式串中构造出DFA*/
		int M=pat.length();
		dfa=new int[R][M];
		dfa[pat.charAt(0)][0]=1;
		for(int X=0,j=1;j<M;j++){
			for(int c=0;c<R;c++)
				dfa[c][j]=dfa[c][X]; //复制匹配失败的情形
			dfa[pat.charAt(j)][j]=j+1; //设置匹配成功的为j+1
			X=dfa[pat.charAt(j)][X]; //更新重启状态
		}
	}
	
	public int search(String txt){
		int N=txt.length();
		int M=pat.length();
		int i,j;
		for(i=0,j=0;i<N&&j<M;i++)
			j=dfa[txt.charAt(i)][j];
		if(j==M) return i-M;
		else return N;
	}

	public static void test(String pat,String txt){
		KMP kmp=new KMP(pat);
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
