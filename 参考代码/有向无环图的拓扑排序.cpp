#include <iostream>
#include <string>
#include <climits>
#include <stack>
using namespace std;

// 弧结点定义
struct ArcNode
{
	int weight;		// 弧上的信息部分
	int adj;		// 邻接点的序号
	ArcNode *nextarc;
};

// 顶点结点定义 
struct VexNode
{
	string info;		// 顶点上的信息部分
	ArcNode *firstarc;	// 弧链头指针
};

// 邻接表结构的图的定义
struct Graph
{
	VexNode *vexes;
	int vexnumber;
};

int InitGraph(Graph &G, int vexnumber)
{
	G.vexes = new VexNode[vexnumber];
	G.vexnumber = vexnumber;
	for (int i = 0; i < vexnumber; i++)
		G.vexes[i].firstarc = nullptr;
	return 0;
}
int DestroyGraph(Graph &G)
{
	for (int i = 0; i < G.vexnumber; i++)
	{
		while (G.vexes[i].firstarc != nullptr)
		{
			ArcNode *p = G.vexes[i].firstarc;
			G.vexes[i].firstarc = p->nextarc;
			delete p;
		}
	}
	delete[]G.vexes;
	G.vexes = nullptr;
	G.vexnumber = 0;
	return 0;
}
int InsertArc(Graph &G, int i, int j, int weight)
{
	ArcNode *aArcNode = new ArcNode;
	aArcNode->weight = weight;
	aArcNode->adj = j;
	aArcNode->nextarc = G.vexes[i].firstarc;
	G.vexes[i].firstarc = aArcNode;
	return 0;
}
int CreateDemoGraph(Graph &G)
{
	InitGraph(G, 12);
	int arcs[][3] = { { 0, 1, 5 },{ 0, 2, 3 },{ 1, 3, 10 },{ 1, 6, 12 },{ 2, 3, 4 },{ 2, 4, 18 },{ 3, 5, 9 },{ 3, 6, 3 },{ 4, 10, 20 },{ 5, 7, 17 },{ 6, 8, 10 },{ 7, 9, 9 },{ 7, 11, 19 },{ 8, 9, 21 },{ 8, 10, 5 },{ 9, 11, 12 },{ 10, 11, 15 }, };
	for (int i = 0; i < sizeof(arcs) / sizeof(*arcs); i++)
	{
		InsertArc(G, arcs[i][0], arcs[i][1], arcs[i][2]);
	}
	return 0;
}

// 拓扑排序，排序成功返回0，排序失败返回1
int Topology(Graph &G, int Topo[])
{
	// 统计各顶点的入度
	int *indegree = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) indegree[i] = 0;
	for (int i = 0; i < G.vexnumber; i++)
		for (ArcNode *p = G.vexes[i].firstarc; p != nullptr; p = p->nextarc)
			indegree[p->adj]++;

	// 入度为0的顶点入栈或队
	stack<int> s;
	for (int i = 0; i < G.vexnumber; i++)
		if (indegree[i] == 0) s.push(i);

	// 生成拓扑序列
	int i = 0;
	while (!s.empty())
	{
		// 取出一个可排入拓扑序列的顶点Vj，排入拓扑序列中
		int j = s.top(); s.pop();
		Topo[i++] = j;

		// 将Vj的邻接点的入度减1，减为0的邻接点入栈
		for (ArcNode *p = G.vexes[j].firstarc; p != nullptr; p = p->nextarc)
		{
			indegree[p->adj]--;
			if (indegree[p->adj] == 0) s.push(p->adj);
		}
	}

	delete[]indegree;

	return i == G.vexnumber ? 0 : 1;
}

int main()
{
	Graph G;
	CreateDemoGraph(G);

	int *Topo = new int[G.vexnumber];
	if (Topology(G, Topo) != 0)
		cout << "发现回路，不是有向无环图！" << endl;
	else
	{
		cout << Topo[0];
		for (int i = 1; i < G.vexnumber; i++)
			cout << " -> " << Topo[i];
		cout << endl;
	}

	DestroyGraph(G);
	delete[]Topo;
	return 0;
}
