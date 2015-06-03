package algo.search;

import com.stdlib.In;
import com.stdlib.StdOut;
import com.stdlib.Stopwatch;

/*字典的应用: 键值对*/
public class FreqCounter {
	
	/**
	 * 输入一段文本字符串，记录每个字符串的出现次数(要求长度至少要达到给定阈值)，并统计出现频率最高的键
	 * @param filename 测试文本
	 * @param minlen 字符串长度至少达到的指定阈值
	 * tinyTale.txt： 狄更斯《双城记》中的前五行
	 * tale.txt： 双城记全书
	 * leipzig1M.txt： 一百万条随机从网络上抽取的句子
	 */
	public static void test(String filename,int minlen){
		/*选择不同实现形式的符号表：二叉查找树、平衡树、散列表(开地址、闭地址)*/
		//SepChainingHashST<String,Integer> st=new SepChainingHashST<String,Integer>();
		LinearProbingHashST<String,Integer> st=new LinearProbingHashST<String,Integer>();
		In input=new In(filename);
		Stopwatch timer=new Stopwatch();
		while(!input.isEmpty()){
			/*构造符号表并统计频率*/
			String word=input.readString();
			if(word.length()<minlen) continue; //忽略小于阈值的单词
			if(!st.contains(word)) st.put(word,1);
			else 		st.put(word, st.get(word)+1);
		}
		StdOut.println(st.size());
		
		/*找出频率最高的单词*/
		String max="";
		st.put(max, 0);
		for(String word: st.keys()){
			if(st.get(word) >st.get(max))
				max=word;
		}
		StdOut.println(max+" "+st.get(max));
		StdOut.println(timer.elapsedTime());
	}
	
	public static void main(String[] args) {
		test("tinytinyTale.txt",1);
		test("tinyTale.txt",1);
		test("medTale.txt",8);
		test("tale.txt",8);
		test("leipzig1M.txt",10);
	}

}
