package algo.search;

import java.util.NoSuchElementException;

import com.stdlib.In;
import com.stdlib.StdOut;

import algo.basic.LinkedQueue;

public class BST<Key extends Comparable<Key>,Value> {
	private Node root; //BST的根结点
	
	/*和二分查找定义结点总数N的方式不同*/
	private class Node{
		private Key key;
		private Value val;
		private Node left,right;
		private int N; //以该结点为根的子树中结点的总数
		
		/*结点计数器的效果是简化了很多有序性操作的实现*/
		public Node(Key key,Value val,int N){
			this.key=key;
			this.val=val;
			this.N=N;
		}
	}
	
	
	/*返回表中键值对个数*/
	public int size(){
		return size(root);
	}
	
	/*计算以x为根结点的子树的结点总数*/
	private int size(Node x){
		if(x==null) return 0;
		else return x.N;
	}
	
	public boolean isEmpty(){
		return size()==0;
	}
	
	/*查找key,找到则更新它的值否则就为它创建一个新的结点，借助Helper function用递归的方式实现*/
	public void put(Key key,Value val){
		root=put(root,key,val);
	}
    
	/**
	 * 递归插入思路:
	 * 如果树是空的，就返回一个含该键值对的新节点
	 * 如果被查找的键小于根结点的的键，递归在左子树中插入
	 * 如果被查找的键小于根结点的的键，递归在右子树中插入
	 * 注意: 递归地在路径上将每个结点中的计数器值加1
	 * 非递归的思路: 实现也不复杂，但更新结点计数器的方法比较复杂
	 */
	private Node put(Node x,Key key,Value val){
		if(x==null) return new Node(key,val,1);
		int cmp=key.compareTo(x.key);
		if(cmp<0) x.left=put(x.left,key,val);
		else if(cmp>0) x.right=put(x.right,key,val);
		else x.val=val;
		x.N=size(x.left)+size(x.right)+1; //更新结点的计数(递归方式)
		return x;
	}
	
	/*在二叉查找树中查找键值对应的实值*/
	public Value get(Key key){
		Node x=root;
		while(x!=null){
			int cmp=key.compareTo(x.key);
			if(cmp<0) x=x.left;
			else if(cmp>0) x=x.right;
			else return x.val;
		}
		return null;
	}
	
	/*判断键是不是在表中*/
	public boolean contains(Key key){
		return get(key)!=null;
	}
	
	/********************************************
	 * 删除操作
	 ********************************************/
	public void deleteMin(){
		 if (isEmpty()) throw new NoSuchElementException("符号表为空");
		 root=deleteMin(root);
	}
	
	/**
	 * 不断深入根结点的左子树中直到遇到一个空链接
	 * 然后把指向该节点的链接指向该节点的右子树(返回它的右链接即可)
	 * 并递归更新在新节点到根结点的路径上的所有结点的计数器的值
	 */
	private Node deleteMin(Node x){
		if(x.left==null) return x.right; 
		x.left=deleteMin(x.left);
		x.N=size(x.left)+size(x.right)+1; //更新结点的计数(递归方式)
		return x;
	}
	
	public void deleteMax(){
		 if (isEmpty()) throw new NoSuchElementException("符号表为空");
		 root=deleteMax(root);
	}
	
	/**
	 * 不断深入根结点的右子树中直到遇到一个空链接
	 * 然后把指向该节点的链接指向该节点的左子树(返回它的左链接即可)
	 * 并递归更新在新节点到根结点的路径上的所有结点的计数器的值
	 */
	private Node deleteMax(Node x){
		if(x.right==null) return x.left; 
		x.right=deleteMax(x.right);
		x.N=size(x.left)+size(x.right)+1; //更新结点的计数(递归方式)
		return x;
	}
	
	public void delete(Key key){
		 root=delete(root,key);
	}
	
