#include <iostream>
using namespace std;

// 用顺序结构实现栈，数据元素为车厢编号
struct Stack
{
	int *datas;
	int bufferlen;
	int top;  // 入栈元素的下标
};

// 初始化
int InitStack(Stack &S, int n)
{
	S.datas = new int[n];
	S.bufferlen = n;
	S.top = 0;
	return 0;
}

// 撤销
int DestroyStack(Stack &S)
{
	delete[]S.datas;
	S.datas = NULL;
	S.bufferlen = 0;
	S.top = 0;
	return 0;
}

// 判断栈是否为空
bool Empty(Stack &S)
{
	return S.top == 0;
}

// 读取栈顶元素
int Top(Stack &S)
{
	return S.datas[S.top - 1];
}

// 入栈，约定栈已满返回1
int Push(Stack &S, int data)
{
	if (S.top >= S.bufferlen) return 1;
	S.datas[S.top] = data;
	S.top++;
	return 0;
}

// 出栈，约定栈空时返回1
int Pop(Stack &S)
{
	if (Empty(S)) return 1;
	S.top--;
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
	InitStack(S, 100);
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
