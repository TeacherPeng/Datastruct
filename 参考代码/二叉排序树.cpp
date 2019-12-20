#include <iostream>
#include <ctime>
using namespace std;

struct BiNode
{
    BiNode(int aKey)
    {
        key = aKey;
        lchild = rchild = nullptr;
    }
    int key;
    BiNode *lchild, *rchild;
};
typedef BiNode *BiTree;

int InitBiTree(BiTree &T)
{
    T = nullptr;
    return 0;
}

int DestroyBiTree(BiTree &T)
{
    if (T == nullptr)
        return 0;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    delete T;
    return 0;
}

BiNode *BSTSearch(BiTree &T, int aKey)
{
    BiNode *p = T;
    while (p != nullptr && p->key != aKey)
    {
        p = aKey < p->key ? p->lchild : p->rchild;
    }
    return p;
}

int Insert(BiTree &T, int aKey)
{
    if (T == nullptr)
    {
        T = new BiNode(aKey);
        return 0;
    }

    BiNode *p = T;
    while (p != nullptr && p->key != aKey)
    {
        if (aKey < p->key)
        {
            if (p->lchild == nullptr)
            {
                p->lchild = new BiNode(aKey);
                return 0;
            }
            else
                p = p->lchild;
        }
        else
        {
            if (p->rchild == nullptr)
            {
                p->rchild = new BiNode(aKey);
                return 0;
            }
            else
                p = p->rchild;
        }
    }
    return 1;
}

int Insert2(BiTree &T, int aKey)
{
    // 定位插入位置
    BiNode **p = &T;
    while (*p != nullptr && (*p)->key != aKey)
    {
        p = aKey < (*p)->key ? &(*p)->lchild : &(*p)->rchild;
    }
    if (*p != nullptr)
        return 1;

    // 插入新结点
    *p = new BiNode(aKey);
    return 0;
}

int Remove(BiTree &T, int aKey)
{
    // 定位被删除结点
    BiNode **p = &T;
    while (*p != nullptr && (*p)->key != aKey)
    {
        p = aKey < (*p)->key ? &(*p)->lchild : &(*p)->rchild;
    }
    if (*p == nullptr)
        return 1;

    // 保存待删除的结点
    BiNode *willRemove = *p;

    if ((*p)->lchild == nullptr)
    {
        // 如果没有左子，直接用右子结点替换被删除结点
        *p = (*p)->rchild;
    }
    else if ((*p)->rchild == nullptr)
    {
        // 如果没有右子，直接用左子结点替换被删除结点
        *p = (*p)->lchild;
    }
    else
    {
        // 找到右子的最左结点
        BiNode **q = &((*p)->rchild);
        while ((*q)->lchild != nullptr)
            q = &(*q)->lchild;

        // 用右子最左结点的右子替换最左结点
        BiNode *temp = *q;
        *q = (*q)->rchild;

        // 用最左结点替换被删除结点
        temp->lchild = (*p)->lchild;
        temp->rchild = (*p)->rchild;
        *p = temp;
    }

    // 释放待删除结点
    delete willRemove;
    return 0;
}

int PreTraverse(BiTree T)
{
    if (T == nullptr)
        return 0;
    cout << T->key << ", ";
    PreTraverse(T->lchild);
    PreTraverse(T->rchild);
    return 0;
}
int InTraverse(BiTree T)
{
    if (T == nullptr)
        return 0;
    InTraverse(T->lchild);
    cout << T->key << ", ";
    InTraverse(T->rchild);
    return 0;
}
int SucTraverse(BiTree T)
{
    if (T == nullptr)
        return 0;
    SucTraverse(T->lchild);
    SucTraverse(T->rchild);
    cout << T->key << ", ";
    return 0;
}

int CreateRands(int datas[], int n, int m)
{
    for (int i = 0; i < n; i++)
        datas[i] = i + 1;
    srand((unsigned int)time(nullptr));
    for (int i = 0; i < m; i++)
        swap(datas[rand() % n], datas[rand() % n]);
    return 0;
}

int Print(BiTree T)
{
    cout << "排序二叉树的前序遍历序：";
    PreTraverse(T);
    cout << endl;

    cout << "排序二叉树的中序遍历序：";
    InTraverse(T);
    cout << endl;

    cout << "排序二叉树的后序遍历序：";
    SucTraverse(T);
    cout << endl;

    return 0;
}

int main()
{
    constexpr int n = 16, m = 20;
    int datas[n];
    CreateRands(datas, n, m);
    cout << "输入序列：";
    for (int i = 0; i < n; i++)
    {
        cout << datas[i] << ", ";
    }
    cout << endl;

    cout << "构造排序二叉树……" << endl;
    BiTree T;
    InitBiTree(T);
    for (int i = 0; i < n; i++)
    {
        Insert(T, datas[i]);
    }
    Print(T);

    cout << "删除8：" << endl;
    Remove(T, 8);
    Print(T);

    cout << "插入8：" << endl;
    Insert2(T, 8);
    Print(T);

    DestroyBiTree(T);
    system("pause");
    return 0;
}