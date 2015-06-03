package algo.search;

import algo.basic.LinkedQueue;

import com.stdlib.In;
import com.stdlib.StdIn;
import com.stdlib.StdOut;

public class DictSearchIndex {

    /**
     * 一般来说，一个键有可能和多个值相关联
     * 使用索引来描述一个键与多个值相关联的符号表，同时也可以构造反向索引(将键和值的角色互换)
     * 反向索引一般是指用值来查找键的操作，例如有大量的数据我们希望直到某个键都在哪些地方出现过
     * 商业交易中账号作为键，值是一系列交易
     * 基因组学中一种氨基酸对应多种密码子，反向索引即是密码子作为键，找到对应的氨基酸
     * 网络搜索中关键字作为键，值对应一系列的网页，反向索引则是一个网页对应哪些关键字
     * IMDB中电影作为键，值对应一系列参与的演员，反向索引则是找到一个演员出演过的所有电影
     * 
     */

	public static void main(String[] args) {
		String filename = StdIn.readString(); //文件名，索引的数据库
		String sep = StdIn.readString(); //文件每行的分隔符
		RedBlackBST<String,LinkedQueue<String>> st=new RedBlackBST<String,LinkedQueue<String>>(); //正向索引
		RedBlackBST<String,LinkedQueue<String>> ts=new RedBlackBST<String,LinkedQueue<String>>(); //反向索引
		
		/*读入文件插入数据到索引中*/
		In input = new In(filename);
		while(!input.isEmpty()){
			String[] tokens = input.readLine().split(sep);
			String key = tokens[0];
			for(int i = 1; i < tokens.length; i++){
				String val = tokens[i];
				if(!st.contains(key))
					st.put(key, new LinkedQueue<String>());
				if(!ts.contains(val))
					ts.put(val, new LinkedQueue<String>());
				
				st.get(key).enqueue(val);
				ts.get(val).enqueue(key);			
			}
		}
		
		/*查询*/
		while(!StdIn.isEmpty()){
			String query = StdIn.readLine();
			if(st.contains(query)){
				if(st.get(query).size()==0)
					StdOut.println("Not Found");
				else {
					for(String s: st.get(query))
						StdOut.println(s+ " ");
					}
			}
			
			if(ts.contains(query)){ //二者执行其一，要么反向索引要么正向索引
				if(ts.get(query).size()==0)
					StdOut.println("Not Found");
				else {
					for(String s: ts.get(query)) 
						StdOut.println(s+ " ");
				}
			}	
		}
	}
}
