import java.util.*;
import com.stdlib.*;

public class Transaction implements Comparable<Transaction> {
	private final String who; //顾客
	private final Date when;  //日期
	private final double amount; //数量
	
	public Transaction(String who,Date when ,double amount) {
		if(Double.isInfinite(amount) || Double.isNaN(amount))
			throw new IllegalArgumentException("Amount cannot be NaN or infinite");
		this.who=who;
		this.when=when;
		if(amount==0.0) this.amount=0.0;//-0.0
		else            this.amount=amount;
	}
	
	public Transaction(String transaction){
		String[] fields=transaction.split("\\s+");
		this.who=fields[0];
		this.when=new Date(fields[1]);
		double amount=Double.parseDouble(fields[2]);
		if(Double.isInfinite(amount) || Double.isNaN(amount))
			throw new IllegalArgumentException("Amount cannot be NaN or infinite");
		if(amount==0.0) this.amount=0.0; //-0.0
		else            this.amount=amount;
	}

	public String who(){
		return this.who;
	}
	
	public Date when(){
		return this.when;
	}
	
	public double amount(){
		return this.amount;
	}
	
	/*********************Object基本继承方法*******************/
	public String toString(){
		return String.format("%-10s %10s %8.2f",who,when,amount);
	}
	
	public int hashCode(){
		int hash=17;
		hash=31*hash+who.hashCode();
		hash=31*hash+when.hashCode();
		hash=31*hash+((Double)amount).hashCode();
		return hash;
	}
	
	public boolean equals(Object o){
		if(o==this) return true;
		if(o==null) return false;
		if(o.getClass() !=this.getClass()) return false;
		Transaction that=(Transaction)o;
		return (this.who.equals(that.who)) && (this.when.equals(that.when)) && (this.amount==that.amount);
	}
	
	/*默认交易对象的大小比较方法*/
	public int compareTo(Transaction o){
		if(this.amount > o.amount) return +1;
		else if(this.amount < o.amount) return -1;
		return 0;
	}
	/********************************************************/
	
	/**********实现不同的比较器内部类：按顾客、日期、交易金额********/
	public static class WhoOrder implements Comparator<Transaction> {
		@Override
		public int compare(Transaction o1, Transaction o2) {
			return o1.who.compareTo(o2.who);
		}
	}
	
	public static class WhenOrder implements Comparator<Transaction> {
		@Override
		public int compare(Transaction o1, Transaction o2) {
			return o1.when.compareTo(o2.when);
		}
	}
	
	public static class AmountOrder implements Comparator<Transaction> {
		@Override
		public int compare(Transaction o1, Transaction o2) {
			if(o1.amount > o2.amount) return +1;
			else if(o1.amount < o2.amount) return -1;
			return 0;
		}
	}
	/********************************************************/
	
	public static void main(String[] args) {
		Transaction[] a=new Transaction[4];
		a[0]=new Transaction("Turing    6/17/1990  664.08");
		a[1]=new Transaction("Tarjan    3/26/2001 4121.85");
		a[2]=new Transaction("Knuth     6/14/1990  288.34");
		a[3]=new Transaction("Dijkstra  8/22/2007 2678.40");
		
		StdOut.println("0 Unsorted: ");
		for(int i=0;i<a.length;i++)
			StdOut.println(a[i]);
		StdOut.println();
		
		StdOut.println("1 Sorted Default: ");
		Arrays.sort(a);
		for(int i=0;i<a.length;i++)
			StdOut.println(a[i]);
		StdOut.println();
		
		StdOut.println("2 Sorted by Customer: ");
		Arrays.sort(a,new Transaction.WhoOrder());
		for(int i=0;i<a.length;i++)
			StdOut.println(a[i]);
		StdOut.println();
		
		StdOut.println("3 Sorted by Date: ");
		Arrays.sort(a,new Transaction.WhenOrder());
		for(int i=0;i<a.length;i++)
			StdOut.println(a[i]);
		StdOut.println();
		
		
		StdOut.println("4 Sorted by Amount: ");
		Arrays.sort(a,new Transaction.AmountOrder());
		for(int i=0;i<a.length;i++)
			StdOut.println(a[i]);
		StdOut.println();

	}

}
