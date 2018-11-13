#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int Shuffle(char *nodes, int n)
{
	for (int i=0; i<10*n; i++)
	{
		int x = rand()%n;
		int y = rand()%n;
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
	if (T==NULL) return 0;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	delete T;
	return 1;
}
BiTree CreateBiTree(const char *nodes)
{
	BiTree T = NULL;
	for (const char *p=nodes; *p!='\0'; p++)
	{
		BiTree *tp = &T;
		while (*tp!=NULL)
		{
			if ((rand()%2)==0)
				tp = &((*tp)->lchild);
			else
				tp = &((*tp)->rchild);
		}
		*tp = new BiNode;
		(*tp)->data = *p;
		(*tp)->lchild = (*tp)->rchild = NULL;
	}
	return T;
}
int VPreBiTree(BiTree T)
{
	if (T==NULL)
	{
		cout << "#";
		return 1;
	}
	cout << T->data;
	VPreBiTree(T->lchild);
	VPreBiTree(T->rchild);
	return 1;
}
int PreBiTree(BiTree T)
{
	if (T==NULL) return 1;
	cout << T->data;
	PreBiTree(T->lchild);
	PreBiTree(T->rchild);
	return 1;
}
int InBiTree(BiTree T)
{
	if (T==NULL) return 1;
	InBiTree(T->lchild);
	cout << T->data;
	InBiTree(T->rchild);
	return 1;
}
int SucBiTree(BiTree T)
{
	if (T==NULL) return 1;
	SucBiTree(T->lchild);
	SucBiTree(T->rchild);
	cout << T->data;
	return 1;
}

int main(int argc, char *args[])
{
	srand((unsigned int)time(NULL));
	char defaultstr[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	int n = (rand() % strlen(defaultstr)) + 1;
	char *s = defaultstr;
	s[n] = '\0';
	if (argc==2)
	{
		s = args[1];
		n = strlen(s);
	}
	Shuffle(s, n);
	BiTree T = CreateBiTree(s);
	VPreBiTree(T); cout << endl;
	PreBiTree(T); cout << endl;
	InBiTree(T); cout << endl;
	SucBiTree(T); cout << endl;
	DestroyBiTree(T);
	return 1;
}
