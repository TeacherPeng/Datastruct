#include <iostream>
using namespace std;

// 对L[s]~L[n-1]进行堆调整
int HeapAdjust(int L[], int n, int s)
{
    int i = s;
    // 从指定起点调整到叶结点（没有左子即为叶结点）
    while (i + i + 1 < n)
    {
        // 确定结点i的最大子结点j
        int j = i + i + 1; // 先取结点i的左子为j
        if (j + 1 < n && L[j] < L[j + 1])
            j++; // 如果结点i有右子且右子比左子大，则取右子为j
        if (L[j] <= L[i])
            break;        // 如果结点i的最大子结点j不比结点i更大，则不需要再调整了。
        swap(L[j], L[i]); // 如果结点i的最大子结点j比结点i大，则交换结点i和j
        i = j;            // 并将调整点移到结点j
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

int main()
{
    int n;
    while (cin >> n)
    {
        int *datas = new int[n];
        for (int i = 0; i < n; i++)
            cin >> datas[i];
        CreateHeap(datas, n);
        for (int i = 0; i < n; i++)
            cout << datas[i] << ' ';
        cout << endl;
        delete[] datas;
    }
    return 0;
}