#include <iostream>
#include <queue>
using namespace std;

struct BiNode
{
    char data;
    BiNode *lchild, *rchild;
};
typedef BiNode *BiTree;

BiTree CreateBiTree(const char *prestr, const char *midstr, int n)
{
    if (n <= 0)
        return nullptr;
    // 创建根结点
    BiTree T = new BiNode;
    T->data = *prestr;

    // 在中序遍历序列中确定根结点的位置
    int rootpos = -1;
    for (int i = 0; i < n; i++)
    {
        if (midstr[i] == *prestr)
        {
            rootpos = i;
            break;
        }
    }

    if (rootpos == -1)
        return nullptr;
    // 分别创建左子树和右子树
    T->lchild = CreateBiTree(prestr + 1, midstr, rootpos);
    T->rchild = CreateBiTree(prestr + 1 + rootpos, midstr + 1 + rootpos, n - rootpos - 1);
    return T;
}

int SucTraverse(BiTree T)
{
    if (T == nullptr)
        return 1;
    SucTraverse(T->lchild);
    SucTraverse(T->rchild);
    cout << T->data;
    return 1;
}

int LevelTraverse(BiTree T)
{
    if (T == nullptr)
        return 1;
    queue<BiNode *> Q;
    Q.push(T);
    while (!Q.empty())
    {
        T = Q.front();
        Q.pop();
        cout << T->data;
        if (T->lchild != nullptr)
            Q.push(T->lchild);
        if (T->rchild != nullptr)
            Q.push(T->rchild);
    }
    return 1;
}
int DestroyBiTree(BiTree &T)
{
    if (T == nullptr)
        return 1;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    delete T;
    T = nullptr;
    return 1;
}

int main()
{
    char prestr[1024], midstr[1024];
    cin >> prestr >> midstr;
    BiTree T = CreateBiTree(prestr, midstr, strlen(prestr));
    SucTraverse(T);
    cout << " ";
    LevelTraverse(T);
    cout << endl;
    DestroyBiTree(T);
    system("PAUSE");
    return 1;
}