	/**
	 * 删除结点x用它的后继结点填补它的位置-一般是右子树的最小结点
	 */
	private Node delete(Node x,Key key){
		if(x==null) return null;
		int cmp=key.compareTo(x.key);
		if(cmp>0) x.left=delete(x.left,key);
		else if(cmp<0) x.right=delete(x.right,key);
		else {
			if(x.right==null) return x.left;
			if(x.left==null) return x.right;
			Node t=x; //暂存当前键的结点
			x=min(t.right); //取右子树的最小结点
			x.right=deleteMin(t.right); //删除最小节点的有节点
			x.left=t.left; //原来的左孩子指向新结点的左链接
		}
		x.N=size(x.left)+size(x.right)+1; //更新结点的计数(递归方式)
		return x;
	}
	
	/*************************************************
	 * 有序性操作
	 *************************************************/
	
	public Key min(){
		if(isEmpty()) return null;
		return min(root).key;
	}
	
	private Node min(Node x){
		if(x.left==null) return x;
		else return min(x.left);
	}
	
	public Key max(){
		if(isEmpty()) return null;
		return max(root).key;
	}
	
	private Node max(Node x){
		if(x.right==null) return x;
		else return max(x.right);
	}
	
	
	public Key floor(Key key){
		Node x=floor(root,key);
		if(x==null) return null;
		return x.key;
	}
	
	/**
	 * 向下取整操作
	 * 如果给定键小于当前根结点的键，那么小于或等于key的最大键必然在左子树中
	 * 若给定键大于当前根结点的键，那么小于或等于key的最大键必然在右子树中
	 * 否则根结点就是小于等于key的最大键
	 */
	private Node floor(Node x,Key key){
		if(x==null) return null;
		int cmp=key.compareTo(x.key);
		if(cmp==0) return x;
		else if(cmp<0) return floor(x.left,key);
		else {
			Node t=floor(x.right,key);
			if(t==null) return x;
			else return t;
		}
	}
	
	public Key ceiling(Key key){
		Node x=ceiling(root,key);
		if(x==null) return null;
		return x.key;
	}
	
	/**
	 * 向上取整操作
	 * 如果给定键小于当前根结点的键，那么大于或等于key的最大键必然在左子树中
	 * 若给定键大于当前根结点的键，那么大于或等于key的最大键必然在右子树中
	 * 否则根结点就是大于等于key的最大键
	 */
	private Node ceiling(Node x,Key key){
		if(x==null) return null;
		int cmp=key.compareTo(x.key);
		if(cmp==0) return x;
		else if(cmp>0) return ceiling(x.right,key);
		else {
			Node t=ceiling(x.left,key);
			if(t==null) return x;
			else return t;
		}
	}
	
	public int rank(Key key){
		return rank(key,root);
	}
	
	/**
	 * 排名操作
	 * 返回以x为根结点的子树中小于key的键的数量
	 * 如果给定的键与根结点键相等，返回左子树中结点的个数
	 * 小于根结点，返回该键在左子树中的排名
	 * 大于根结点，返回该键在右子树的排名+左子树结点个数+1
	 */
	private int rank(Key key,Node x){
		if(x==null) return 0;
		int cmp=key.compareTo(x.key);
		if(cmp<0) return rank(key,x.left);
		else if(cmp>0) return 1+size(x.left)+rank(key,x.right);
		else return size(x.left);
	}
	
	/*返回排名为k的键值*/
	public Key select(int k){
		if(k <0 || k >=size()) return null; //排名0-N-1
		return select(k,root).key;
	}
	
	/**
	 * 找到排名为k的键(树中正好有小于k的键)
	 * 如果左子树的结点数t大于k,则递归地在左子树中查找排名为k的键
	 * 如果小于k，则递归地在右子树中查找排名为k-t-1的键
	 * 如果相等，就返回根结点的键
	 */
	private Node select(int k,Node x){
		if(x==null) return null;
		int t=size(x.left);
		if(t>k) return select(k,x.left);
		else if(t<k) return select(k-t-1,x.right);
		else return x;
	}
	
	public Iterable<Key> keys(){
		return keys(min(),max());
	}
	
