package algo.search;

import java.util.NoSuchElementException;

import com.stdlib.In;
import com.stdlib.StdOut;

import algo.basic.LinkedQueue;

public class RedBlackBST<Key extends Comparable<Key>, Value> {
	private static final boolean RED=true;
	private static final boolean BLACK=false;
	private Node root;
	
	private class Node {
		private Key key;
		private Value val;
		private Node left,right;
		private int N; //该子树的结点总数
		private boolean color; //由其父结点指向它的链接的颜色
		
		public Node(Key key, Value val, boolean color, int N) {
	            this.key = key;
	            this.val = val;
	            this.color = color;
	            this.N = N;
	    }
	}
	
	/*结点辅助函数*/
	private boolean isRed(Node x){
		if(x==null) return false;
		return (x.color==RED);
	}
	
	/**
	 * 左旋转
	 * 若新增的红色结点会产生一个红色的右链接
	 * 只需要将插入结点的父结点旋转为红色左链接，修改颜色和结点总数
	 */
	private Node rotateLeft(Node h){
		Node x=h.right;
		h.right=x.left;
		x.left=h;
		x.color=h.color;
		h.color=RED;
		x.N=h.N;
		h.N=1+size(h.left)+size(h.right);
		return x;
	}
	
	/**
	 * 右旋转
	 * 若新增的红色结点会产生一个红色的左链接(两个连续的红色左链接)
	 * 使左链接lean向右侧
	 */
	private Node rotateRight(Node h){
		Node x=h.left;
		h.left=x.right;
		x.right=h;
		x.color=h.color;
		h.color=RED;
		x.N=h.N;
		h.N=1+size(h.left)+size(h.right);
		return x;
	}
	
	
	/**
	 * 当左右链接均为红链接时
	 * 子结点的颜色由红变黑，父节点的颜色由黑变红
	 */
	private void flipColors(Node h){
		h.color=!h.color;
		h.left.color=!h.left.color;
		h.right.color=!h.right.color;
	}
	
	// Assuming that h is red and both h.left and h.left.left
    // are black, make h.left or one of its children red.
    private Node moveRedLeft(Node h) {
        // assert (h != null);
        // assert isRed(h) && !isRed(h.left) && !isRed(h.left.left);

        flipColors(h);
        if (isRed(h.right.left)) { 
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    // Assuming that h is red and both h.right and h.right.left
    // are black, make h.right or one of its children red.
    private Node moveRedRight(Node h) {
        // assert (h != null);
        // assert isRed(h) && !isRed(h.right) && !isRed(h.right.left);
        flipColors(h);
        if (isRed(h.left.left)) { 
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

    // restore red-black tree invariant
    private Node balance(Node h) {
        // assert (h != null);

        if (isRed(h.right))                      h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left)) h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right))     flipColors(h);

        h.N = size(h.left) + size(h.right) + 1;
        return h;
    }

	
	
	
	
	private int size(Node x){
		if(x==null) return 0;
		return x.N;
	}
	
	public int size(){
		return size(root);
	}
	
	public boolean isEmpty(){
		return (root==null);
	}
	
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
	
	public boolean contains(Key key){
		return get(key)!=null;
	}
	
	/*自底向上更新结点颜色，并始终保持根结点颜色是黑色*/
	public void put(Key key,Value val){
		root=put(root,key,val);
		root.color=BLACK;
	}
	
	/**
	 * 树形调整操作: 旋转及改变颜色，重新令树保持平衡
	 * 
	 * @param h
	 * @param key
	 * @param val
	 * @return
	 */
	private Node put(Node h,Key key,Value val){
		if(h==null)
			return new Node(key,val,RED,1);
		
		/*查找到未命中结点的位置*/
		 int cmp = key.compareTo(h.key);
	     if      (cmp < 0) h.left  = put(h.left,  key, val); 
	     else if (cmp > 0) h.right = put(h.right, key, val); 
	     else              h.val   = val;
	     
	     /*修正任何右倾的链接,递归地自底向上判断h结点及其孩子结点的颜色*/
	     if(isRed(h.right)&& !isRed(h.left)) h=rotateLeft(h);
	     if(isRed(h.left)&& isRed(h.left.left)) h=rotateRight(h);
	     if(isRed(h.left)&& isRed(h.right)) flipColors(h);
	     h.N=1+size(h.left)+size(h.right);
	     
	     return h;
	}
	
	  /*************************************************************************
	    *  Red-black deletion
	    *************************************************************************/

	    // delete the key-value pair with the minimum key
	    public void deleteMin() {
	        if (isEmpty()) throw new NoSuchElementException("BST underflow");

	        // if both children of root are black, set root to red
	        if (!isRed(root.left) && !isRed(root.right))
	            root.color = RED;

	        root = deleteMin(root);
	        if (!isEmpty()) root.color = BLACK;
	        // assert check();
	    }

	    // delete the key-value pair with the minimum key rooted at h
	    private Node deleteMin(Node h) { 
	        if (h.left == null)
	            return null;

	        if (!isRed(h.left) && !isRed(h.left.left))
	            h = moveRedLeft(h);

	        h.left = deleteMin(h.left);
	        return balance(h);
	    }


