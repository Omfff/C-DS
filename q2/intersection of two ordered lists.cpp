#include<iostream>
using namespace std;

class orderedList
{
	class node
	{
	public:
		int num;
		node * next;
		node() { next = NULL; };
		friend orderedList* intersection(orderedList * s1, orderedList * s2);
	};
	
public:
	node * first;
	orderedList() { first = NULL; };
	void insertNode(void);
	friend orderedList* intersection(orderedList * s1, orderedList * s2);
	~orderedList();
};
void orderedList::insertNode(void)
{
	int num;
	cin >> num;
	node * aheadNode;
	while (num != -1)
	{
		node * tempNode = new node;
		tempNode->num = num;
		if (first == NULL)
			first = tempNode;
		else
			aheadNode->next = tempNode;
		aheadNode = tempNode;
		cin >> num;
	}
}
orderedList * intersection(orderedList * s1, orderedList * s2)
{
	orderedList * s3 = new orderedList;
	//s1 或 s2 中有一个为null 则交集为空
	if (s1->first != NULL && s2->first != NULL)
	{
		orderedList::node * tempNode1 = s1->first;
		orderedList::node * tempNode2 = s2->first;
		orderedList::node * tempNode3;
		//s1、s2的当前指针有一个为null，则结束
		while (tempNode1 != NULL && tempNode2 != NULL)
		{
			//如果s1中当前指针指向的值大于s2中当前指针指向的值
			//s2当前指针后移，否则s1当前指针后移
			if (tempNode1->num > tempNode2->num)
				tempNode2 = tempNode2->next;
			else if (tempNode1->num < tempNode2->num)
				tempNode1 = tempNode1->next;
			else
			{
				//s1、s2的当前指针指向的节点值相等，则把结果链中的当前指针的next指向该节点
				if (s3->first == NULL)
					s3->first = tempNode1;
				else
					tempNode3->next = tempNode1;
				//s3、s2、s1中的指针全部后移一位
				tempNode3 = tempNode1;
				tempNode1 = tempNode1->next;
				tempNode2 = tempNode2->next;
			}
		}
	}
	if (s3->first == NULL)
		cout << "NULL" << endl;
	else
	{
		orderedList::node * tempNode = s3->first;
		while (tempNode != NULL)
		{
			cout << tempNode->num<<"  ";
			tempNode = tempNode->next;
		}
		cout << endl;
	}
	return s3;
}
orderedList::~orderedList() {
	node * temp;
	if (first != NULL) {
		temp = first->next;
		delete first;
		first = temp;
	}
}
int main()
{
	orderedList * s1 = new orderedList;
	orderedList * s2 = new orderedList;
	
	s1->insertNode();
	s2->insertNode();
	intersection(s1, s2);
	system("pause");

}