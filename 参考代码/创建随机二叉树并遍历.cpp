#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
using namespace std;
int Shuffle(char *nodes, int n)
{
    for (int i = 0; i < 10 * n; i++)
    {
        int x = rand() % n;
        int y = rand() % n;
        swap(nodes[x], nodes[y]);
    }
    return 0;
}
struct BiNode
{
    char data;
    BiNode *lchild, *rchild;
};
using BiTree = BiNode *;
int DestroyBiTree(BiTree &T)
{
    if (T == nullptr)
        return 0;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    delete T;
    return 0;
}
BiTree CreateBiTree(const char *nodes)
{
    BiTree T = nullptr;
    for (const char *p = nodes; *p != '\0'; p++)
    {
        BiTree *tp = &T;
        while (*tp != nullptr)
        {
            if ((rand() % 2) == 0)
                tp = &((*tp)->lchild);
            else
                tp = &((*tp)->rchild);
        }
        *tp = new BiNode;
        (*tp)->data = *p;
        (*tp)->lchild = (*tp)->rchild = nullptr;
    }
    return T;
}
int VPreTraverse(BiTree T)
{
    if (T == nullptr)
    {
        cout << "#";
        return 1;
    }
    cout << T->data;
    VPreTraverse(T->lchild);
    VPreTraverse(T->rchild);
    return 0;
}
int PreTraverse(BiTree T)
{
    if (T == nullptr)
        return 0;
    cout << T->data;
    PreTraverse(T->lchild);
    PreTraverse(T->rchild);
    return 0;
}
int PreTraverse_Norecursion(BiTree T)
{
    if (T == nullptr)
        return 0;
    stack<BiNode *> s;
    s.push(T);
    while (!s.empty())
    {
        BiNode *p = s.top();
        s.pop();
        cout << p->data;
        if (p->rchild != nullptr)
            s.push(p->rchild);
        if (p->lchild != nullptr)
            s.push(p->lchild);
    }
    return 0;
}
int InTraverse(BiTree T)
{
    if (T == nullptr)
        return 0;
    InTraverse(T->lchild);
    cout << T->data;
    InTraverse(T->rchild);
    return 0;
}
int InTraverse_Norecursion(BiTree T)
{
    stack<BiNode *> s;
    BiNode *p = T;
    while (p != nullptr || !s.empty())
    {
        if (p != nullptr)
        {
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            cout << p->data;
            p = p->rchild;
        }
    }
    return 0;
}
int SucTraverse(BiTree T)
{
    if (T == nullptr)
        return 0;
    SucTraverse(T->lchild);
    SucTraverse(T->rchild);
    cout << T->data;
    return 0;
}
int SucTraverse_Norecursion(BiTree T)
{
    if (T == nullptr)
        return 0;
    stack<pair<BiNode *, bool>> s;
    s.push(make_pair(T, false));
    while (!s.empty())
    {
        auto p = s.top();
        s.pop();
        if (p.second)
        {
            cout << p.first->data;
        }
        else
        {
            s.push(make_pair(p.first, true));
            if (p.first->rchild != nullptr)
                s.push(make_pair(p.first->rchild, false));
            if (p.first->lchild != nullptr)
                s.push(make_pair(p.first->lchild, false));
        }
    }
    return 0;
}

int main(int argc, char *args[])
{
    srand((unsigned int)time(nullptr));
    char defaultstr[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    int n = (rand() % strlen(defaultstr)) + 1;
    char *s = defaultstr;
    s[n] = '\0';
    if (argc == 2)
    {
        s = args[1];
        n = strlen(s);
    }
    Shuffle(s, n);
    BiTree T = CreateBiTree(s);
    VPreTraverse(T);
    cout << endl;
    PreTraverse(T);
    cout << endl;
    PreTraverse_Norecursion(T);
    cout << endl;
    InTraverse(T);
    cout << endl;
    InTraverse_Norecursion(T);
    cout << endl;
    SucTraverse(T);
    cout << endl;
    SucTraverse_Norecursion(T);
    cout << endl;
    DestroyBiTree(T);
    return 0;
}
