#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct BiNode
{
	string data;
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
	T = NULL;
	return 0;
}

int GetDepth(BiTree T)
{
	if (T == NULL) return 0;
	return max(GetDepth(T->lchild), GetDepth(T->rchild)) + 1;
}

int GetNodeNumber(BiTree T)
{
	if (T == NULL) return 0;
	return GetNodeNumber(T->lchild) + GetNodeNumber(T->rchild) + 1;
}

int PreTraverse(BiTree T)
{
	if (T == NULL) return 0;
	cout << T->data << endl;
	PreTraverse(T->lchild);
	PreTraverse(T->rchild);
	return 0;
}

int InTraverse(BiTree T)
{
	if (T == NULL) return 0;
	InTraverse(T->lchild);
	cout << T->data << endl;
	InTraverse(T->rchild);
	return 0;
}

int SucTraverse(BiTree T)
{
	if (T == NULL) return 0;
	SucTraverse(T->lchild);
	SucTraverse(T->rchild);
	cout << T->data << endl;
	return 0;
}

int PreTraverseWithNull(ostream &ostr, BiTree T)
{
	if (T == NULL)
	{
		// 约定#表示空结点
		ostr << "#" << endl;
		return 0;
	}
	ostr << T->data << endl;
	PreTraverseWithNull(ostr, T->lchild);
	PreTraverseWithNull(ostr, T->rchild);
	return 0;
}

// 从输入流中读入带虚结点行的前序遍历行序列（每行对应一个结点），构造并返回构造好的二叉树
BiTree CreateBiTree(istream &istr)
{
	// 从流中读一行内容
	string aData;
	getline(istr, aData);

	// 约定#表示空结点
	if (aData == "#") return NULL;

	// 创建结点
	BiNode *aNode = new BiNode;
	aNode->data = aData;

	// 继续输入并构造左子树和右子树，然后返回结果。
	aNode->lchild = CreateBiTree(istr);
	aNode->rchild = CreateBiTree(istr);
	return aNode;
}

// 用带虚结点的前序遍历串str（每个字符对应一个结点）构造二叉树T，并返回剩余字符串
char *CreateBiTree(BiTree &T, char *str)
{
	// 约定#表示空结点
	if (*str == '#')
	{
		T = NULL;
		return str + 1;
	}

	// 创建结点
	T = new BiNode;
	T->data = *str;

	// 继续输入并构造左子树和右子树
	str = CreateBiTree(T->lchild, str + 1);
	str = CreateBiTree(T->rchild, str);

	// 返回剩余的字符串
	return str;
}

bool IsLeaf(BiNode *p)
{
	return p != NULL && p->lchild == NULL && p->rchild == NULL;
}

BiNode *StartRecognize(BiTree T)
{
	if (T == NULL)
	{
		cout << "知识库是空的，无法工作！" << endl;
		return NULL;
	}

	BiNode *p = T;
	while (!IsLeaf(p))
	{
		string ans;
		cout << p->data << "(Y/N)";
		getline(cin, ans);
		if (ans == "Y" || ans == "y") p = p->rchild; else p = p->lchild;
	}
	cout << "满足条件的物种是：" << p->data << endl;
	return p;
}

int main()
{
	// 从文件里读入初始知识库二叉树
	ifstream istr("datas.txt");
	BiTree T = CreateBiTree(istr);
	istr.close();

	while (true)
	{
		BiNode *p = StartRecognize(T);
		if (p == NULL)
		{
			cout << "请输入第一个已知物种：";
			T = new BiNode;
			getline(cin, T->data);
			T->lchild = T->rchild = NULL;
		}
		else
		{
			cout << "是否需要对回答进行修正？(Y/N/Q)";
			string ans;
			getline(cin, ans);
			if (ans == "Y" || ans == "y")
			{
				p->lchild = new BiNode;
				p->lchild->data = p->data;
				p->lchild->lchild = p->lchild->rchild = NULL;

				cout << "请输入正确的答案：";
				p->rchild = new BiNode;
				getline(cin, p->rchild->data);
				p->rchild->lchild = p->rchild->rchild = NULL;

				cout << "请输入一个识别问题，回答Y是【" << p->rchild->data << "】，回答N是【" << p->lchild->data << "】：";
				getline(cin, p->data);
			}
			else if (ans == "Q" || ans == "q")
				break;
		}
	}

	// 退出前保存知识库二叉树
	ofstream ostr("datas.txt");
	PreTraverseWithNull(ostr, T);
	ostr.close();

	DestroyBiTree(T);
	return 0;
}
