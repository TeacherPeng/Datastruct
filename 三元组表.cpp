#include <iostream>
using namespace std;

struct TriNode
{
	int row, col;
	int data;
};
struct TriTable
{
	TriNode *datas;
	int mu, nu, tu;  // 行数，列数，非零元个数
};

int CreateTriTable(TriTable &T, int matrix[], int m, int n)
{
	T.mu = m;
	T.nu = n;

	// 统计非零元的个数，分配存储空间
	int count = 0;
	for (int i = 0; i < m*n; i++)
		if (matrix[i] != 0) count++;
	T.tu = count;
	T.datas = new TriNode[count];

	// 填写三元组表
	int k = 0, t = 0;
	for (int i = 0; i<m; i++)
		for (int j = 0; j < n; j++)
		{
			if (matrix[k] != 0)
			{
				T.datas[t].row = i;
				T.datas[t].col = j;
				T.datas[t].data = matrix[k];
				t++;
			}
			k++;
		}
	return 0;
}

int DestroyTriTable(TriTable &T)
{
	delete[]T.datas;
	T.mu = T.nu = T.tu = 0;
	return 0;
}

int PrintTriTable(TriTable &T)
{
	cout << "mu = " << T.mu << ", nu = " << T.nu << ", tu = " << T.tu << endl;
	for (int i = 0; i < T.tu; i++)
	{
		cout << "(" << T.datas[i].row << ", " << T.datas[i].col << ") = " << T.datas[i].data << endl;
	}
	return 0;
}

// 将三元组表结构的矩阵A转置到B
int FastTranspose(TriTable &B, TriTable &A)
{
	// 初始化结果三元组表
	B.mu = A.nu;
	B.nu = A.mu;
	B.tu = A.tu;
	B.datas = new TriNode[B.tu];

	// 统计结果矩阵每行非零元个数
	int *rsum = new int[B.mu];
	for (int i = 0; i < B.mu; i++) rsum[i] = 0;
	for (int i = 0; i < A.tu; i++)
		rsum[A.datas[i].col]++;

	// 计算结果矩阵各行在三元组表中的起始下标
	int *rpos = new int[B.mu];
	rpos[0] = 0;
	for (int i = 1; i < B.mu; i++)
		rpos[i] = rpos[i - 1] + rsum[i - 1];

	// 将源三元组表转置到目标三元组表中
	for (int i = 0; i < A.tu; i++)
	{
		int j = rpos[A.datas[i].col];
		B.datas[j].row = A.datas[i].col;
		B.datas[j].col = A.datas[i].row;
		B.datas[j].data = A.datas[i].data;
		rpos[A.datas[i].col]++;
	}

	delete[]rpos;
	delete[]rsum;
	return 0;
}

int main()
{
	int *matrix, m, n;
	cout << "请输入行数 列数：";
	cin >> m >> n;
	matrix = new int[m*n];
	cout << "请按行优先顺序输入矩阵：";
	for (int i = 0; i < m*n; i++)
	{
		cin >> matrix[i];
	}

	TriTable T1;
	CreateTriTable(T1, matrix, m, n);
	cout << "源矩阵：" << endl;
	PrintTriTable(T1);

	TriTable T2;
	FastTranspose(T2, T1);
	cout << "转置后矩阵：" << endl;
	PrintTriTable(T2);

	DestroyTriTable(T1);
	DestroyTriTable(T2);
	system("pause");
	return 0;
}