package algo.search;

import com.stdlib.In;
import com.stdlib.StdIn;
import com.stdlib.StdOut;

public class DictSearchCSV {

	/**
	 * 字典类实例: 提供插入、获取、查找操作
	 * 它在现实生活中有很多应用，如
	 * 字典中单词的定义作为键，拼写作为值
	 * 账户信息中账户名作为键，余额作为值
	 * 基因组中密码子作为键，氨基酸作为值或者氨基酸序列与蛋白质的对应广西
	 * 实验数据中数据或时间作为键，结果作为值
	 * 文件系统中文件名作为键，对应地址作为值
	 * DNS中域名-IP是一个良好的键值对映射关系
	 * 元素周期表名字与对应位置
	 * 
	 * 下面以逗号分隔的不同的CSV文件利用符号表实现更新和查找
	 * 从文件中读入数据动态构建对应符号表
	 * 接受三个输入参数: 文件、键和值所在的位置
	 * 实现的处理: 查询某个键对应的值、改变键对应的值、范围查找或者构建多个字典
	 */
	public static void test(String filename,int keyField,int valField){
		RedBlackBST<String,String> st=new RedBlackBST<String,String>();
		/*从文件中读入数据插入到符号表中*/
		In input=new In(filename);
		while(!input.isEmpty()){
			String line = input.readLine();
			String[] tokens = line.split(",");
			st.put(tokens[keyField], tokens[valField]);
		}
		
		 while (!StdIn.isEmpty()) {
	            String s = StdIn.readString();
	            if (st.contains(s)) StdOut.println(st.get(s));
	            else                StdOut.println("Not found");
	     }
	}

	public static void main(String[] args) {
		String filename = StdIn.readString();
		int keyField = StdIn.readInt();
		int valField = StdIn.readInt();
		test(filename,keyField,valField);
	}
}
