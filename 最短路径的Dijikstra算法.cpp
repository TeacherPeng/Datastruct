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
		G.vexes[i].firstarc = NULL;
	return 0;
}
int DestroyGraph(Graph &G)
{
	for (int i = 0; i < G.vexnumber; i++)
	{
		while (G.vexes[i].firstarc != NULL)
		{
			ArcNode *p = G.vexes[i].firstarc;
			G.vexes[i].firstarc = p->nextarc;
			delete p;
		}
	}
	delete[]G.vexes;
	G.vexes = NULL;
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
	InitGraph(G, 6);
	int arcs[][3] = { { 0, 1, 17 },{ 0, 2, 21 },{ 0, 3, 12 },{ 0, 4, 5 },{ 1, 0, 6 },{ 1, 5, 4 },{ 2, 0, 10 },{ 2, 3, 14 },{ 3, 1, 11 },{ 3, 5, 4 },{ 4, 1, 4 },{ 4, 2, 13 },{ 5, 0, 9 },{ 5, 4, 20 }, };
	for (int i = 0; i < sizeof(arcs) / sizeof(*arcs); i++)
	{
		InsertArc(G, arcs[i][0], arcs[i][1], arcs[i][2]);
	}
	return 0;
}

int Dijkstra(Graph &G, int v0, int Path[])
{
	// 创建并初始化shortest向量、U向量和Path向量
	int *shortest = new int[G.vexnumber];
	int *U = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++)
	{
		shortest[i] = INT_MAX;
		Path[i] = -1;
		U[i] = 0;
	}
	U[v0] = 1;
	for (ArcNode *p = G.vexes[v0].firstarc; p != NULL; p = p->nextarc)
	{
		shortest[p->adj] = p->weight;
		Path[p->adj] = v0;
	}

	// 开始计算
	for (int i = 0; i < G.vexnumber - 1; i++)
	{
		// 找出不在U中的shortest最小的顶点Vk
		int k = -1;
		for (int j = 0; j < G.vexnumber; j++)
			if (!U[j] && (k < 0 || shortest[j] < shortest[k])) k = j;
		if (shortest[k] == INT_MAX) break;

		// 将Vk并入U中
		U[k] = 1;

		// 修正Vk的邻接点的shortest和Path
		for (ArcNode *p = G.vexes[k].firstarc; p != NULL; p = p->nextarc)
		{
			if (!U[p->adj] && shortest[k] + p->weight < shortest[p->adj])
			{
				shortest[p->adj] = shortest[k] + p->weight;
				Path[p->adj] = k;
			}
		}
	}

	delete[]U;
	delete[]shortest;
	return 0;
}

int OutputPath(int Path[], int v0, int aEnd)
{
	if (aEnd == v0)
		cout << v0;
	else
	{
		OutputPath(Path, v0, Path[aEnd]);
		cout << " -> " << aEnd;
	}
	return 0;
}

int main()
{
	Graph G;
	CreateDemoGraph(G);

	int *Path = new int[G.vexnumber];
	Dijkstra(G, 0, Path);

	for (int i = 1; i < G.vexnumber; i++)
	{
		if (Path[i] < 0) continue;
		OutputPath(Path, 0, i);
		cout << endl;
	}

	DestroyGraph(G);
	delete[]Path;
	system("pause");
	return 0;
}
