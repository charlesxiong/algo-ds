#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;

/*两个队列实现一个栈*/
template<typename T>
class CStack{
public:
	CStack();
	~CStack();

	/*从栈顶压入元素*/
	void appendTail(const T& val);

	/*从栈顶弹出元素*/
	T popBack();

private:
	/*定义两个队列*/
	queue<T> q1;
	queue<T> q2;	
};

template<typename T>
CStack<T>::CStack(){

}

template<typename T>
CStack<T>::~CStack(){
	
}

/*压栈: 直接插入队列q1中*/
template<typename T>
void CStack<T>::appendTail(const T& val){
	q1.push(val);
}

/**
 * 出栈思路(比出队更为麻烦些): 队列的特性先进先出  
 * 如果队列q2为空，不停从队列q1中弹出元素压入队列q2中直至q1中剩下一个元素，
 * 弹出q1最后一个元素必然是对应出栈的元素
 * 如果队列q1为空，不停从队列q2中弹出元素压入队列q1中直至q2中剩下一个元素，
 * 弹出q2最后一个元素必然是对应出栈的元素
 *
 */
template<typename T>
T CStack<T>::popBack(){
	if((q1.size()==0)&&(q2.size()==0)){
		cout<<"Stack is empty\n";
		exit(1);
	}
	
	if(q2.size()<=0){
		while(q1.size()>1){
			T& data=q1.front();
			q1.pop();
			q2.push(data);
		}
		T head=q1.front();
		q1.pop();
		return head;
	} 

	if(q1.size()<=0){
		while(q2.size()>1){
			T& data=q2.front();
			q2.pop();
			q1.push(data);
		}
		T head=q2.front();
		q2.pop();
		return head;
	}
	
}

/*测试出栈的元素是否正确*/
void test(char val,char expected){
	if(val==expected)
		cout<< "Test for "<<val<<" passed"<<endl;
	else
		cout<< "Test for "<<val<<" failed"<<endl;
}


int main(){
	CStack<char> st;
	/*空栈中删除元素*/
	//st.popBack();

	/*队列中插入元素*/
	st.appendTail('a');
	st.appendTail('c');
	st.appendTail('d');
	st.appendTail('z');

	/*非空队列中删除元素*/
	char head=st.popBack();
	test(head,'z');

	head=st.popBack();
	test(head,'d');

	/*继续插入元素*/
	st.appendTail('f');
	head=st.popBack();
	test(head,'f');

	head=st.popBack();
	test(head,'c');

	st.appendTail('g');
	st.appendTail('k');

	head=st.popBack();
	test(head,'k');

	head=st.popBack();
	test(head,'g');

	head=st.popBack();
	test(head,'a');

	return 0;
}