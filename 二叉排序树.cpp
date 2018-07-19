#include <iostream>
#include <ctime>
using namespace std;

struct BiNode
{
	BiNode(int aKey)
	{
		key = aKey;
		lchild = rchild = NULL;
	}
	int key;
	BiNode *lchild, *rchild;
};
typedef BiNode *BiTree;

int InitBiTree(BiTree &T)
{
	T = NULL;
	return 0;
}

int DestroyBiTree(BiTree &T)
{
	if (T == NULL) return 0;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	delete T;
	return 0;
}

BiNode *BSTSearch(BiTree &T, int aKey)
{
	BiNode *p = T;
	while (p != NULL && p->key != aKey)
	{
		p = aKey < p->key ? p->lchild : p->rchild;
	}
	return p;
}

int Insert(BiTree &T, int aKey)
{
	if (T == NULL)
	{
		T = new BiNode(aKey);
		return 0;
	}

	BiNode *p = T;
	while (p != NULL && p->key != aKey)
	{
		if (aKey < p->key)
		{
			if (p->lchild == NULL)
			{
				p->lchild = new BiNode(aKey);
				return 0;
			}
			else
				p = p->lchild;
		}
		else
		{
			if (p->rchild == NULL)
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
	BiNode **p = &T;
	while (*p != NULL && (*p)->key != aKey)
	{
		p = aKey < (*p)->key ? &(*p)->lchild : &(*p)->rchild;
	}
	if (*p != NULL) return 1;
	*p = new BiNode(aKey);
	return 0;
}

int PreTraverse(BiTree T)
{
	if (T == NULL) return 0;
	cout << T->key << ", ";
	PreTraverse(T->lchild);
	PreTraverse(T->rchild);
	return 0;
}
int InTraverse(BiTree T)
{
	if (T == NULL) return 0;
	InTraverse(T->lchild);
	cout << T->key << ", ";
	InTraverse(T->rchild);
	return 0;
}
int SucTraverse(BiTree T)
{
	if (T == NULL) return 0;
	SucTraverse(T->lchild);
	SucTraverse(T->rchild);
	cout << T->key << ", ";
	return 0;
}

int CreateRands(int datas[], int n, int m)
{
	for (int i = 0; i < n; i++)
		datas[i] = i + 1;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < m; i++)
		swap(datas[rand() % n], datas[rand() % n]);
	return 0;
}

int main()
{
	int datas[16], n = 16, m = 20;
	CreateRands(datas, n, m);
	BiTree T;
	InitBiTree(T);
	for (int i = 0; i < n; i++)
	{
		cout << datas[i] << ", ";
		Insert(T, datas[i]);
	}
	cout << endl;
	PreTraverse(T); cout << endl;
	InTraverse(T); cout << endl;
	SucTraverse(T); cout << endl;
	DestroyBiTree(T);
	system("pause");
	return 0;
}