	    // delete the key-value pair with the maximum key
	    public void deleteMax() {
	        if (isEmpty()) throw new NoSuchElementException("BST underflow");

	        // if both children of root are black, set root to red
	        if (!isRed(root.left) && !isRed(root.right))
	            root.color = RED;

	        root = deleteMax(root);
	        if (!isEmpty()) root.color = BLACK;
	        // assert check();
	    }

	    // delete the key-value pair with the maximum key rooted at h
	    private Node deleteMax(Node h) { 
	        if (isRed(h.left))
	            h = rotateRight(h);

	        if (h.right == null)
	            return null;

	        if (!isRed(h.right) && !isRed(h.right.left))
	            h = moveRedRight(h);

	        h.right = deleteMax(h.right);

	        return balance(h);
	    }

	    // delete the key-value pair with the given key
	    public void delete(Key key) { 
	        if (!contains(key)) {
	            System.err.println("symbol table does not contain " + key);
	            return;
	        }

	        // if both children of root are black, set root to red
	        if (!isRed(root.left) && !isRed(root.right))
	            root.color = RED;

	        root = delete(root, key);
	        if (!isEmpty()) root.color = BLACK;
	        // assert check();
	    }

	    // delete the key-value pair with the given key rooted at h
	    private Node delete(Node h, Key key) { 
	        // assert get(h, key) != null;

	        if (key.compareTo(h.key) < 0)  {
	            if (!isRed(h.left) && !isRed(h.left.left))
	                h = moveRedLeft(h);
	            h.left = delete(h.left, key);
	        }
	        else {
	            if (isRed(h.left))
	                h = rotateRight(h);
	            if (key.compareTo(h.key) == 0 && (h.right == null))
	                return null;
	            if (!isRed(h.right) && !isRed(h.right.left))
	                h = moveRedRight(h);
	            if (key.compareTo(h.key) == 0) {
	                Node x = min(h.right);
	                h.key = x.key;
	                h.val = x.val;
	                // h.val = get(h.right, min(h.right).key);
	                // h.key = min(h.right).key;
	                h.right = deleteMin(h.right);
	            }
	            else h.right = delete(h.right, key);
	        }
	        return balance(h);
	    }
	

	    /*************************************************************************
	     *  Utility functions
	     *************************************************************************/

	     // height of tree (1-node tree has height 0)
	     public int height() { return height(root); }
	     private int height(Node x) {
	         if (x == null) return -1;
	         return 1 + Math.max(height(x.left), height(x.right));
	     }

	    /*************************************************************************
	     *  Ordered symbol table methods.
	     *************************************************************************/

	     // the smallest key; null if no such key
	     public Key min() {
	         if (isEmpty()) return null;
	         return min(root).key;
	     } 

	     // the smallest key in subtree rooted at x; null if no such key
	     private Node min(Node x) { 
	         // assert x != null;
	         if (x.left == null) return x; 
	         else                return min(x.left); 
	     } 

	     // the largest key; null if no such key
	     public Key max() {
	         if (isEmpty()) return null;
	         return max(root).key;
	     } 

	     // the largest key in the subtree rooted at x; null if no such key
	     private Node max(Node x) { 
	         // assert x != null;
	         if (x.right == null) return x; 
	         else                 return max(x.right); 
	     } 

	     // the largest key less than or equal to the given key
	     public Key floor(Key key) {
	         Node x = floor(root, key);
	         if (x == null) return null;
	         else           return x.key;
	     }    

	     // the largest key in the subtree rooted at x less than or equal to the given key
	     private Node floor(Node x, Key key) {
	         if (x == null) return null;
	         int cmp = key.compareTo(x.key);
	         if (cmp == 0) return x;
	         if (cmp < 0)  return floor(x.left, key);
	         Node t = floor(x.right, key);
	         if (t != null) return t; 
	         else           return x;
	     }

	     // the smallest key greater than or equal to the given key
	     public Key ceiling(Key key) {  
	         Node x = ceiling(root, key);
	         if (x == null) return null;
	         else           return x.key;  
	     }

	     // the smallest key in the subtree rooted at x greater than or equal to the given key
	     private Node ceiling(Node x, Key key) {  
	         if (x == null) return null;
	         int cmp = key.compareTo(x.key);
	         if (cmp == 0) return x;
	         if (cmp > 0)  return ceiling(x.right, key);
	         Node t = ceiling(x.left, key);
	         if (t != null) return t; 
	         else           return x;
	     }


	     // the key of rank k
	     public Key select(int k) {
	         if (k < 0 || k >= size())  return null;
	         Node x = select(root, k);
	         return x.key;
	     }

	     // the key of rank k in the subtree rooted at x
	     private Node select(Node x, int k) {
	         // assert x != null;
	         // assert k >= 0 && k < size(x);
	         int t = size(x.left); 
	         if      (t > k) return select(x.left,  k); 
	         else if (t < k) return select(x.right, k-t-1); 
	         else            return x; 
	     } 

	     // number of keys less than key
	     public int rank(Key key) {
	         return rank(key, root);
	     } 

