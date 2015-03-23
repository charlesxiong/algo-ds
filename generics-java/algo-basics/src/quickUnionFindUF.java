import com.stdlib.*;

/**
 * 并查集解决动态连通性问题
 * 通过等价关系把对象分为多个等价类: 两个对象相连视为一个等价类
 * 
 * 设计一个数据结构来保存程序已知的所有整数对的足够多的信息，并用它们来保存一对新对象是否相连
 * 
 * 应用: 物理中的渗流、通信网络中的连通性
 * @author charles
 *
 */
public class quickUnionFindUF {
	private int[] id; //分量id, 以触点为索引
	private int count; //分量个数
	
	public quickUnionFindUF(int N) { //初始化分量id数组
		count=N;
		id=new int[N];
		for(int i=0;i<N;i++)
			id[i]=i;
	}
	
	public int count(){
		return count;
	}
	
	/*如果p和q存在同一个分量中，则返回true*/
	public boolean connected(int p,int q){
		return find(p)==find(q);
	}
	
	/**
	 * 方法1: quick-find方法
	 *  
	 *  id[p]==id[q],不需进行任何改动
	 *  id[p]不等于id[q],所有和id[q]相等的元素的值变为id[p]的值
	 *  
	 *  find操作只需访问数组一次，union操作对于每一对输入都要扫描整个数组
	 *  quick-find算法的时间复杂度: 　O(N^2)
	 *  对于最终只能得到少数连通分量的一般应用都是平方级别的
	 */

	/*p所在的分量标识符，0-N-1*/
//	int find(int p){
//		return id[p];
//	}
//	
//	public void union(int p,int q){
//		int pId=find(p);
//		int qId=find(q);
//		
//		if(pId==qId) return ; //已经在同一个分量中，无需采取任何行动
//		
//		for(int i=0;i<id.length;i++){
//			if(id[i]==pId) id[i]=qId;
//		}
//		
//		count--; //减少有触点对应的id值是id[p]的分量
//	}
	
	/**
	 * 方法2: quick-union方法
	 * 
	 * 　find: 通过链接由一个触点到另外一个触点，知道有个链接它必定指向自身的触点即id[x]=x，该触点必然存在
	 * 　因而find方法则是通过不断链接遍历到id[x]==x的时为止，该触点为根触点
	 * 
	 * 　union方法: 只需把一个根触点连接到另一个分量的根触点上，通过一条语句就使一个根结点变成另一个根结点的父节点，快速归并了两棵树
	 * 
	 * 它是quick-find方法的一种改良(union操作总是线性级别的)，但并不能保证在所有情况下都比quick-find算法快
	 * 它取决于树中节点的深度，最坏情况下动态连通性问题只有一个分量，则quick-union的复杂度也是平方级别的
	 * 原因: 最坏情况下树的深度为N，树的深度无法得到保证。
	 * 改进的办法是: 记录每一棵树的大小并总是将较小的树连接到较大的树中，它能够大大改进算法的效率，称为加权quick-union
	 */
	
	public int find(int p){
		while(p!=id[p]) p=id[p];
		return p;
	}
	
	public void union(int p,int q){//将p和q的根结点统一
		int pRoot=find(p);
		int qRoot=find(q);
		
		if(pRoot==qRoot) return ;
		id[pRoot]=qRoot;
		count--;
	}
	
	
	
	/**
	 * 3个测试文件:
	 * tinyUF.txt- 10个触点和11个连接
	 * mediumUF.txt- 625个触点和900条连接
	 * largeUF.txt- 100万个触点和200万条连接
	 * 
	 * 要处理百万级数据的规模，应该选择何种算法
	 */
	public static void test(String filename){
		In in=new In(filename);
		int N=in.readInt(); //读取触点数
		
		quickUnionFindUF uf=new quickUnionFindUF(N); //初始化触点分量
		while(!in.isEmpty()){
			int p=in.readInt();
			int q=in.readInt();
			if(uf.connected(p, q)) continue; //如果已经连通，则忽略
			uf.union(p, q); //合并分量
			//StdOut.println(p+ " "+q); //打印连接，不用打出已知相连的整数对(不必要)
		}
		StdOut.println(uf.count() + " components");
	}

	public static void main(String[] args) {
		test("tinyUF.txt");
		test("mediumUF.txt");
		test("largeUF.txt");

	}

}
