import com.stdlib.*;


public class QuickUnionByPathCompresUF {
	private int[] id; //触点i所对应的下一个索引
	private byte[] rank;//以触点i为根结点的高度(从x到某一个后代的叶结点最长路径上边的数目),这里最长深度为31，不能超出int位数-1
	private int count; //分量个数
	
	public QuickUnionByPathCompresUF(int N) {
		count=N;
		id=new int[N];
		rank=new byte[N];
		for(int i=0;i<N;i++){
			id[i]=i;
			rank[i]=0; //初始所有高度均为0
		}
	}
	
	/**
	 *  原始路径下根结点的秩只有1，始终能保证在路径上遇到的所有节点最后都直接链接到了根结点
	 *  路径压缩但并不改变节点的秩
	 *  
	 *  带路径压缩的find()方法，最后得到的是几乎完全扁平化的树
	 */
	public int find(int p){ 
		while(p!=id[p]){ 
			id[p]=id[id[p]];
			p=id[p];
		}
		return p;
	}
	
	public void union(int p,int q){
		int r1=find(p);
		int r2=find(q);
		
		if(r1==r2) return;
		if(rank[r1]< rank[r2]){
			id[r1]=r2;		
		} else if(rank[r1] > rank[r2]){
			id[r2]=r1;
		} else {
			id[r2]=r1;  //小根指向大根的根结点
			rank[r1]++; //相等时，产生新的高度，根的秩才加1(秩才上升)
		}
		count--;
	}
	
	public int count(){
		return count;
	}
	
	public boolean connected(int p,int q){
		return find(p)==find(q);
	}
	


	/**
	 * 3个测试文件:
	 * tinyUF.txt- 10个触点和11个连接
	 * mediumUF.txt- 625个触点和900条连接
	 * largeUF.txt- 100万个触点和200万条连接
	 */
	public static double test(String filename){
		In in=new In(filename);
		int N=in.readInt(); //读取触点数
		
		QuickUnionByPathCompresUF uf=new QuickUnionByPathCompresUF(N); //初始化触点分量
		Stopwatch timer=new Stopwatch();
		while(!in.isEmpty()){
			int p=in.readInt();
			int q=in.readInt();
			if(uf.connected(p, q)) continue; //如果已经连通，则忽略
			uf.union(p, q); //合并分量
			//StdOut.println(p+ " "+q); //打印连接，不用打出已知相连的整数对(不必要)
		}
		StdOut.println(uf.count() + " components");
		return timer.elapsedTime();
	}

	public static void main(String[] args) {
		StdOut.println(test("tinyUF.txt"));
		StdOut.println(test("mediumUF.txt"));
		StdOut.println(test("largeUF.txt"));
	}
}
