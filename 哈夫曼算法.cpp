#include <iostream>
#include <algorithm>
using namespace std;

struct HuffmanNode
{
	int weight;
	int parent, lchild, rchild;
};
// 定义结点的排序规则，sort算法需要使用这个重载的运算符
bool operator<(const HuffmanNode &node1, const HuffmanNode &node2)
{
	return node1.weight < node2.weight;
}

struct HuffmanTree
{
	HuffmanNode *nodes;
	int leafnumber;
};

int CreateHuffmanTree(HuffmanTree &T, int leafnumber, int *weights)
{
	// 分配哈夫曼树存储空间
	T.nodes = new HuffmanNode[leafnumber + leafnumber - 1];
	T.leafnumber = leafnumber;

	// 初始化叶结点
	for (int i = 0; i < leafnumber; i++)
	{
		T.nodes[i].weight = weights[i];
		T.nodes[i].parent = T.nodes[i].lchild = T.nodes[i].rchild = -1;
	}
	
	// 将叶结点按权值排序
	sort(T.nodes, T.nodes + leafnumber);
	
	// 开始构造哈夫曼树
	int s = 0, t = leafnumber; // 分别用来遍历叶结点和非叶结点
	for (int i = 0; i < leafnumber - 1; i++)
	{
		// 选择第一个权值最小的根结点
		int k1;
		if (s < leafnumber && (t >= leafnumber + i || T.nodes[s].weight < T.nodes[t].weight))
			k1 = s++;
		else
			k1 = t++;
		
		// 选择第二个权值最小的根结点
		int k2;
		if (s < leafnumber && (t >= leafnumber + i || T.nodes[s].weight < T.nodes[t].weight))
			k2 = s++;
		else
			k2 = t++;

		// 将根结点k1, 根结点k2合并到新增根结点i + leafnumber下
		T.nodes[i + leafnumber].weight = T.nodes[k1].weight + T.nodes[k2].weight;
		T.nodes[i + leafnumber].parent = -1;
		T.nodes[i + leafnumber].lchild = k1;
		T.nodes[i + leafnumber].rchild = k2;
		T.nodes[k1].parent = i + leafnumber;
		T.nodes[k2].parent = i + leafnumber;
	}

	return 0;
}

int DestroyHuffmanTree(HuffmanTree &T)
{
    delete[] T.nodes;
    T.nodes = nullptr;
    T.leafnumber = 0;
    return 0;
}

int main()
{
	HuffmanTree T;
	int weights[] = { 3, 7, 8, 6, 21 };
	CreateHuffmanTree(T, 5, weights);

	for (int i = 0; i < T.leafnumber + T.leafnumber - 1; i++)
	{
		cout << i << ":" << T.nodes[i].weight << ", " << T.nodes[i].parent << ", " << T.nodes[i].lchild << ", " << T.nodes[i].rchild << endl;
	}

    DestroyHuffmanTree(T);
    system("pause");
	return 0;
}