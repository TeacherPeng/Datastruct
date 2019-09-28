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
	int vexnumber, arcnumber;
};

int InitGraph(Graph &G, int vexnumber)
{
	G.vexes = new VexNode[vexnumber];
	G.vexnumber = vexnumber;
	G.arcnumber = 0;
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
	G.arcnumber++;
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

int CriticalPath(Graph &G, int(*aCriticalArcs)[2])
{
	// 统计各顶点入度
	int *indegree = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) indegree[i] = 0;
	for (int i = 0; i < G.vexnumber; i++)
		for (ArcNode *p = G.vexes[i].firstarc; p != nullptr; p = p->nextarc)
			indegree[p->adj]++;

	// 入度为0的顶点入栈
	stack<int> s;
	for (int i = 0; i < G.vexnumber; i++)
		if (indegree[i] == 0) s.push(i);

	// 拓扑排序，并按拓扑序计算顶点的ve
	int *ve = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) ve[i] = 0;
	stack<int> s2; // 用来记录拓扑序
	while (!s.empty())
	{
		// 取出一个可排序顶点，并记录到s2栈中（用于生成逆拓扑序）
		int i = s.top(); s.pop();
		s2.push(i);
		// 遍历Vi的所有邻接点
		for (ArcNode *p = G.vexes[i].firstarc; p != nullptr; p = p->nextarc)
		{
			// 将Vi的邻接点Vj入度减1，减到0则Vj入栈等待拓扑排序
			int j = p->adj;
			indegree[j]--;
			if (indegree[j] == 0) s.push(p->adj);

			// 修正Vj的ve值
			if (ve[i] + p->weight > ve[j])
				ve[j] = ve[i] + p->weight;
		}
	}

	// 按逆拓扑序计算顶点的vl，终点的ve值作为vl的初值
	int *vl = new int[G.vexnumber];
	int maxve = ve[s2.top()];
	for (int i = 0; i < G.vexnumber; i++) vl[i] = maxve;
	while (!s2.empty())
	{
		int i = s2.top(); s2.pop();
		// 用Vi的邻接点来修正Vi的vl值
		for (ArcNode *p = G.vexes[i].firstarc; p != nullptr; p = p->nextarc)
		{
			int j = p->adj;
			if (vl[j] - p->weight < vl[i])
				vl[i] = vl[j] - p->weight;
		}
	}

	// 遍历所有的弧，计算弧的e和l值，挑选关键弧（e和l相等的弧）
	int count = 0;
	for (int i = 0; i < G.vexnumber; i++)
	{
		for (ArcNode *p = G.vexes[i].firstarc; p != nullptr; p = p->nextarc)
		{
			int e = ve[i];
			int l = vl[p->adj] - p->weight;
			if (e == l)
			{
				aCriticalArcs[count][0] = i;
				aCriticalArcs[count][1] = p->adj;
				count++;
			}
		}
	}

	delete[]indegree;
	delete[]ve;
	delete[]vl;
	return count;
}

int main()
{
	Graph G;
	CreateDemoGraph(G);

	int(*Path)[2] = new int[G.arcnumber][2];
	int n = CriticalPath(G, Path);
	for (int i = 0; i < n; i++)
	{
		cout << Path[i][0] << " -> " << Path[i][1] << endl;
	}
	cout << endl;

	DestroyGraph(G);
	delete[]Path;
	system("pause");
	return 0;
}
