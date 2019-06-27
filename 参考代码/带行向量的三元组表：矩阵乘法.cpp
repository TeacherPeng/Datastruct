#include <iostream>
using namespace std;

struct TriNode
{
    int row, col;
    int data;
};
struct TriTable
{
    TriNode *datas; // 三元组表，按行优先顺序存储矩阵中的非零元。
    int *rpos;       // 行向量，row[i]表示i行在datas中的起始下标。
    int mu, nu, tu; // 行数，列数，非零元个数。
};

int CreateTriTable(TriTable &T, int matrix[], int n1, int n2)
{
    T.mu = n1;
    T.nu = n2;

    // 统计非零元的个数，分配存储空间
    int count = 0;
    for (int i = 0; i < n1 * n2; i++)
        if (matrix[i] != 0)
            count++;
    T.tu = count;
    T.datas = new TriNode[count];
    T.rpos = new int[n1 + 1];

    // 填写三元组表
    int k = 0, t = 0;
    for (int i = 0; i < n1; i++)
    {
        T.rpos[i] = t;
        for (int j = 0; j < n2; j++)
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
    }
    T.rpos[n1] = t;
    return 0;
}

int DestroyTriTable(TriTable &T)
{
    delete[] T.datas;
    delete[] T.rpos;
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

// C = A * B
int MatrixMulti(TriTable &C, TriTable &A, TriTable &B)
{
    // 分配未压缩结果矩阵存储区，并初始化为全0
    int *buffer = new int[A.mu * B.nu]{};

    // 逐行计算Ci，Ci = Ai * B
    int *cp = buffer; // cp此时指向buffer中的第0行
    for (int i = 0; i < A.mu; i++)
    {
        // 取A的第i行中的非零元
        for (int j = A.rpos[i]; j < A.rpos[i + 1]; j++)
        {
            // A[i]中的非零元与B的对应行中的非零元对乘，结果累加到C的第i行中
            int r = A.datas[j].col;
            for (int k = B.rpos[r]; k < B.rpos[r + 1]; k++)
            {
                cp[B.datas[k].col] += A.datas[j].data * B.datas[k].data;
            }
        }
        // cp指向下一行（C的列数与B的列数相同）
        cp += B.nu;
    }

    // 将计算结果填写到结果表C中
    CreateTriTable(C, buffer, A.mu, B.nu);
    delete[] buffer;
    return 0;
}

int main()
{
    int *matrix, n1, n2, n3;
    cout << "请输入矩阵A的行数 列数：";
    cin >> n1 >> n2;
    matrix = new int[n1 * n2];
    cout << "请按行优先顺序输入矩阵A：";
    for (int i = 0; i < n1 * n2; i++)
    {
        cin >> matrix[i];
    }

    TriTable T1;
    CreateTriTable(T1, matrix, n1, n2);
    delete[] matrix;

    cout << "矩阵A：" << endl;
    PrintTriTable(T1);

    cout << "请输入矩阵B的列数：";
    cin >> n3;
    matrix = new int[n2 * n3];
    cout << "请按行优先顺序输入矩阵A：";
    for (int i = 0; i < n2 * n3; i++)
    {
        cin >> matrix[i];
    }

    TriTable T2;
    CreateTriTable(T2, matrix, n2, n3);
    delete[] matrix;

    cout << "矩阵B：" << endl;
    PrintTriTable(T1);

    TriTable T3;
    MatrixMulti(T3, T1, T2);
    cout << "C = A * B：" << endl;
    PrintTriTable(T3);

    DestroyTriTable(T1);
    DestroyTriTable(T2);
    DestroyTriTable(T3);
    system("pause");
    return 0;
}