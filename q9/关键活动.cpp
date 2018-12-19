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
	//保存拓扑序列的数组
	int * aov = new int[vertexNum];
	int pos = 0;
	for (int i = 1; i < vertexNum; i++)
		//用count数组作为栈来存储入度为0的节点
		if (count[i] == 0) {
			//进栈，栈顶指针top更新
			count[i] = top;
			top = i;
		}
	for (int j = 1; j < vertexNum; j++) {
		//当栈为空，但还有元素未进入拓扑序列，说明存在环，直接返回null
		if (top == -1) {
			delete[] aov;
			return NULL;
		}
		int vertex = G.getFirstNeighbor(top);
		int head = top;
		//将栈顶节点放入拓扑序列数组
		aov[pos] = top;
		pos++;
		//弹出栈顶元素
		top = count[top];
		//将所有与vertex邻接的节点的入度减一
		while (vertex != -1) {
			count[vertex]--;
			if (count[vertex] == 0) {
				//压入栈，更新栈顶指针
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
	//保存关键路径
	vector<pair<int, int>> route;
	//存储每个任务最早开始时间的辅助数组
	int * Ve = new int[vNum+1];
	//存储每个任务最迟允许开始时间的辅助数组
	int * Vi = new int[vNum+1];
	for (int i = 0; i < vNum+1; i++) 
		Ve[i] = 0;
	//从拓扑序列的起点开始，更新该节点的所有邻接节点的最早开始时间
	for (int j = 0; j < vNum; j++) {
		int head = aov[j];
		int dest = G.getFirstNeighbor(head);
		int w;
		while (dest != -1) {
			w = G.getWeight(head, dest);
			//时间更长则更新
			if (Ve[head] + w > Ve[dest])
				Ve[dest] = Ve[head] + w;
			dest = G.getNextNeighbor(head, dest);
		}
	}
	////print(Ve, vNum+1);
	//初始化
	for (int i = 0; i < vNum + 1; i++)
		Vi[i] = 2147483647;
	Vi[vNum] = Ve[vNum];
	//从拓扑序列的倒数第二个点开始，
	//更新每个节点所有邻接节点的最迟允许开始时间
	for (int i = vNum - 2; i>= 0; i--) {
		int head = aov[i];
		int dest = G.getFirstNeighbor(head);
		int w;
		while (dest != -1) {
			w = G.getWeight(head, dest);
			//该节点允许开始时间更迟，则更新
			if (Vi[dest] - w < Vi[head])
				Vi[head] = Vi[dest] - w;
			dest = G.getNextNeighbor(head, dest);
		}
	}
	//print(Vi, vNum + 1);
	cout << Ve[vNum]<<endl;
	int Ae, Ai;
	//辅助数组，用来调换起点编号相同的关键活动的输出次序，
	//使得其次序与输入时任务的顺序相反
	vector<int> reverse;
	//从拓扑序列的起点开始，
	//比较每个节点的最早可能开始时间和最迟允许开始时间
	for (int i = 0; i < vNum; i++) {
		int head = aov[i];
		int dest = G.getFirstNeighbor(head);
		while (dest != -1) {
			//最早可能开始时间
			Ae = Ve[head];
			//最迟允许开始时间
			Ai = Vi[dest] - G.getWeight(head, dest);
			if (Ae == Ai)
				//是关键活动
				reverse.push_back(dest);
			dest = G.getNextNeighbor(head, dest);
		}
		vector<int>::iterator ite;
		while(reverse.size() > 0) {
			//cout << head << "->" << reverse.back()<< endl;
			//反向放入关键路径
			route.push_back(make_pair(head, reverse.back()));
			reverse.pop_back();
		}
		reverse.clear();
	}
	//稳定排序，使得任务开始的交接点编号小者优先输出
	stable_sort(route.begin(), route.end(), cmp);
	for (pair<int, int> e : route)
		cout << e.first << "->" << e.second << endl;
}
int main() {
	int N, M;
	cin >> N >> M;
	Graph * G = new Graph(N+1);
	int * aov;
	//该数组用来记录所有节点的入度
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
		cout << "error:存在多个终点" << endl;
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

