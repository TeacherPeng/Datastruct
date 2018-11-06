#include <iostream>
using namespace std;

struct CrossNode
{
    int row, col;
    int data;
    CrossNode *rownext, *colnext;
};

struct CrossTable
{
    CrossNode **rowheads, **colheads;
    int mu, nu, tu;
};

int CreateCrossTable(CrossTable &T, int *matrix, int m, int n)
{
    T.mu = m;
    T.nu = n;
    T.rowheads = new CrossNode *[m] {};
    T.colheads = new CrossNode *[n] {};
    CrossNode **rowtails = new CrossNode *[m] {};
    CrossNode **coltails = new CrossNode *[n] {};
    int k = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++, k++)
        {
            // 略过零元
            if (matrix[k] == 0)
                continue;
            // 创建结点
            CrossNode *node = new CrossNode;
            node->row = i;
            node->col = j;
            node->data = matrix[k];
            node->rownext = nullptr;
            node->colnext = nullptr;
            // 将结点追加到行链i中
            if (rowtails[i] == nullptr)
            {
                T.rowheads[i] = rowtails[i] = node;
            }
            else
            {
                rowtails[i]->rownext = node;
                rowtails[i] = node;
            }
            // 将结点追加到列链j中
            if (coltails[j] == nullptr)
            {
                T.colheads[j] = coltails[j] = node;
            }
            else
            {
                coltails[j]->colnext = node;
                coltails[j] = node;
            }
        }
    }
    T.tu = k;
    delete[] rowtails;
    delete[] coltails;
    return 0;
}

int DestroyCrossTable(CrossTable &T)
{
    for (int i = 0; i < T.mu; i++)
    {
        while (T.rowheads[i] != nullptr)
        {
            CrossNode *p = T.rowheads[i];
            T.rowheads[i] = p->rownext;
            delete p;
        }
    }
    for (int i = 0; i < T.nu; i++)
        T.colheads[i] = nullptr;
    return 0;
}

int PrintCrossTable(CrossTable &T)
{
    for (int i = 0; i < T.mu; i++)
    {
        for (CrossNode *p = T.rowheads[i]; p != nullptr; p = p->rownext)
        {
            cout << "(" << p->row << ", " << p->col << ") = " << p->data << endl;
        }
    }
    return 0;
}

int main()
{
    int m, n, *datas;
    cout << "请输入源矩阵的行数和列数：";
    cin >> m >> n;
    datas = new int[m * n];
    for (int i = 0; i < m * n; i++)
        cin >> datas[i];
    
    CrossTable T1;
    cout << "创建十字链表……" << endl;
    CreateCrossTable(T1, datas, m, n);

    cout << "输出十字链表……" << endl;
    PrintCrossTable(T1);

    cout << "撤销十字链表……" << endl;
    DestroyCrossTable(T1);
    delete[] datas;
    return 0;
}
