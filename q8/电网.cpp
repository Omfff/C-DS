#include<iostream>
#include<vector> 
#include<algorithm>
#include<iomanip>
#define MAX_SIZE 2000000
using namespace std;
struct Edge
{
	char dest;
	int destPos;
	int cost;
	Edge * next;
	Edge(char dest, int cost,int destPos) :dest(dest), cost(cost),next() ,destPos(destPos){}
};
struct Vertex
{
	char name;
	int pos;
	Edge * head;
	Vertex(char name,int pos):name(name),head(NULL),pos(pos){}
};
class Graph {
private:
	vector<Vertex*> nodeArray;//节点数组
	int edgeNum;//当前边数
	int vertexNum;//当前节点数
	int maxVertex;//允许最大的节点数
	int getVertexposition(char name)const;//获得节点在节点数组中的位置
	void linkEdge(Vertex* v, Edge * Edge);//向邻接表插入边的辅助数组
public:
	Graph() { maxVertex = (int)nodeArray.max_size() ; edgeNum = 0; vertexNum = 0; };
	~Graph();
	int getvertexNum() { return vertexNum; }
	int getedgeNum() { return edgeNum; }
	bool insertEdge(char begin, char dest, int cost);
	bool addVertex(char name);
	//获得该节点第一个邻接出边
	Edge * getFirstNeighbor(const Vertex * vertex)const;
	//获得该节点的邻接出边x的下一个邻接出边
	Edge * getNextNeighbor(const Vertex * vertex, const Edge * edge)const;
	//获得名字为name的节点
	Vertex * getVertex(char name);
};
int Graph::getVertexposition(char name)const {
	for (int i = 0; i < vertexNum; i++) {
		if (nodeArray[i]->name == name)
			return i;
	}
	return -1;
}
void  Graph::linkEdge(Vertex* v, Edge * edge) {
	if (v->head == NULL) {
		v->head = edge;
		return;
	}
	else {
		Edge * temp = v->head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = edge;

	}
}
Graph::~Graph() {
	vector<Vertex*>::iterator ite;
	for (ite = nodeArray.begin(); ite != nodeArray.end(); ite++) {
		if (*ite != NULL) {
			Edge * temp = (*ite)->head;
			Edge * next;
			while (temp != NULL) {
				next = temp->next;
				delete temp;
				temp = next;
			}
			delete *ite;
		}
	}
	nodeArray.clear();
}
Vertex * Graph::getVertex(char name) {
	int pos = getVertexposition(name);
	if (pos != -1)
		return nodeArray[pos];
	else
		return NULL;
}
bool Graph::addVertex(char name) {
	if (vertexNum < maxVertex) {
		nodeArray.push_back(new Vertex(name,vertexNum));
		vertexNum++;
		return true;
	}
	else
		return false;
}
bool Graph::insertEdge(char begin, char dest, int cost) {
	int beginPos = getVertexposition(begin);
	int destPos = getVertexposition(dest);
	bool result1=true, result2=true;
	if (beginPos == -1) {
		result1 = addVertex(begin);
		beginPos = vertexNum - 1;
	}
	if (destPos == -1) {
		result2 = addVertex(dest);
		destPos = vertexNum - 1;
	}
	if (result1&&result2) {
		linkEdge(nodeArray[beginPos], new Edge(dest, cost, destPos));
		linkEdge(nodeArray[destPos], new Edge(begin, cost, beginPos));
		edgeNum++;
		return true;
	}
	else
		return false;
}
Edge * Graph::getFirstNeighbor(const Vertex * vertex) const{
	int pos = getVertexposition(vertex->name);
	if (pos == -1) return NULL;
	else
		return nodeArray[pos]->head;
}
Edge * Graph::getNextNeighbor(const Vertex * vertex,const Edge * edge)const {
	int pos = getVertexposition(vertex->name);
	if (pos == -1) return NULL;
	Edge * temp = nodeArray[pos]->head;
	while (temp->dest != edge->dest) {
		temp = temp->next;
	}
	return temp->next;
}
struct TreeNode {
	int tail, head;//图中边的的起始位置，和终点位置
	char begin, dest;//边的两个节点的名字
	int cost;//权值
	TreeNode() :tail(-1), head(-1) {}
};
class MinSpanTree {
	TreeNode*  tree;
	int maxsize;
	int currentNum;
	int begin=-1;//树中第一个节点所在数组中的位置
public :
	MinSpanTree() :currentNum(0), maxsize(MAX_SIZE) {
		tree = new TreeNode[maxsize];
	}
	~MinSpanTree();
	int insert(TreeNode & node);
	//重载输出
	friend void operator<<(ostream &out,MinSpanTree & minTree);
};
MinSpanTree::~MinSpanTree() {
	delete tree;
}
void operator <<(ostream &out, MinSpanTree & minTree) {

	if (minTree.begin != -1) {
		int pos = minTree.begin;
		for (int i = 0; i < minTree.currentNum; i++) {
			out << minTree.tree[pos].begin << "-<" << minTree.tree[pos].cost << ">->" << minTree.tree[pos].dest << "   ";
			//下一个节点位置
			pos = minTree.tree[pos].tail;
		}
		cout << endl;
	}
}
int MinSpanTree::insert(TreeNode & node) {
	if (begin == -1)
		begin = node.head;
	tree[node.head] = node;
	currentNum++;
	return currentNum;
}
//用来生成最小堆的自定义比较函数
struct Greater
{
	bool operator()(TreeNode * a, TreeNode *b) const{
		return a->cost > b->cost;
	}
};
void deleteMinHeap(vector<TreeNode*>& minHeap) {
	for (vector<TreeNode *>::iterator it = minHeap.begin(); it != minHeap.end(); it++)
		if (*it != NULL)
		{
			delete *it;
			*it = NULL;
		}
	minHeap.clear();
}
void prim(Graph * g, MinSpanTree * minTree,char begin) {
	//获取起始的节点
	Vertex * beginVertex=g->getVertex(begin);
	int vertexNum, edgeNum, beginPos;
	beginPos = beginVertex->pos;
	vertexNum = g->getvertexNum();
	edgeNum = g->getedgeNum();
	//辅助数组，用来及记录节点是否已经存在最小生成树中
	bool * treeVertex = new bool[vertexNum];
	//初始化
	for (int i = 0; i < vertexNum; i++)
		treeVertex[i] = false;
	//最小堆用来存储当前可选的边
	vector<TreeNode*>minHeap;
	vector<TreeNode*>::iterator ite;
	TreeNode * tempTreeNode;
	treeVertex[beginPos] = true;
	Vertex * tempVertex = beginVertex;
	Edge * tempEdge;
	Greater greater;
	int count=1;
	do {
		tempEdge = g->getFirstNeighbor(tempVertex);
		//把新加入最小生成树的这个图中节点的所有
		//另一个端点不在最小生成树里的邻接边加入到最小堆中
		while (tempEdge != NULL) {
			if (treeVertex[tempEdge->destPos] == false) {
				tempTreeNode = new TreeNode();
				tempTreeNode->begin = tempVertex->name;
				tempTreeNode->dest = tempEdge->dest;
				tempTreeNode->cost = tempEdge->cost;
				tempTreeNode->head = tempVertex->pos;
				tempTreeNode->tail = tempEdge->destPos;
				minHeap.push_back(tempTreeNode);
			}
			tempEdge = g->getNextNeighbor(tempVertex, tempEdge);
		}
		//重新调整最小堆
		make_heap(minHeap.begin(), minHeap.end(),greater);
		//只要最小堆不为空，就进行插入最小生成树操作
		while (minHeap.empty() == false&&count<vertexNum) {
			ite = minHeap.begin();//堆顶指针
			//另一个端点不在最小生成树里，则加入最小生成树中
			if (treeVertex[(*ite)->tail] == false) {
				treeVertex[(*ite)->tail] = true;
				minTree->insert(*(*ite));
				tempVertex = g->getVertex((*ite)->dest);
				count++;
				//弹出堆顶元素，调整最小堆
				pop_heap(minHeap.begin(), minHeap.end(), greater);
				minHeap.pop_back();
				break;
			}
			//另一个端点在最小生成树里，则直接弹出堆顶元素，调整最小堆
			pop_heap(minHeap.begin(), minHeap.end(), greater);
			minHeap.pop_back();
		}
	} while (count < vertexNum);
	//释放最小堆中的节点内存
	deleteMinHeap(minHeap);
}
void a(Graph *g);
void b(Graph *g);
void c(Graph *g,MinSpanTree * minTree);
void d(MinSpanTree *minTree);
int main() {
	cout << "**" << setw(12) << " " << "电网造价模拟系统" << setw(12) << " " << "**"<<endl;
	cout << setfill('=') << setw(44) << "=" << endl;
	cout << "**" << setfill(' ')<<setw(12) << " " << "a --- 创建电网顶点" << setw(10) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "b --- 添加电网的边" << setw(10) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "c --- 构造最小生成树" << setw(8) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "d --- 显示最小生成树" << setw(8) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "e --- 退出 程序" << setw(13) << " " << "**" << endl;
	cout << setfill('=') << setw(44) << "=" << endl;
	char command;
	cout << "请选择操作:";
	cin >> command;
	Graph * g = new Graph();
	MinSpanTree * minTree = new MinSpanTree();
	while (command != 'e') {
		switch (command) {
		case 'a':
			a(g);
			break;
		case 'b':
			b(g);
			break;
		case 'c':
			c(g,minTree);
			break;
		case 'd':
			d(minTree);
			break;
		default:
			cout << "指令有误，请重新输入" << endl;
			break;
		}
		cout << "请选择操作：";
		cin >> command;
	}
}
void a(Graph *g) {
	int vertexNum;
	char Vertexname;
	while (1) {
		cout << "请输入顶点的个数：";
		cin >> vertexNum;
		if (vertexNum >= 2) {
			cout << "请依次输入各顶点名称" << endl;
			for (int i = 0; i < vertexNum; i++) {
				cin >> Vertexname;
				g->addVertex(Vertexname);
			}
			break;
		}
		else {
			cout << "输入有误" << endl;
		}
	}
}
void b(Graph * g) {
	if (g->getvertexNum() <= 0) {
		cout << "请先输入顶点" << endl;
		return;
	}
	char begin, dest;
	int cost;
	while (1) {
		cout << "输入两个顶点及边：";
		cin >> begin >> dest >> cost;
		if (begin == '?'&&dest == '?')
			break;
		else
			g->insertEdge(begin, dest, cost);
	}
}
void c(Graph * g,MinSpanTree * minTree) {
	if (g->getedgeNum() < g->getvertexNum() - 1) {
		cout << "输入的边数太少，请先输入边" << endl;
		return;
	}
	cout << "请输入起始顶点：";
	char begin;
	cin >> begin;
	prim(g, minTree, begin);
	cout << "生成prim最小生成树!" << endl;
}
void d(MinSpanTree * minTree) {

	cout << *minTree;
}
