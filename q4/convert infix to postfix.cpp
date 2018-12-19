#include<iostream>
#include<string>
#include<map>
using namespace std;
template<class T>
class node
{
public:
	T information;
	node<T>* nextNode;
	node(T data) :information(data), nextNode(NULL) {}
	node() :nextNode(NULL) {}
};
template<class T>
class stack
{
public:
	stack() :top(NULL) {};
	stack(const T&topP) { top = NULL; push(topP); }
	~stack();
	bool push(const T& data);
	bool pop(T& data);
	bool getTop(T & data)const;//���ջ��Ԫ��
	void clear();
	friend ostream & operator<< (ostream & os, stack<T> s)
	{
		node<T> * temp = s.top;
		while (temp->nextNode != NULL)
		{
			cout << temp->information << " ";
			temp = temp->nextNode;
		}
		return os;
	}

private:
	node<T> * top;//ջ��
};
template<class T> stack<T>::~stack()
{
	clear();
}
template<class T> void stack<T>::clear()
{
	if (top == NULL)
		return;
	else
	{
		T data;
		while (top != NULL)
		{
			pop(data);
		}
	}
}
template<class T> bool stack<T>::pop(T&data)
{
	if (top == NULL)
		return false;
	else
	{
		node<T> * temp = top;
		top = top->nextNode;
		data = temp->information;
		//delete temp;
		return true;
	}
}
template<class T> bool stack<T>::getTop(T & data)const
{
	if (top != NULL)
	{
		data = top->information;
		return true;
	}
	else
		return false;
}
template<class T> bool stack<T>::push(const T & data)
{
	node<T> * temp = new node<T>(data);
	temp->nextNode = top;
	top = temp;
	return true;
}
int main()
{
	cout << "��������׺���ʽ:" << endl;
	string expression;
	getline(cin, expression);
	
	stack<char> eStack;
	eStack.push('#');
	map<char, int>isp;//ջ��������
	isp.insert(make_pair('*', 5));
	isp.insert(make_pair('/', 5));
	isp.insert(make_pair('+', 3));
	isp.insert(make_pair('-', 3));
	isp.insert(make_pair('#', 0));
	isp.insert(make_pair('(', 1));
	isp.insert(make_pair(')', 6));

	map<char, int>icp;//ջ��������
	icp.insert(make_pair('*', 4));
	icp.insert(make_pair('/', 4));
	icp.insert(make_pair('+', 2));
	icp.insert(make_pair('-', 2));
	icp.insert(make_pair('#', 0));
	icp.insert(make_pair('(', 6));
	icp.insert(make_pair(')', 1));
	cout << "��Ӧ�ĺ�׺���ʽΪ��";
	char temp;
	char output;
	for (int i = 0; i < expression.length(); i++)
	{
		char exp = expression[i];
		if ((exp <= '9'&&exp >= '0') || exp == '.')
		{
			cout << exp;//���ֻ�С����ֱ�����
			if (!((expression[i + 1] <= '9'&&expression[i + 1] >= '0') || expression[i + 1] == '.'))
				cout << ' ';
		}
		else if (exp == '+' || exp == '-' || exp == '/' || exp == '*')
		{
			//�������ţ���ջ����Ԫ�����ȼ����бȽ�
			eStack.getTop(temp);
			//+,-��Ϊ���������ű�ʾ
			if ((exp == '+' || exp == '-') && (i == 0 || expression[i - 2] == '('))
			{
				if (exp == '-')
					cout << exp;
				continue;
			}
			//
			while (isp[temp] > icp[exp])
			{
				eStack.pop(output);
				if (output != '(')
					cout << output << " ";
				eStack.getTop(temp);
			}
			eStack.push(exp);
		}
		else if (exp == '(')
			eStack.push(exp);
		else if (exp == ')')
		{
			eStack.pop(output);
			while (output != '(')
			{
				cout << output << " ";
				eStack.pop(output);
			}
			eStack.getTop(temp);
		}
		else
			continue;
	}
	cout << eStack;
	system("pause");
}
