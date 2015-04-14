#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

/*用两个栈实现一个队列*/
template<typename T>
class CQueue{
public:
	CQueue();
	~CQueue();

	/*队尾插入结点*/
	void appendTail(const T& val);

	/*队头删除节点*/
	T deleteHead();

private:
	/*定义两个栈*/
	stack<T> s1;
	stack<T> s2;
};

template<typename T>
CQueue<T>::CQueue(){

}

template<typename T>
CQueue<T>::~CQueue(){

}

/*入队: 直接插入栈s1中*/
template<typename T>
void CQueue<T>::appendTail(const T& val){
	s1.push(val);
}

/**
 * 出队思路:  
 * 如果栈s2为空，不停从栈s1中弹出元素压入栈s2中
 * 如果栈s2不为空，直接从栈顶s2中弹出元素
 * 解释: 栈的顺序是后进先出，从s1栈弹出再重新压入新栈s2中使得先插入的元素最先出队，保证和插入顺序一致
 */
template<typename T>
T CQueue<T>::deleteHead(){
	if(s2.size()<=0){
		while(!s1.empty()){
			T& data=s1.top();
			s1.pop();
			s2.push(data);
		}
	}

	if(s2.size()==0){
		cout<<"Queue is empty\n";
		exit(1);
		
	} 

	T head=s2.top();
	s2.pop();
	return head;
}

/*测试出队的元素是否正确*/
void test(char val,char expected){
	if(val==expected)
		cout<< "Test for "<<val<<" passed"<<endl;
	else
		cout<< "Test for "<<val<<" failed"<<endl;
}


int main(){
	CQueue<char> queue;
	/*空队列中删除元素*/
	//queue.deleteHead();

	/*队列中插入元素*/
	queue.appendTail('a');
	queue.appendTail('c');
	queue.appendTail('d');
	queue.appendTail('z');

	/*非空队列中删除元素*/
	char head=queue.deleteHead();
	test(head,'a');

	head=queue.deleteHead();
	test(head,'c');

	/*继续插入元素*/
	queue.appendTail('f');
	head=queue.deleteHead();
	test(head,'d');

	head=queue.deleteHead();
	test(head,'z');

	queue.appendTail('g');
	queue.appendTail('k');

	head=queue.deleteHead();
	test(head,'f');

	head=queue.deleteHead();
	test(head,'g');

	head=queue.deleteHead();
	test(head,'k');

	return 0;
}
