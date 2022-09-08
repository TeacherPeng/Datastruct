#include <iostream>
using namespace std;

// 链表结点结构定义
struct StackNode
{
	int data;
	StackNode *next;
};
using Stack = StackNode *;

// 初始化栈
int InitStack(Stack &S)
{
	S = nullptr;
	return 0;
}

// 判断栈是否为空，如果为空则返回true
bool Empty(Stack S)
{
	return S == nullptr;
}

// 读取栈顶元素
int Top(Stack S)
{
	return S->data;
}

// 将指定元素入栈
int Push(Stack &S, int data)
{
	// 创建新结点
	StackNode *p = new StackNode;
	p->data = data;

	// 将新结点插入在表头位置
	p->next = S;
	S = p;

	return 0;
}

// 从栈中弹出一个结点
int Pop(Stack &S)
{
	if (Empty(S))
		return 1;
	// 暂存栈顶（表头）结点
	StackNode *p = S;
	// 将栈顶结点摘下
	S = S->next;
	// 删除摘下的结点
	delete p;
	return 0;
}

// 撤销栈
int DestroyStack(Stack &S)
{
	while (!Empty(S))
		Pop(S);
	return 0;
}

// 显示操作菜单，输入并返回操作选择
int ShowMenu()
{
	cout << "1. 车厢入栈" << endl;
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
			// 车厢入栈
			int aNo;
			cout << "请输入入栈车厢的编号：";
			cin >> aNo;
			if (Push(S, aNo) != 0)
				cout << "入栈失败！" << endl;
			else
				cout << aNo << "入栈成功！" << endl;
			cout << aNo << "已入栈。" << endl;
			break;
		}
		case 2:
		{
			// 车厢出栈
			if (Empty(S))
			{
				cout << "栈中没有车厢可以出栈！" << endl;
			}
			else
			{
				int aNo = Top(S);
				Pop(S);
				cout << aNo << "已出栈。" << endl;
			}
			break;
		}
		}
	}
	DestroyStack(S);
	return 0;
}
