#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;
//子女兄弟链表的节点
template<class T>
struct Node
{
public:
	T data;
	Node<T> * broNode;//指向兄弟的指针
	Node<T> * childNode;//指向子女的指针
	Node():broNode(NULL), childNode(NULL) {}
	Node(T value) :data(value), broNode(NULL), childNode(NULL) {}
};
template<class T>
class Tree
{
public:
	Tree() :root(NULL) {}
	Tree(T data) { root = new Node<T>(data); }
	~Tree() {}
	//添加一个子树，相当于新建家庭
	bool addChildTree(const T & data,const T* childData,int childNum) ;
	//添加一个子节点，相当于添加新的家庭成员
	bool addChildTreeNode(const T & data, T & childData) ;
	//解散节点及其所有子女，相当于解散一个家庭
	bool disbandNode(const T & data) ;
	//更改节点信息，相当于更改家庭成员姓名
	bool changeNodeData(const T & data, T & newData);
	//获得某位家庭成员的第一代子孙信息
	vector<T> getFirstChildTree(const T & data);
private:
	bool searchMark=false;
	Node<T> * root;//家谱祖先指针
	Node<T> * find(const T & data) ;//根据名字查找某位家族成员
	//find的辅助函数，在家谱中进行该名字的搜索
	bool search( Node<T>* begin,const T & data);
	//删除一个节点及其所有子女
	void deleteTree(Node<T> * treeRoot);
	Node<T> * searchResult;
};
template<class T> bool Tree<T>::addChildTree(const T & data, const T* childData,int childNum)
{
	Node<T>* temp = find(data);
	int begin = 0;
	if (temp != NULL)
	{
		if (temp->childNode == NULL)
		{
			temp->childNode = new Node<T>(childData[0]);
			begin = 1;
			temp = temp->childNode;
		}
		else
		{
			temp = temp->childNode;
			while (temp->broNode != NULL)
				temp = temp->broNode;
		}
		for (int i = begin; i < childNum; i++)
		{
			temp->broNode = new Node<T>(childData[i]);
			temp = temp->broNode;
		}
		return true;
	}
	else
		return false;
}
template<class T> bool Tree<T>::addChildTreeNode(const T & data, T & childData)
{
	Node<T> * temp = find(data);
	if (temp != NULL)
	{
		if (temp->childNode == NULL)
			temp->childNode = new Node<T>(childData);
		else
		{
			temp = temp->childNode;
			while (temp->broNode!=NULL)
				temp = temp->broNode;
			temp->broNode = new Node<T>(childData);	
		}
		return true;
	}
	else
	{
		return false;
	}
}
template<class T> bool Tree<T>::changeNodeData(const T & data, T & newData)
{
	Node<T> * temp = find(data);
	if (temp != NULL)
	{
		temp->data = newData;
		return true;
	}
	else
		return false;
}
template<class T> Node<T> * Tree<T>::find(const T & data)
{
	Node<T> * p = root;
	searchMark = false;
	searchResult = NULL;
	if (search(p,data) == true)
	{
		return searchResult;
	}
	else
	{
		cout << "can't find " <<data<< endl;
		return NULL;
	}
 }
template<class T> bool Tree<T>::search(Node<T>* begin, const T & data)
{
	if (searchMark == false)
	{
		if (begin->data == data)
		{
			searchResult = begin;
			searchMark = true;
			return true;
		}
		else
		{
			if (searchMark == false && begin->broNode != NULL)
				if (search(begin->broNode,data) == true)
					return true;
			if (searchMark == false && begin->childNode != NULL)
				if (search(begin->childNode,data) == true)
					return true;
			return false;
		}

	}
	return true;
}
template<class T> void Tree<T>::deleteTree(Node<T>* nodeStart)
{
	if (nodeStart != NULL)
	{
		deleteTree(nodeStart->broNode);
		deleteTree(nodeStart->childNode);
		delete nodeStart;
	}
	return;
}
template<class T> bool Tree<T>::disbandNode(const T & data)
{
	Node<T> * temp = find(data);
	if (temp != NULL)
	{
		deleteTree(temp->childNode);
		temp->childNode = NULL;
		return true;
	}
	else
		return false;
}
template<class T> vector<T> Tree<T>::getFirstChildTree(const T & data)
{
	Node<T> * temp = find(data);
	vector<T> childNodes;
	if (temp != NULL)
	{
		temp = temp->childNode;
		while (temp != NULL)
		{
			childNodes.push_back(temp->data);
			temp = temp->broNode;
		}
	}
	return childNodes;
}
void init()
{
	cout << "**                 家谱管理系统                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**              请选择要执行的操作：            **" << endl;
	cout << "**                 A --- 完善家谱               **" << endl;
	cout << "**                 B --- 添加家庭成员           **" << endl;
	cout << "**                 C --- 解散局部家庭           **" << endl;
	cout << "**                 D --- 更改家庭成员姓名       **" << endl;
	cout << "**                 E --- 退出程序               **" << endl;
	cout << "==================================================" << endl;
	cout << "首先建立一个家谱！" << endl;
}
Tree<string> * familyTree;
void printFirstChildren(string & name)
{
	vector<string> firstChildren;
	cout << name << "的第一代子孙是：";
	firstChildren = familyTree->getFirstChildTree(name);
	if (firstChildren.size() > 0) {
		for (int i = 1; i <= firstChildren.size(); i++)
			cout << firstChildren[i - 1] << " ";
		cout << endl << endl;
	}
	else
		cout << "无"<<endl;
	
}

int main()
{
	init();
	cout << "请输入祖先的姓名：";
	string ancestor;
	cin >> ancestor;
	cout << "此家谱的祖先是：" << ancestor << endl << endl;
	familyTree = new Tree<string>(ancestor);
	char operation;
	bool endMark = false;
	while (!endMark)
	{
		cout << "请选择要执行的操作：";
		cin >> operation;
		string name;
		string newName;
		string childName;
		string * childNames;
		int childNum;
		switch (operation)
		{
		case 'A':
			cout << "请输入要建立家庭的人的姓名：";
			cin >> name;
			cout << "请输入" << name << "的儿女的人数:";
			cin >> childNum;
			childNames = new string[childNum];
			cout << "请以此输入" << name << "的儿女姓名:";
			for (int i = 0; i < childNum; i++)
				cin >> childNames[i];
			if (familyTree->addChildTree(name, childNames, childNum) == true)
			{
				printFirstChildren(name);
			}
			else
				cout << "找不到"<<name<< endl << endl;
			break;
		case 'B':
			cout << "请输入要添加儿子（或女儿）的人的姓名：";
			cin>> name;
			cout << "请输入" << name << "新添加的儿子或女儿的姓名：";
			cin >> childName;
			if (familyTree->addChildTreeNode(name, childName) == true)
			{
				printFirstChildren(name);
			}
			else
				cout << "未添加成功"<<endl<<endl;
			break;
		case 'C':
			cout << "请输入要解散家庭的人的姓名:";
			cin >> name;
			cout << "要解散的家庭的人是"<<name<<endl;
			printFirstChildren(name);
			if (familyTree->disbandNode(name) == false)
				cout << "解散失败！" << endl;
			break;
		case 'D':
			cout << "请输入要更改姓名的人的目前的姓名：";
			cin >> name;
			cout << "请输入更改后的姓名：";
			cin >> newName;
			if (familyTree->changeNodeData(name, newName) == true)
				cout << name << "已更名为" << newName << endl<<endl;
			break;
		case 'E':
			endMark = true;
			break;
		default:
			cout << "您输入的指令有误，请重新输入!" << endl<<endl;
			break;
		}
	}
}