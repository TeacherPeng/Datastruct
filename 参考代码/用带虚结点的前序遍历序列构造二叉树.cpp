#include <iostream>
#include <string>
using namespace std;
int Shuffle(char *nodes, int n)
{
    for (int i = 0; i < 10 * n; i++)
    {
        int x = rand() % n;
        int y = rand() % n;
        swap(nodes[x], nodes[y]);
    }
    return 1;
}
struct BiNode
{
    char data;
    BiNode *lchild, *rchild;
};
typedef BiNode *BiTree;
int DestroyBiTree(BiTree &T)
{
    if (T == NULL)
        return 0;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    delete T;
    return 1;
}
const char *CreateBiTree(BiTree &T, const char *s)
{
    if (s == nullptr || *s == '\0')
        return nullptr;
    if (*s=='#')
    {
        T = nullptr;
        return s + 1;
    }
    T = new BiNode;
    T->data = *s;
    const char *afterLeft = CreateBiTree(T->lchild, s + 1);
    if (afterLeft == nullptr)
        return nullptr;
    const char *afterRight = CreateBiTree(T->rchild, afterLeft);
    return afterRight;
}
int PreBiTree(BiTree T)
{
    if (T == NULL)
        return 1;
    cout << T->data;
    PreBiTree(T->lchild);
    PreBiTree(T->rchild);
    return 1;
}
int InBiTree(BiTree T)
{
    if (T == NULL)
        return 1;
    InBiTree(T->lchild);
    cout << T->data;
    InBiTree(T->rchild);
    return 1;
}
int SucBiTree(BiTree T)
{
    if (T == NULL)
        return 1;
    SucBiTree(T->lchild);
    SucBiTree(T->rchild);
    cout << T->data;
    return 1;
}

int main()
{
    string s;
    cin >> s;
    BiTree T;
    if (CreateBiTree(T, s.c_str()) == nullptr)
    {
        cout << "构造失败，输入串可能有问题！" << endl;
        return 1;
    }
    PreBiTree(T);
    cout << endl;
    InBiTree(T);
    cout << endl;
    SucBiTree(T);
    cout << endl;
    DestroyBiTree(T);
    return 1;
}
