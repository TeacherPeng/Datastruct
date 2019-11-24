#include <iostream>
using namespace std;

// 链式结构队列定义
struct QueueNode
{
	int data;
	QueueNode *next;
};
struct Queue
{
	QueueNode *head, *tail;
};

// 初始化队列
int InitQueue(Queue &Q)
{
	Q.head = Q.tail = nullptr;
	return 0;
}

// 判断队列是否为空，如果为空，返回true
bool Empty(Queue Q)
{
	return Q.head == nullptr;
}

// 返回队首元素值，即下一个出队元素值
int Top(Queue Q)
{
	return Q.head->data;
}

// 入队
int EnQueue(Queue &Q, int data)
{
	// 创建新结点
	QueueNode *p = new QueueNode;
	p->data = data;
	p->next = nullptr;

	// 新结点追加到队尾的后面
	if (Q.tail == nullptr)
	{
		Q.head = Q.tail = p;
	}
	else
	{
		Q.tail->next = p;
		Q.tail = p;
	}

	return 0;
}

// 出队
int DeQueue(Queue &Q)
{
	if (Empty(Q)) return 1;
	
	// 暂存出队结点
	QueueNode *p = Q.head;
	
	// 将出队结点从队头摘下
	Q.head = Q.head->next;
	if (Q.head == nullptr) Q.tail = nullptr;

	// 删除摘下的结点
	delete p;
	
	return 0;
}

// 撤销队列
int DestroyQueue(Queue &Q)
{
	while (!Empty(Q))
		DeQueue(Q);
	return 0;
}

// 显示操作菜单并返回操作选择
int ShowMenu()
{
	cout << "1. 货车进站" << endl;
	cout << "2. 货车出站" << endl;
	cout << "0. 退出" << endl;
	cout << "请选择操作：";

	int op;
	cin >> op;
	return op;
}

int main()
{
	Queue Q;
	InitQueue(Q);
	int op;
	while ((op = ShowMenu()) != 0)
	{
		switch (op)
		{
		case 1:
		{
			// 货车入站
			int aNo;
			cout << "请输入入站货车的编号：";
			cin >> aNo;
			if (EnQueue(Q, aNo) != 0)
				cout << "入站失败！" << endl;
			else
				cout << aNo << "号货车已入站。" << endl;
			break;
		}
		case 2:
		{
			// 货车出站
			if (Empty(Q))
			{
				cout << "站内已空，没有可出站的货车。" << endl;
			}
			else
			{
				int aNo = Top(Q);
				DeQueue(Q);
				cout << aNo << "号货车出站。" << endl;
			}
			break;
		}
		}
	}
	DestroyQueue(Q);
	return 0;
}
