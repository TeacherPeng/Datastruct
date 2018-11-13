#include <iostream>
#include <ctime>
using namespace std;

// 直接插入排序法，预留了L[0]位置，数据从L[1]~L[n]
int InsertSort(int L[], int n)
{
	for (int i = 2; i <= n; i++)
	{
		L[0] = L[i];
		for (int j = i; L[j - 1] > L[j]; j--)
			swap(L[j - 1], L[j]);
	}
	return 0;
}

// 直接交换排序法（冒泡排序）
int SwapSort(int L[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		bool swapped = false;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (L[j] > L[j + 1])
			{
				swap(L[j], L[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
	return 0;
}

// 快速排序的划分过程
int Partition(int L[], int s, int t)
{
	int temp = L[s];
	int low = s, high = t;
	while (low <  high)
	{
		while (low < high && L[high] >= temp) high--;
		L[low] = L[high];
		while (low < high && L[low] <= temp) low++;
		L[high] = L[low];
	}
	L[low] = temp;
	return low;
}
// 快速排序的递归过程
int QSort(int L[], int s, int t)
{
	if (s >= t) return 0;
	int k = Partition(L, s, t);
	QSort(L, s, k - 1);
	QSort(L, k + 1, t);
	return 0;
}
// 快速排序法的主过程
int QuickSort(int L[], int n)
{
	return QSort(L, 0, n - 1);
}

// 对L[s]~L[n-1]进行堆调整
int HeapAdjust(int L[], int n, int s)
{
	int i = s;
	// 从指定起点调整到叶结点（没有左子即为叶结点）
	while (i + i + 1 < n)
	{
		// 确定结点i的最大子结点j
		int j = i + i + 1;						// 先取结点i的左子为j
		if (j + 1 < n && L[j] < L[j + 1]) j++;	// 如果结点i有右子且右子比左子大，则取右子为j
		if (L[j] <= L[i]) break;				// 如果结点i的最大子结点j不比结点i更大，则不需要再调整了。
		swap(L[j], L[i]);						// 如果结点i的最大子结点j比结点i大，则交换结点i和j
		i = j;									// 并将调整点移到结点j
	}
	return 0;
}
// 用指定待排序序列创建一个大顶堆
int CreateHeap(int L[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(L, n, i);
	}
	return 0;
}
// 堆排序
int HeapSort(int L[], int n)
{
	// 先将待排序序列创建成一个大顶堆
	CreateHeap(L, n);
	// 开始排序，待处理的大顶堆的结点数从n递减到1
	for (int i = n; i > 1; i--)
	{
		// 交换堆顶与最后一片叶子
		swap(L[0], L[i - 1]);
		// 调整
		HeapAdjust(L, i - 1, 0);
	}
	return 0;
}

// 将两个有序序列A和B归并到C中
int Merge(int C[], int A[], int nA, int B[], int nB)
{
    int iA = 0, iB = 0, iC = 0;
    while (iA < nA && iB < nB)
    {
        if (A[iA] < B[iB])
        {
            C[iC] = A[iA];
            iA++;
        }
        else
        {
            C[iC] = B[iB];
            iB++;
        }
        iC++;
    }
    while (iA < nA)
    {
        C[iC] = A[iA];
        iA++;
        iC++;
    }
    while (iB < nB)
    {
        C[iC] = B[iB];
        iB++;
        iC++;
    }
    return 0;
}

// 创建取值范围1~n的随机序列，扰动次数为m
int CreateRandSequence(int L[], int n, int m)
{
	for (int i = 0; i < n; i++)
		L[i] = i + 1;
	for (int i = 0; i < m; i++)
		swap(L[rand() % n], L[rand() % n]);
	return 0;
}

// 输出序列
int OutputSequence(const char *title, int L[], int n)
{
	cout << title;
	for (int i = 0; i < n; i++)
		cout << L[i] << ", ";
	cout << endl;
	return 0;
}

int main()
{
	srand((unsigned int)time(NULL));
	int *L0, *L;
	int n = 16, m = 20;
	L0 = new int[n];
	L = new int[n + 1];
	CreateRandSequence(L0, n, m);

	memcpy(L + 1, L0, n * sizeof(int));
	OutputSequence("原始序列：", L + 1, n);
	InsertSort(L, n);
	OutputSequence("直接插入排序结果：", L + 1, n);

	memcpy(L, L0, n * sizeof(int));
	OutputSequence("\n原始序列：", L, n);
	SwapSort(L, n);
	OutputSequence("直接交换排序结果：", L, n);

	memcpy(L, L0, n * sizeof(int));
	OutputSequence("\n原始序列：", L, n);
	QuickSort(L, n);
	OutputSequence("快速排序结果：", L, n);

	memcpy(L, L0, n * sizeof(int));
	OutputSequence("\n原始序列：", L, n);
	HeapSort(L, n);
	OutputSequence("堆排序结果：", L, n);

	delete[]L;
	delete[]L0;
	system("pause");
	return 0;
}