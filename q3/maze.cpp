#include<iostream>
using namespace std;
struct mazePos
{
	int x;
	int y;
	int dir;//存储当前搜索的方向
	mazePos(int x, int y) { this->x = x; this->y = y; }
	mazePos() {}
};
template<class T>
class node
{	
public:
	T information;
	node * nextNode;
	node() :nextNode(NULL){}
	node(T data) :information(data) ,nextNode(NULL){}
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
	bool getTop(T & data)const;
	void clear();
	bool isEmpty() {
		if (top == NULL)
			return true;
		else
			return false;
	}
	friend ostream & operator<< (ostream & os, stack<T> s)
	{
		node<T> * temp = s.top;
		while (temp != NULL)
		{
			os << "<" << temp->information.x << "," << temp->information.y << ">";
			temp = temp->nextNode;
			if(temp!=NULL)
				os << "--->";
		}
		return os;
	}

private:
	node<T> * top;
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
		if(temp!=NULL)
			delete temp;
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

int go[2][8] = { {-1,0,1,0,-1,1,1,-1},{0,1,0,-1,1,1,-1,-1} };
int maze[7][7] = { { 1,1,1,1,1,1,1 },
{ 1,0,1,1,1,1,1 },
{ 1,0,1,1,1,1,1 },
{ 1,0,0,0,1,1,1 },
{ 1,0,1,0,0,0,1 },
{ 1,0,1,1,1,0,1 },
{ 1,1,1,1,1,1,1 } };

void findPath(mazePos start, mazePos end, int sizeX, int sizeY)
{

	int ** maze2 = new int*[sizeX];
	for (int i = 0; i < sizeX; i++)
		maze2[i] = new int[sizeY];
	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++)
			maze2[i][j] = maze[i][j];

	mazePos temp = start;
	temp.dir = 0;
	stack<mazePos> mStack(temp);
	maze2[start.x][start.y] = 1;
	int dir = 0;
	while ((temp.x!=end.x||temp.y!=end.y)&&mStack.isEmpty()==false)
	{
		while(dir<4)
		{
			temp.x += go[0][dir];
			temp.y += go[1][dir];
			temp.dir = dir;
			if (temp.x == end.x&&temp.y == end.y)
			{
				cout << "<"<<end.x<<","<<end.y << ">"<<"--->";
				cout << mStack;
				
				return;
			}	
			if (maze2[temp.x][temp.y] == 0 && maze[temp.x][temp.y] == 0)
			{
				maze2[temp.x][temp.y] = 1;
				mStack.push(temp);
				dir = 0;
			}
			else
			{
				temp.x -= go[0][dir];
				temp.y -= go[1][dir];
				dir++;
			}
		}
		if (temp.x == start.x&&temp.y == start.y&&temp.dir == 3) {
			cout << "不存在有效路径" << endl;
			return;
		}	
		mStack.pop(temp);
		mStack.getTop(temp);
		dir = temp.dir;
		
	}

	for (int i = 0; i < sizeX;i++)
	{
		delete [] maze2[i];
	}
	delete[] maze2;
}

int main()
{
	//cout << "请选择输入命令来选择使用内置地图，或者输入地图" << endl;
	//cout << "0 代表内置地图" << endl;
	//cout << "1 代表输入地图" << endl;
	//int command;
	//cin >> command;
	cout << "迷宫地图：" << endl;
	for (int i = 0; i < 7; i++)
	{
		if (i == 0)
		{
			for (int t = 0; t < 7; t++)
				cout << "	" << t << "列";
			cout << endl;
		}
		cout << i << "行";
		for (int j = 0; j < 7; j++)
			
			if (maze[i][j] == 0)
				cout << "  	0";
			else
				cout << "	#";
		cout << endl;
	}
	cout << "迷宫路径:" << endl;
	mazePos start(1, 1);
	mazePos end(5, 5);
	findPath(end, start, 7, 7);
	system("pause");
}
