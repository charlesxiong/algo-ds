import com.stdlib.*;



/**
 * 　id数组是用父链接的形式表示了一片森林，这种方法在数组的应用是个很不错的技巧
 * 
 * 不相交集合森林的表示，采用链接的形式
 * 改进运行时间的启发式策略: 按秩合并和路径压缩
 * 按秩合并，加权quick-union算法构造的森林中的任意节点的深度最多为lgN
 * 也就是说对于从一个节点到它根节点的路径上的每个节点，每种操作最多只会访问数组常数次
 * 策略: 包含节点较小的根在union操作中要指向节点较大的根
 * @author charles
 *
 */
public class WeightedQuickUnionUF {
	private int[] id;
	private int[] sz; //记录每个分量的节点个数
	private int count;//分量的个数
	
	public WeightedQuickUnionUF(int N) {
		count=N;
		id=new int[N];
		sz=new int[N];
		for(int i=0;i<N;i++)
			id[i]=i;
		for(int i=0;i<N;i++)
			sz[i]=1;
	}
	
	public int count(){
		return this.count;
	}
	
	public boolean connected(int p,int q){
		return find(p)==find(q);
	}
	
	public int find(int p){
		while(p!=id[p]) p=id[p];
		return p;
	}
	
	/*合并操作总是使小树连接到大树上*/
	public void union(int p,int q){
		int pRoot=find(p);
		int qRoot=find(q);
		
		if(pRoot==qRoot) return;
		if(sz[pRoot]<sz[qRoot]) { 
			id[pRoot]=qRoot;
			
			sz[qRoot] +=sz[pRoot];
		} else{
			id[qRoot]=pRoot;
			sz[pRoot] +=sz[qRoot];
		}
		
		this.count--;
	}
	
	/**
	 * 3个测试文件:
	 * tinyUF.txt- 10个触点和11个连接
	 * mediumUF.txt- 625个触点和900条连接
	 * largeUF.txt- 100万个触点和200万条连接
	 * 
	 * 要处理百万级数据的规模，应该选择何种算法
	 * @param filename
	 */
	public static double test(String filename){
		In in=new In(filename);
		int N=in.readInt(); //读取触点数
		
		WeightedQuickUnionUF uf=new WeightedQuickUnionUF(N); //初始化触点分量
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
