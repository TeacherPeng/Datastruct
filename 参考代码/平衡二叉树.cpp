#include <iostream>
#include <stack>
using namespace std;

// 平衡二叉树结构定义
struct AVLNode
{
    AVLNode(int aKey)
    {
        key = aKey;
        balance = 0;
        lchild = rchild = nullptr;
    }
    ~AVLNode();
    int key;
    int balance;
    AVLNode *lchild, *rchild;
};
using AVLTree = AVLNode *; // typedef AVLNode *AVLTree;

AVLNode::~AVLNode()
{
    delete lchild;
    lchild = nullptr;
    delete rchild;
    rchild = nullptr;
}

int LRotate(AVLNode *&p)
{
    AVLNode *temp = p;
    p = p->rchild;
    temp->rchild = p->lchild;
    p->lchild = temp;
    return 0;
}

int RRotate(AVLNode *&p)
{
    AVLNode *temp = p;
    p = p->lchild;
    temp->lchild = p->rchild;
    p->rchild = temp;
    return 0;
}

int LLAdjust(AVLNode *&p)
{
    RRotate(p);
    p->balance = 0;
    p->rchild->balance = 0;
    return 0;
}

int LRAdjust(AVLNode *&p)
{
    LRotate(p->lchild);
    RRotate(p);
    switch (p->balance)
    {
    case 1:
        p->lchild->balance = 0;
        p->rchild->balance = -1;
        break;
    case -1:
        p->lchild->balance = 1;
        p->rchild->balance = 0;
        break;
    }
    p->balance = 0;
    return 0;
}

int RLAdjust(AVLNode *&p)
{
    RRotate(p->rchild);
    LRotate(p);
    switch (p->balance)
    {
    case -1:
        p->lchild->balance = 1;
        p->rchild->balance = 0;
        break;
    case 1:
        p->lchild->balance = 0;
        p->rchild->balance = -1;
        break;
    }
    p->balance = 0;
    return 0;
}

int RRAdjust(AVLNode *&p)
{
    LRotate(p);
    p->balance = 0;
    p->lchild->balance = 0;
    return 0;
}

int Insert(AVLTree &T, int aKey)
{
    AVLNode **p = &T;
    stack<pair<AVLNode **, int>> ancestors;
    while (*p != nullptr)
    {
        if (aKey < (*p)->key)
        {
            ancestors.push(make_pair(p, 1));
            p = &(*p)->lchild;
        }
        else if (aKey > (*p)->key)
        {
            ancestors.push(make_pair(p, -1));
            p = &(*p)->rchild;
        }
        else
        {
            return 1;
        }
    }
    *p = new AVLNode(aKey);

    // 自底向上沿祖先链修正各祖先结点的平衡因子
    while (!ancestors.empty())
    {
        // 修正祖先结点的平衡因子
        auto aPair = ancestors.top();
        ancestors.pop();
        AVLNode *&curr = *aPair.first;
        curr->balance += aPair.second;

        // 检查平衡状态
        switch (curr->balance)
        {
        case 0:
            // 祖先结点的平衡因子不会再变化，结束修正过程
            return 0;
        case -1:
        case 1:
            // 没有失衡，但平衡因子的变化还需要继续向上传递
            break;
        case 2: // 新结点在左子树上
            switch (curr->lchild->balance)
            {
            case 1:
                // 新结点在左子的左子上（LL型）
                LLAdjust(curr);
                break;
            case -1:
                // 新结点在左子的右子上（LR型）
                LRAdjust(curr);
                break;
            }
            return 0;
        case -2: // 新结点在右子树上
            switch (curr->rchild->balance)
            {
            case 1:
                // 新结点在右子的左子上（RL型）
                RLAdjust(curr);
                break;
            case -1:
                // 新结点在右子的右子上（RR型）
                RRAdjust(curr);
                break;
            }
            return 0;
        }
    }
    return 0;
}

int Print(AVLTree T, int aLevel)
{
    if (T == nullptr)
        return 0;
    Print(T->rchild, aLevel + 1);
    for (int i = 0; i < aLevel; i++)
        cout << "   ";
    cout << T->key << '(' << T->balance << ')' << endl;
    Print(T->lchild, aLevel + 1);
    return 0;
}

int main()
{
    AVLTree T = nullptr;
    int datas[]{45, 32, 16, 77, 94, 38, 44, 21, 39, 68, 33, 87};
    for (int x : datas)
    {
        cout << "Insert " << x << endl;
        Insert(T, x);
        Print(T, 0);
        cout << endl;
    }
    delete T;
    return 0;
}