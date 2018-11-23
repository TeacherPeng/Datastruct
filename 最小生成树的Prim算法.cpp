#include <iostream>
#include <string>
#include <climits>
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
	return 0;
}
int CreateDemoGraph(Graph &G)
{
	// 初始化图存储结构
	InitGraph(G, 7);
	
	// 初始化顶点信息
	string infos[] = { "高家庄", "马家河子", "夹皮沟", "曹家堡", "高良村", "过山屯", "集贤村" };
	for (int i = 0; i < G.vexnumber; i++)
		G.vexes[i].info = infos[i];
	
	// 初始化弧信息
	int arcs[][3] = { { 0, 1, 10 },{ 0, 2, 9 },{ 0, 3, 13 },{ 1, 3, 15 },{ 1, 4, 7 },{ 1, 6, 12 },{ 2, 3, 4 },{ 2, 5, 3 },{ 3, 5, 22 },{ 3, 6, 23 },{ 4, 6, 20 },{ 5, 6, 32 }, };
	for (int i = 0; i < sizeof(arcs) / sizeof(*arcs); i++)
	{
		// 无向图的边由两条对称的弧组成 
		InsertArc(G, arcs[i][0], arcs[i][1], arcs[i][2]);
		InsertArc(G, arcs[i][1], arcs[i][0], arcs[i][2]);
	}
	return 0;
}

int Prim(Graph &G, int(*T)[2])
{
	// 初始化U向量，U[i]表示Vi是否在U集中，1表示在，0表示不在
	int *U = new int[G.vexnumber];
	U[0] = 1;
	for (int i = 1; i < G.vexnumber; i++) U[i] = 0;

	// 初始化cost向量，cost[i]表示Vi到U集的最短边的权值
	// 初始时，U中只有V0，因此cost[i]即边<V0, Vi>的权值
	int *cost = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) cost[i] = INT_MAX;
	for (ArcNode *p = G.vexes[0].firstarc; p != NULL; p = p->nextarc)
		cost[p->adj] = p->weight;

	// 初始化adj向量，adj[i]表示Vi到U集的最短边在U中的邻接点的序号
	// 初始时，U中只有V0，因此adj[i]为0
	int *adj = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++)
		adj[i] = 0;

	// 按照MST性质挑选n-1条边
	for (int i = 0; i < G.vexnumber - 1; i++)
	{
		// 检索V-U中cost最小的顶点k 
		int k = -1;
		for (int j = 0; j < G.vexnumber; j++)
		{
			if (!U[j] && (k == -1 || cost[j] < cost[k]))
				k = j;
		}

		// 将顶点k并入U集
		U[k] = 1;
		// 收集一条边<Vk, Vadj[k]>
		T[i][0] = k;
		T[i][1] = adj[k];

		// 修正V-U中剩余顶点的cost和adj（只有顶点k的邻接点需要被修正） 
		for (ArcNode *p = G.vexes[k].firstarc; p != NULL; p = p->nextarc)
		{
			// 对顶点Vj，检查新出现的跨U和V-U的边<Vk, Vj>是否比原来的跨U和V-U的最短边更短
			int j = p->adj;
			if (!U[j] && p->weight < cost[j])
			{
				cost[j] = p->weight;
				adj[j] = k;
			}
		}
	}

	delete[]adj;
	delete[]cost;
	delete[]U;
	return 0;
}

int main()
{
	Graph G;
	CreateDemoGraph(G);

	int(*T)[2] = new int[G.vexnumber - 1][2];
	Prim(G, T);
	for (int i = 0; i < G.vexnumber - 1; i++)
		cout << G.vexes[T[i][0]].info << " -- " << G.vexes[T[i][1]].info << endl;

	DestroyGraph(G);
	delete[]T;
	return 0;
}