	     // number of keys less than key in the subtree rooted at x
	     private int rank(Key key, Node x) {
	         if (x == null) return 0; 
	         int cmp = key.compareTo(x.key); 
	         if      (cmp < 0) return rank(key, x.left); 
	         else if (cmp > 0) return 1 + size(x.left) + rank(key, x.right); 
	         else              return size(x.left); 
	     } 

	    /***********************************************************************
	     *  Range count and range search.
	     ***********************************************************************/

	     // all of the keys, as an Iterable
	     public Iterable<Key> keys() {
	         return keys(min(), max());
	     }

	     // the keys between lo and hi, as an Iterable
	     public Iterable<Key> keys(Key lo, Key hi) {
	         LinkedQueue<Key> queue = new LinkedQueue<Key>();
	         // if (isEmpty() || lo.compareTo(hi) > 0) return queue;
	         keys(root, queue, lo, hi);
	         return queue;
	     } 

	     // add the keys between lo and hi in the subtree rooted at x
	     // to the queue
	     private void keys(Node x, LinkedQueue<Key> queue, Key lo, Key hi) { 
	         if (x == null) return; 
	         int cmplo = lo.compareTo(x.key); 
	         int cmphi = hi.compareTo(x.key); 
	         if (cmplo < 0) keys(x.left, queue, lo, hi); 
	         if (cmplo <= 0 && cmphi >= 0) queue.enqueue(x.key); 
	         if (cmphi > 0) keys(x.right, queue, lo, hi); 
	     } 

	     // number keys between lo and hi
	     public int size(Key lo, Key hi) {
	         if (lo.compareTo(hi) > 0) return 0;
	         if (contains(hi)) return rank(hi) - rank(lo) + 1;
	         else              return rank(hi) - rank(lo);
	     }
	
	
	     public boolean check() {
	         if (!isBST())            StdOut.println("Not in symmetric order");
	         if (!isSizeConsistent()) StdOut.println("Subtree counts not consistent");
	         if (!isRankConsistent()) StdOut.println("Ranks not consistent");
	         if (!is23())             StdOut.println("Not a 2-3 tree");
	         if (!isBalanced())       StdOut.println("Not balanced");
	         return isBST() && isSizeConsistent() && isRankConsistent() && is23() && isBalanced();
	     }

	     // does this binary tree satisfy symmetric order?
	     // Note: this test also ensures that data structure is a binary tree since order is strict
	     private boolean isBST() {
	         return isBST(root, null, null);
	     }

	     // is the tree rooted at x a BST with all keys strictly between min and max
	     // (if min or max is null, treat as empty constraint)
	     // Credit: Bob Dondero's elegant solution
	     private boolean isBST(Node x, Key min, Key max) {
	         if (x == null) return true;
	         if (min != null && x.key.compareTo(min) <= 0) return false;
	         if (max != null && x.key.compareTo(max) >= 0) return false;
	         return isBST(x.left, min, x.key) && isBST(x.right, x.key, max);
	     } 

	     // are the size fields correct?
	     private boolean isSizeConsistent() { return isSizeConsistent(root); }
	     private boolean isSizeConsistent(Node x) {
	         if (x == null) return true;
	         if (x.N != size(x.left) + size(x.right) + 1) return false;
	         return isSizeConsistent(x.left) && isSizeConsistent(x.right);
	     } 

	     // check that ranks are consistent
	     private boolean isRankConsistent() {
	         for (int i = 0; i < size(); i++)
	             if (i != rank(select(i))) return false;
	         for (Key key : keys())
	             if (key.compareTo(select(rank(key))) != 0) return false;
	         return true;
	     }
	     
	     
	     private boolean is23(){
	    	 return is23(root);
	     }
	     
	     /**
	      * 检查是否存在同时和两条红链接相连的结点和红色右链接
	      */
	     private boolean is23(Node x){
	    	 if(x==null) return true;
	    	 if(isRed(x.right)) return false;
	    	 if(x!=root && isRed(x) && isRed(x.left))
	    		 return false;
	    	 return is23(x.left) && is23(x.right); //保证左右孩子也必须满足该性质
	     }
	     
	     /**
	      * 检查从根结点到所有叶子结点的路径上黑链接的数量相同
	      */
	     private boolean isBalanced(){
	    	 Node x=root;
	    	 int black=0;
	    	 while(x!=null){
	    		 if(!isRed(x)) black++;
	    		 x=x.left;
	    	 }
	    	 return isBalanced(root,black);
	     }
	     
	     /*判断从根结点到叶结点是否有给定数目的黑色链接*/
	     private boolean isBalanced(Node x,int black){
	    	 if(x==null) return black==0;
	    	 if(!isRed(x)) black--;
	    	 return isBalanced(x.left, black) && isBalanced(x.right, black);
	     }

	     public static void test(String filename){
	 		RedBlackBST<String,Integer> st=new RedBlackBST<String,Integer>();
	 		In input=new In(filename);
	 		int i=0;
	 		while(!input.isEmpty()){
	 			String key=input.readString();
	 			st.put(key, i);
	 			i++;
	 		}
	 		
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
