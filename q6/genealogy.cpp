#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;
//��Ů�ֵ�����Ľڵ�
template<class T>
struct Node
{
public:
	T data;
	Node<T> * broNode;//ָ���ֵܵ�ָ��
	Node<T> * childNode;//ָ����Ů��ָ��
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
	//���һ���������൱���½���ͥ
	bool addChildTree(const T & data,const T* childData,int childNum) ;
	//���һ���ӽڵ㣬�൱������µļ�ͥ��Ա
	bool addChildTreeNode(const T & data, T & childData) ;
	//��ɢ�ڵ㼰��������Ů���൱�ڽ�ɢһ����ͥ
	bool disbandNode(const T & data) ;
	//���Ľڵ���Ϣ���൱�ڸ��ļ�ͥ��Ա����
	bool changeNodeData(const T & data, T & newData);
	//���ĳλ��ͥ��Ա�ĵ�һ��������Ϣ
	vector<T> getFirstChildTree(const T & data);
private:
	bool searchMark=false;
	Node<T> * root;//��������ָ��
	Node<T> * find(const T & data) ;//�������ֲ���ĳλ�����Ա
	//find�ĸ����������ڼ����н��и����ֵ�����
	bool search( Node<T>* begin,const T & data);
	//ɾ��һ���ڵ㼰��������Ů
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
	cout << "**                 ���׹���ϵͳ                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**              ��ѡ��Ҫִ�еĲ�����            **" << endl;
	cout << "**                 A --- ���Ƽ���               **" << endl;
	cout << "**                 B --- ��Ӽ�ͥ��Ա           **" << endl;
	cout << "**                 C --- ��ɢ�ֲ���ͥ           **" << endl;
	cout << "**                 D --- ���ļ�ͥ��Ա����       **" << endl;
	cout << "**                 E --- �˳�����               **" << endl;
	cout << "==================================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;
}
Tree<string> * familyTree;
void printFirstChildren(string & name)
{
	vector<string> firstChildren;
	cout << name << "�ĵ�һ�������ǣ�";
	firstChildren = familyTree->getFirstChildTree(name);
	if (firstChildren.size() > 0) {
		for (int i = 1; i <= firstChildren.size(); i++)
			cout << firstChildren[i - 1] << " ";
		cout << endl << endl;
	}
	else
		cout << "��"<<endl;
	
}

int main()
{
	init();
	cout << "���������ȵ�������";
	string ancestor;
	cin >> ancestor;
	cout << "�˼��׵������ǣ�" << ancestor << endl << endl;
	familyTree = new Tree<string>(ancestor);
	char operation;
	bool endMark = false;
	while (!endMark)
	{
		cout << "��ѡ��Ҫִ�еĲ�����";
		cin >> operation;
		string name;
		string newName;
		string childName;
		string * childNames;
		int childNum;
		switch (operation)
		{
		case 'A':
			cout << "������Ҫ������ͥ���˵�������";
			cin >> name;
			cout << "������" << name << "�Ķ�Ů������:";
			cin >> childNum;
			childNames = new string[childNum];
			cout << "���Դ�����" << name << "�Ķ�Ů����:";
			for (int i = 0; i < childNum; i++)
				cin >> childNames[i];
			if (familyTree->addChildTree(name, childNames, childNum) == true)
			{
				printFirstChildren(name);
			}
			else
				cout << "�Ҳ���"<<name<< endl << endl;
			break;
		case 'B':
			cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
			cin>> name;
			cout << "������" << name << "����ӵĶ��ӻ�Ů����������";
			cin >> childName;
			if (familyTree->addChildTreeNode(name, childName) == true)
			{
				printFirstChildren(name);
			}
			else
				cout << "δ��ӳɹ�"<<endl<<endl;
			break;
		case 'C':
			cout << "������Ҫ��ɢ��ͥ���˵�����:";
			cin >> name;
			cout << "Ҫ��ɢ�ļ�ͥ������"<<name<<endl;
			printFirstChildren(name);
			if (familyTree->disbandNode(name) == false)
				cout << "��ɢʧ�ܣ�" << endl;
			break;
		case 'D':
			cout << "������Ҫ�����������˵�Ŀǰ��������";
			cin >> name;
			cout << "��������ĺ��������";
			cin >> newName;
			if (familyTree->changeNodeData(name, newName) == true)
				cout << name << "�Ѹ���Ϊ" << newName << endl<<endl;
			break;
		case 'E':
			endMark = true;
			break;
		default:
			cout << "�������ָ����������������!" << endl<<endl;
			break;
		}
	}
}