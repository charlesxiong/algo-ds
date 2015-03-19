import com.stdlib.*;

public class Date implements Comparable<Date> {
	private static final int[] DAYS={0,31,29,31,30,31,30,31,31,30,31,30,31};
	/*成员变量均为final类型，表示一经初始化就不可变化*/
	private final int month;
	private final int day;
	private final int year;
	
	/*接受月日年的日期格式*/
	public Date(int m,int d,int y){
		if(!isValid(m,d,y))
			throw new IllegalArgumentException("Invalid date");
		this.month=m;
		this.day=d;
		this.year=y;
	}
	
	/*接受字符串格式的日期形式*/
	public Date(String date) {
		String[] fields=date.split("/");
		if(fields.length!=3)
			throw new IllegalArgumentException("Invalid date");
		this.month=Integer.parseInt(fields[0]);
		this.day=Integer.parseInt(fields[1]);
		this.year=Integer.parseInt(fields[2]);
		if(!isValid(month,day,year))
			throw new IllegalArgumentException("Invalid date");
	}
	
	public int month(){
		return this.month;
	}
	
	public int day(){
		return this.day;
	}
	
	public int year(){
		return this.year;
	}
	
	/*判断月、日、年是否有效*/
	private static boolean isValid(int m,int d,int y){
		if(m<1 || m>12) return false;
		if(d<1 || d> DAYS[m]) return false;
		if(m==2 && d==29 && !isLeapYear(y)) return false;
		return true;
		
	}
	
	/**
	 * 年数必须为4整除，但正百的年数必须被400整数才是闰年,闰年的2月有29天
	 * 更重要的条件放前面，减少了if-else的多重判断
	 * 四年一闰，百年不闰，四百年再闰
	 */
	private static boolean isLeapYear(int y){
		if((y %400==0) || ((y%4==0) && (y%100!=0)))
			return true;
		return false;
	}
	
	/*********************Object基本继承方法*******************/
	public String toString(){
		return month+"/"+day+"/"+year;
	}

	/*比较日期：按优先顺序比较-年，月，日*/
	public int compareTo(Date o) {
		if(this.year  > o.year)       return +1;
		else if(this.year  < o.year)  return -1;
		else if(this.month > o.month) return +1;
		else if(this.month < o.month) return -1;
		else if(this.day > o.day)     return +1;
		else if(this.day < o.day)     return -1;
		else                          return 0;
	}
	
	/**
	 * ==，比较两个基本数据类型的值是否相等或者判断两个对象是否具有相同的引用(比较的是内存地址)
	 * equals方法：判定两个对象是否具有相同的内容，不比较地址
	 */
	public boolean equals(Object x){
		if(x==this) return true;
		if(x==null) return false;
		if(x.getClass()!=this.getClass()) return false;
		Date o=(Date)x;
		return (this.month==o.month) && (this.day==o.day) && (this.year==o.year);
	}
	
    
	/*常见hash方法*/
	public int hashCode(){
		int hash=17;
		hash=31*hash+month;
		hash=31*hash+day;
		hash=31*hash+year;
		return hash;
	}
	

	
	/******************************************/
	/*日期是否在o日期后面*/
	public boolean isAfter(Date o){
		return compareTo(o) >0; 
	}
	
	/*日期是否在o日期前面*/
	public boolean isBefore(Date o){
		return compareTo(o)  <0; 
	}
	
	public Date next(){
		if(isValid(month,day+1,year))      return new Date(month,day+1,year);
		else if(isValid(month+1,day,year)) return new Date(month+1,1,year);
		else                               return new Date(1,1,year+1);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Date today=new Date(12,30,2014);
		StdOut.println(today);
		for(int i=0;i<10;i++) {
			today=today.next();
			StdOut.println(today);
		}
		
		StdOut.println(today.isAfter(today.next()));
		StdOut.println(today.next().isAfter(today));
		StdOut.println(today.isBefore(today.next()));
		

		
		
		
	}

	

}
