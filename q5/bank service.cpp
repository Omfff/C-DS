#include<iostream>
using namespace std;
template<class T>
class node
{
public:
	T information;//用户信息
	node<T> * nextNode;//下一个节点（用户）
	node(T & data) :information(data), nextNode(NULL) {};
	node() :nextNode(NULL) {};
};
 template<class T>
 class quque
 {
 public:
	 quque() :head(NULL), tail(NULL) {};
	 ~quque() { clear(); };
	 bool enQuque(T & data);//从队尾进入队列
	 bool getFront(T & data);//获得队列中第一个节点（用户）
	 bool deQuque(T & date);//从队首出队
	 void clear();
	 node<T> * head;//队首指针
	 node<T> * tail;//队尾指针
 };
 template<class T> bool quque<T>::deQuque(T & data)
 {
	 if (head != NULL)
	 {//队首出队列，并把head指针后移
		 data = head->information;
		 node<T> * temp = head->nextNode;
		 delete head;
		 head = temp;
		 return true;
	 }
	 else
		 return false;
 }
 template<class T> bool quque<T>::enQuque(T & data)
 {
	 node<T> *temp = new node<T>(data);
	 if (temp != NULL)
	 {
		 if (head == NULL)
		 {//队列为空就直接放入队首
			 head = temp;
			 tail = temp;
		 }
		 else
		 {
			 //链入队尾，指针后移
			 tail->nextNode = temp;
			 tail = temp;
		 }
		 return true;
	 }
	 else
		 return false;
 }
 template<class T> void quque<T>::clear()
 {
	 node<T> * temp ;
	 while (head != NULL)
	 {
		 temp = head;
		 head = head->nextNode;
		 delete temp;
	 }
	 tail = NULL;
 }
 template<class T> bool quque<T>::getFront(T &data)
 {
	 if (head == NULL)
		 return false;
	 else
	 {
		 data = head->information;
		 return true;
	 }
 }
 int main()
 {
	 int totalNum;
	 quque<int> A;
	 quque<int> B;
	 while (1) {
		 cout << "请输入顾客总人数：";
		 cin >> totalNum;
		 if (totalNum <= 0)
			 cout << "顾客数量太少！" << endl;
		 else if (totalNum > 1000)
			 cout << "顾客数量太多，系统无法承受！" << endl;
		 else
			 break;
	 }
	 int * customers = new int[totalNum];
	 cout << "请输入" << totalNum << "位顾客的编号:";
	 for (int i = 0; i < totalNum; i++)
	 {
		 cin >> customers[i];
		 if (customers[i] % 2 == 0)//编号为偶数的顾客进入B窗口队列
			 B.enQuque(customers[i]);
		 else
			 A.enQuque(customers[i]);//编号为奇数的顾客进入A窗口队列
	 }
	 int customerA;
	 int customerB;
	 cout << "完成业务处理顾客的序列：";
	 //模拟时间，假设A窗口的每位顾客处理时间为1，则B窗口的每位顾客处理时间为2
	 for (int i = 1; i <= 2 * totalNum; i++)
	 {
		 //输出A窗口处理完成的顾客
		 if (A.deQuque(customerA))
			 cout << customerA<<' ';
		 //当A和B窗口同时处理完2个顾客，B窗口后输出
		 if (i % 2 == 0 && B.deQuque(customerB) == true)
			 cout << customerB<<' ';
	 }
	 system("pause");
 }