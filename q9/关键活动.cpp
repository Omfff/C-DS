#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
const int MaxSize=100;
void print(int *(&temp), int n) {
	for (int i = 0; i < n; i++)
		cout << temp[i] << " ";
	cout << endl << endl;
}
struct Edge {
	int dest;
	int cost;
	Edge * next;
	Edge(int dest, int cost) :dest(dest), cost(cost), next(NULL) {}
};
struct Vertex {
	int name;
	Edge * head;
	Vertex() :name(-1), head(NULL) {}
};
class Graph {
	Vertex * vertexArray;
	int maxNode;
	int edgeNum;
	int vertexNum;
	void linkEdge(int head, Edge * edge);
public:
	Graph(int size = MaxSize) {
		vertexArray = new Vertex[size];
		edgeNum = 0;
		vertexNum = 0;
		maxNode = size;
	}
	~Graph();
	bool addVertex(int name);
	bool insertEdge(int head, int dest, int cost);
	int getFirstNeighbor(int head);
	int getNextNeighbor(int head, int near);
	int getWeight(int head, int dest);
	int getEndPointNum() {
		int num=0;
		for (int i = 0; i < vertexNum; i++) {
			if (vertexArray[i].head == NULL)
				num++;
		}
		return num;
	}
};
void Graph::linkEdge(int head, Edge * edge) {
	if (vertexArray[head].head == NULL) {
		vertexArray[head].head = edge;
		return;
	}
	Edge * temp = vertexArray[head].head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = edge;
}
bool Graph::addVertex(int name) {
	if (vertexNum == maxNode)
		return false;
	else {
		vertexArray[name].name = name;
		vertexNum++;
		return true;
	}
}
bool Graph::insertEdge(int head, int dest, int cost) {
	bool result1 = true, result2 = true;
	if (vertexArray[head].name == -1)result1 = addVertex(head);
	if (vertexArray[dest].name == -1)result2 = addVertex(dest);
	if (result1&&result2) {
		linkEdge(head, new Edge(dest, cost));
		edgeNum++;
		return true;
	}
	else 
		return false;
}
int Graph::getFirstNeighbor(int head) {
	if (vertexArray[head].name == -1)
		return -1;
	else
		if (vertexArray[head].head != NULL)
			return vertexArray[head].head->dest;
		else
			return -1;
}
int Graph::getNextNeighbor(int head, int near) {
	Edge * temp= vertexArray[head].head;
	while (temp->next != NULL && temp->dest != near) 
		temp = temp->next;
	if (temp->next != NULL)
		return temp->next->dest;
	else
		return -1;
}
Graph::~Graph() {

}
int Graph::getWeight(int head, int dest){
	Edge * temp = vertexArray[head].head;
	while (temp->next != NULL && temp->dest != dest)
		temp = temp->next;
	if (temp->dest == dest)
		return temp->cost;
	else
		return -1;
}
int *  AOV(Graph & G, int* (&count),int vertexNum) {
	int top = -1;
	//�����������е�����
	int * aov = new int[vertexNum];
	int pos = 0;
	for (int i = 1; i < vertexNum; i++)
		//��count������Ϊջ���洢���Ϊ0�Ľڵ�
		if (count[i] == 0) {
			//��ջ��ջ��ָ��top����
			count[i] = top;
			top = i;
		}
	for (int j = 1; j < vertexNum; j++) {
		//��ջΪ�գ�������Ԫ��δ�����������У�˵�����ڻ���ֱ�ӷ���null
		if (top == -1) {
			delete[] aov;
			return NULL;
		}
		int vertex = G.getFirstNeighbor(top);
		int head = top;
		//��ջ���ڵ����������������
		aov[pos] = top;
		pos++;
		//����ջ��Ԫ��
		top = count[top];
		//��������vertex�ڽӵĽڵ����ȼ�һ
		while (vertex != -1) {
			count[vertex]--;
			if (count[vertex] == 0) {
				//ѹ��ջ������ջ��ָ��
				count[vertex] = top;
				top = vertex;
			}
			vertex = G.getNextNeighbor(head, vertex);
		}		
	}
	return aov;

}
bool cmp(pair<int, int> a, pair<int, int> b) { return a.first < b.first; }
void AOE(Graph & G,int * (&aov),int vNum) {
	//����ؼ�·��
	vector<pair<int, int>> route;
	//�洢ÿ���������翪ʼʱ��ĸ�������
	int * Ve = new int[vNum+1];
	//�洢ÿ�������������ʼʱ��ĸ�������
	int * Vi = new int[vNum+1];
	for (int i = 0; i < vNum+1; i++) 
		Ve[i] = 0;
	//���������е���㿪ʼ�����¸ýڵ�������ڽӽڵ�����翪ʼʱ��
	for (int j = 0; j < vNum; j++) {
		int head = aov[j];
		int dest = G.getFirstNeighbor(head);
		int w;
		while (dest != -1) {
			w = G.getWeight(head, dest);
			//ʱ����������
			if (Ve[head] + w > Ve[dest])
				Ve[dest] = Ve[head] + w;
			dest = G.getNextNeighbor(head, dest);
		}
	}
	////print(Ve, vNum+1);
	//��ʼ��
	for (int i = 0; i < vNum + 1; i++)
		Vi[i] = 2147483647;
	Vi[vNum] = Ve[vNum];
	//���������еĵ����ڶ����㿪ʼ��
	//����ÿ���ڵ������ڽӽڵ���������ʼʱ��
	for (int i = vNum - 2; i>= 0; i--) {
		int head = aov[i];
		int dest = G.getFirstNeighbor(head);
		int w;
		while (dest != -1) {
			w = G.getWeight(head, dest);
			//�ýڵ�����ʼʱ����٣������
			if (Vi[dest] - w < Vi[head])
				Vi[head] = Vi[dest] - w;
			dest = G.getNextNeighbor(head, dest);
		}
	}
	//print(Vi, vNum + 1);
	cout << Ve[vNum]<<endl;
	int Ae, Ai;
	//�������飬���������������ͬ�Ĺؼ�����������
	//ʹ�������������ʱ�����˳���෴
	vector<int> reverse;
	//���������е���㿪ʼ��
	//�Ƚ�ÿ���ڵ��������ܿ�ʼʱ����������ʼʱ��
	for (int i = 0; i < vNum; i++) {
		int head = aov[i];
		int dest = G.getFirstNeighbor(head);
		while (dest != -1) {
			//������ܿ�ʼʱ��
			Ae = Ve[head];
			//�������ʼʱ��
			Ai = Vi[dest] - G.getWeight(head, dest);
			if (Ae == Ai)
				//�ǹؼ��
				reverse.push_back(dest);
			dest = G.getNextNeighbor(head, dest);
		}
		vector<int>::iterator ite;
		while(reverse.size() > 0) {
			//cout << head << "->" << reverse.back()<< endl;
			//�������ؼ�·��
			route.push_back(make_pair(head, reverse.back()));
			reverse.pop_back();
		}
		reverse.clear();
	}
	//�ȶ�����ʹ������ʼ�Ľ��ӵ���С���������
	stable_sort(route.begin(), route.end(), cmp);
	for (pair<int, int> e : route)
		cout << e.first << "->" << e.second << endl;
}
int main() {
	int N, M;
	cin >> N >> M;
	Graph * G = new Graph(N+1);
	int * aov;
	//������������¼���нڵ�����
	int * count = new int[N+1];
	int head, dest, cost;
	for (int i = 0; i < N+1; i++)
		count[i] = 0;
	for (int i = 0; i < M; i++) {
		cin >> head >> dest >> cost;
		G->insertEdge(head, dest, cost);
		count[dest]++;
	}
	if (G->getEndPointNum() > 1)
	{
		cout << "error:���ڶ���յ�" << endl;
		return 0;
	}

	aov = AOV(*G, count, N+1);
	if (aov != NULL) {
		//print(aov, N);
		AOE(*G, aov, N);
	}
	else
		cout << "0" << endl;
}

