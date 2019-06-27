#include <iostream>
using namespace std;

// 用链式结构实现栈，数据元素为车厢编号
struct StackNode
{
	int data;
	StackNode *next;
};
typedef StackNode *Stack;

// 初始化
int InitStack(Stack &S)
{
	S = NULL;
	return 0;
}

// 判断栈是否为空
bool Empty(Stack S)
{
	return S == NULL;
}

// 读取栈顶元素
int Top(Stack S)
{
	return S->data;
}

// 入栈
int Push(Stack &S, int data)
{
	// 创建新结点
	StackNode *p = new StackNode;
	p->data = data;

	// 入栈
	p->next = S;
	S = p;

	return 0;
}

// 出栈，约定栈空时返回1
int Pop(Stack &S)
{
	if (Empty(S)) return 1;
	// 暂存栈顶元素
	StackNode *p = S;
	// 摘除栈顶元素
	S = S->next;
	// 删除摘下的栈顶元素
	delete p;
	return 0;
}

// 撤销
int DestroyStack(Stack &S)
{
	while (!Empty(S))
		Pop(S);
	return 0;
}

// 操作菜单
int ShowMenu()
{
	cout << "1. 车厢进栈" << endl;
	cout << "2. 车厢出栈" << endl;
	cout << "0. 退出" << endl;
	cout << "请选择操作：";

	int op;
	cin >> op;
	return op;
}

int main()
{
	Stack S;
	InitStack(S);
	int op;
	while ((op = ShowMenu()) != 0)
	{
		switch (op)
		{
		case 1:
		{
			// 车厢进栈
			int aNo;
			cout << "请输入进栈车厢号：";
			cin >> aNo;
			if (Push(S, aNo) != 0)
				cout << "车厢进栈失败！" << endl;
			else
				cout << aNo << "号车厢进栈完毕。" << endl;
			cout << aNo << "号车厢进栈完毕。" << endl;
			break;
		}
		case 2:
		{
			// 车厢出栈
			if (Empty(S))
			{
				cout << "货栈里是空的，没有车厢可以出栈了。" << endl;
			}
			else
			{
				int aNo = Top(S);
				Pop(S);
				cout << aNo << "号车厢出栈。" << endl;
			}
			break;
		}
		}
	}
	DestroyStack(S);
	return 0;
}
