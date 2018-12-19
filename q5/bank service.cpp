#include<iostream>
using namespace std;
template<class T>
class node
{
public:
	T information;//�û���Ϣ
	node<T> * nextNode;//��һ���ڵ㣨�û���
	node(T & data) :information(data), nextNode(NULL) {};
	node() :nextNode(NULL) {};
};
 template<class T>
 class quque
 {
 public:
	 quque() :head(NULL), tail(NULL) {};
	 ~quque() { clear(); };
	 bool enQuque(T & data);//�Ӷ�β�������
	 bool getFront(T & data);//��ö����е�һ���ڵ㣨�û���
	 bool deQuque(T & date);//�Ӷ��׳���
	 void clear();
	 node<T> * head;//����ָ��
	 node<T> * tail;//��βָ��
 };
 template<class T> bool quque<T>::deQuque(T & data)
 {
	 if (head != NULL)
	 {//���׳����У�����headָ�����
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
		 {//����Ϊ�վ�ֱ�ӷ������
			 head = temp;
			 tail = temp;
		 }
		 else
		 {
			 //�����β��ָ�����
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
		 cout << "������˿���������";
		 cin >> totalNum;
		 if (totalNum <= 0)
			 cout << "�˿�����̫�٣�" << endl;
		 else if (totalNum > 1000)
			 cout << "�˿�����̫�࣬ϵͳ�޷����ܣ�" << endl;
		 else
			 break;
	 }
	 int * customers = new int[totalNum];
	 cout << "������" << totalNum << "λ�˿͵ı��:";
	 for (int i = 0; i < totalNum; i++)
	 {
		 cin >> customers[i];
		 if (customers[i] % 2 == 0)//���Ϊż���Ĺ˿ͽ���B���ڶ���
			 B.enQuque(customers[i]);
		 else
			 A.enQuque(customers[i]);//���Ϊ�����Ĺ˿ͽ���A���ڶ���
	 }
	 int customerA;
	 int customerB;
	 cout << "���ҵ����˿͵����У�";
	 //ģ��ʱ�䣬����A���ڵ�ÿλ�˿ʹ���ʱ��Ϊ1����B���ڵ�ÿλ�˿ʹ���ʱ��Ϊ2
	 for (int i = 1; i <= 2 * totalNum; i++)
	 {
		 //���A���ڴ�����ɵĹ˿�
		 if (A.deQuque(customerA))
			 cout << customerA<<' ';
		 //��A��B����ͬʱ������2���˿ͣ�B���ں����
		 if (i % 2 == 0 && B.deQuque(customerB) == true)
			 cout << customerB<<' ';
	 }
	 system("pause");
 }