	public Iterable<Key> keys(Key lo,Key hi){
		LinkedQueue<Key> queue=new LinkedQueue<Key>();
		keys(root,queue,lo,hi);
		return queue;
	}
	
	private void keys(Node x,LinkedQueue<Key> queue,Key lo,Key hi){
		if(x==null) return;
		int cmplo=lo.compareTo(x.key);
		int cmphi=hi.compareTo(x.key);
		if(cmplo<0) keys(x.left,queue,lo,hi);
		if(cmplo <=0 && cmphi >=0) queue.enqueue(x.key);
		if(cmphi>0) keys(x.right,queue,lo,hi); 
	}
	
	public int size(Key lo,Key hi){
		if(lo.compareTo(hi)>0) return 0;
		if(contains(hi)) return rank(hi)-rank(lo)+1;
		else 			 return rank(hi)-rank(lo);
	}
	
	public int height(){
		return height(root);
	}
	
	/**
	 * BST的高度: 一个结点的树高为0
	 * @param x
	 * @return
	 */
	private int height(Node x){
		if(x==null) return -1;
		return 1+ Math.max(height(x.left), height(x.right));
	}
	
	public Iterable<Key> levelOrder(){
		LinkedQueue<Key> keys=new LinkedQueue<Key>();
		LinkedQueue<Node> queue=new LinkedQueue<Node>();
		queue.enqueue(root);
		while(!queue.isEmpty()){
			Node x=queue.dequeue();
			keys.enqueue(x.key);
			if(x.left!=null)
				queue.enqueue(x.left);
			if(x.right!=null)
				queue.enqueue(x.right);
		}
		return keys;
	}
	
	/*************************************
	 * BST数据结构的一致性
	 *************************************/
	private boolean check(){
		if(!isBST()) System.out.println("不是一个对称顺序");
		if(!isSizeConsistent()) System.out.println("子树结点的数目不一致");
		if(!isRankConsistent()) System.out.println("排名不一致");
		return isBST() && isSizeConsistent() &&isRankConsistent();
	}
	
	private boolean isBST(){
		return isBST(root,null,null);
	}
	
	private boolean isBST(Node x,Key min,Key max){
		if(x==null) return true;
		if(min!=null && x.key.compareTo(min) <=0) return false;
		if(max!=null && x.key.compareTo(max) >=0) return false;
		return isBST(x.left,min,x.key) && isBST(x.right,x.key,max);
	}
	
	private boolean isSizeConsistent(){
		return isSizeConsistent(root);
	}
	
	private boolean isSizeConsistent(Node x){
		if(x==null) return true;
		if(x.N!=size(x.left)+size(x.right)+1)
			return false;
		return isSizeConsistent(x.left)&& isSizeConsistent(x.right);
	}
	
	private boolean isRankConsistent(){
		for(int i=0;i< size();i++)
			if(i!=rank(select(i))) return false;
		for(Key key : keys())
			if(key.compareTo(select(rank(key)))!=0) return false;
		return true;
	}
	
	public static void test(String filename){
		BST<String,Integer> st=new BST<String,Integer>();
		In input=new In(filename);
		int i=0;
		while(!input.isEmpty()){
			String key=input.readString();
			st.put(key, i);
			i++;
		}
		
		StdOut.println("层次序遍历:");
		for(String s: st.levelOrder())
			StdOut.println(s+ " "+st.get(s));
		
		StdOut.println("中序遍历:");
		for(String s: st.keys()){
			StdOut.println(s+ " "+st.get(s));
		}
		
		String s=st.floor("R");
		StdOut.println("小于等于当前键R的最大键: "+s);
		s=st.ceiling("J");
		StdOut.println("大于或等于当前键J的最小键: "+s);
		StdOut.println("小于键R的数值: "+st.rank("R"));
		StdOut.println("第3个的键值: "+st.select(3));
		StdOut.println(st.size("R","X"));	
	}
	
	public static void main(String[] args) {
		test("tinyST.txt");
		test("tinyST1.txt");

	}

}
