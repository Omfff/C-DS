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
	vector<Vertex*> nodeArray;//�ڵ�����
	int edgeNum;//��ǰ����
	int vertexNum;//��ǰ�ڵ���
	int maxVertex;//�������Ľڵ���
	int getVertexposition(char name)const;//��ýڵ��ڽڵ������е�λ��
	void linkEdge(Vertex* v, Edge * Edge);//���ڽӱ����ߵĸ�������
public:
	Graph() { maxVertex = (int)nodeArray.max_size() ; edgeNum = 0; vertexNum = 0; };
	~Graph();
	int getvertexNum() { return vertexNum; }
	int getedgeNum() { return edgeNum; }
	bool insertEdge(char begin, char dest, int cost);
	bool addVertex(char name);
	//��øýڵ��һ���ڽӳ���
	Edge * getFirstNeighbor(const Vertex * vertex)const;
	//��øýڵ���ڽӳ���x����һ���ڽӳ���
	Edge * getNextNeighbor(const Vertex * vertex, const Edge * edge)const;
	//�������Ϊname�Ľڵ�
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
	int tail, head;//ͼ�бߵĵ���ʼλ�ã����յ�λ��
	char begin, dest;//�ߵ������ڵ������
	int cost;//Ȩֵ
	TreeNode() :tail(-1), head(-1) {}
};
class MinSpanTree {
	TreeNode*  tree;
	int maxsize;
	int currentNum;
	int begin=-1;//���е�һ���ڵ����������е�λ��
public :
	MinSpanTree() :currentNum(0), maxsize(MAX_SIZE) {
		tree = new TreeNode[maxsize];
	}
	~MinSpanTree();
	int insert(TreeNode & node);
	//�������
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
			//��һ���ڵ�λ��
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
//����������С�ѵ��Զ���ȽϺ���
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
	//��ȡ��ʼ�Ľڵ�
	Vertex * beginVertex=g->getVertex(begin);
	int vertexNum, edgeNum, beginPos;
	beginPos = beginVertex->pos;
	vertexNum = g->getvertexNum();
	edgeNum = g->getedgeNum();
	//�������飬��������¼�ڵ��Ƿ��Ѿ�������С��������
	bool * treeVertex = new bool[vertexNum];
	//��ʼ��
	for (int i = 0; i < vertexNum; i++)
		treeVertex[i] = false;
	//��С�������洢��ǰ��ѡ�ı�
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
		//���¼�����С�����������ͼ�нڵ������
		//��һ���˵㲻����С����������ڽӱ߼��뵽��С����
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
		//���µ�����С��
		make_heap(minHeap.begin(), minHeap.end(),greater);
		//ֻҪ��С�Ѳ�Ϊ�գ��ͽ��в�����С����������
		while (minHeap.empty() == false&&count<vertexNum) {
			ite = minHeap.begin();//�Ѷ�ָ��
			//��һ���˵㲻����С��������������С��������
			if (treeVertex[(*ite)->tail] == false) {
				treeVertex[(*ite)->tail] = true;
				minTree->insert(*(*ite));
				tempVertex = g->getVertex((*ite)->dest);
				count++;
				//�����Ѷ�Ԫ�أ�������С��
				pop_heap(minHeap.begin(), minHeap.end(), greater);
				minHeap.pop_back();
				break;
			}
			//��һ���˵�����С���������ֱ�ӵ����Ѷ�Ԫ�أ�������С��
			pop_heap(minHeap.begin(), minHeap.end(), greater);
			minHeap.pop_back();
		}
	} while (count < vertexNum);
	//�ͷ���С���еĽڵ��ڴ�
	deleteMinHeap(minHeap);
}
void a(Graph *g);
void b(Graph *g);
void c(Graph *g,MinSpanTree * minTree);
void d(MinSpanTree *minTree);
int main() {
	cout << "**" << setw(12) << " " << "�������ģ��ϵͳ" << setw(12) << " " << "**"<<endl;
	cout << setfill('=') << setw(44) << "=" << endl;
	cout << "**" << setfill(' ')<<setw(12) << " " << "a --- ������������" << setw(10) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "b --- ��ӵ����ı�" << setw(10) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "c --- ������С������" << setw(8) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "d --- ��ʾ��С������" << setw(8) << " " << "**" << endl;
	cout << "**" << setw(12) << " " << "e --- �˳� ����" << setw(13) << " " << "**" << endl;
	cout << setfill('=') << setw(44) << "=" << endl;
	char command;
	cout << "��ѡ�����:";
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
			cout << "ָ����������������" << endl;
			break;
		}
		cout << "��ѡ�������";
		cin >> command;
	}
}
void a(Graph *g) {
	int vertexNum;
	char Vertexname;
	while (1) {
		cout << "�����붥��ĸ�����";
		cin >> vertexNum;
		if (vertexNum >= 2) {
			cout << "�������������������" << endl;
			for (int i = 0; i < vertexNum; i++) {
				cin >> Vertexname;
				g->addVertex(Vertexname);
			}
			break;
		}
		else {
			cout << "��������" << endl;
		}
	}
}
void b(Graph * g) {
	if (g->getvertexNum() <= 0) {
		cout << "�������붥��" << endl;
		return;
	}
	char begin, dest;
	int cost;
	while (1) {
		cout << "�����������㼰�ߣ�";
		cin >> begin >> dest >> cost;
		if (begin == '?'&&dest == '?')
			break;
		else
			g->insertEdge(begin, dest, cost);
	}
}
void c(Graph * g,MinSpanTree * minTree) {
	if (g->getedgeNum() < g->getvertexNum() - 1) {
		cout << "����ı���̫�٣����������" << endl;
		return;
	}
	cout << "��������ʼ���㣺";
	char begin;
	cin >> begin;
	prim(g, minTree, begin);
	cout << "����prim��С������!" << endl;
}
void d(MinSpanTree * minTree) {

	cout << *minTree;
}
