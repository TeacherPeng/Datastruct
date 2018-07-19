#include <iostream>
using namespace std;

// 用链式结构实现队列，数据元素为货车编号
struct QueueNode
{
	int data;
	QueueNode *next;
};
struct Queue
{
	QueueNode *head, *tail;
};

// 初始化
int InitQueue(Queue &Q)
{
	Q.head = Q.tail = NULL;
	return 0;
}

// 判断队列是否为空
bool Empty(Queue Q)
{
	return Q.head == NULL;
}

// 读取队首元素
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
	p->next = NULL;

	// 入队
	if (Q.tail == NULL)
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

// 出队，约定队列空时返回1
int DeQueue(Queue &Q)
{
	if (Empty(Q)) return 1;
	
	// 暂存队首结点
	QueueNode *p = Q.head;
	
	// 摘除队首结点
	Q.head = Q.head->next;
	if (Q.head == NULL) Q.tail = NULL;

	// 删除摘下的队首结点
	delete p;
	
	return 0;
}

// 撤销
int DestroyQueue(Queue &Q)
{
	while (!Empty(Q))
		DeQueue(Q);
	return 0;
}

// 操作菜单
int ShowMenu()
{
	cout << "1. 货车入库" << endl;
	cout << "2. 货车出库" << endl;
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
			// 货车入库
			int aNo;
			cout << "请输入入库货车号：";
			cin >> aNo;
			if (EnQueue(Q, aNo) != 0)
				cout << "入库失败！" << endl;
			else
				cout << aNo << "号货车入库完毕。" << endl;
			break;
		}
		case 2:
		{
			// 货车出队
			if (Empty(Q))
			{
				cout << "车库里是空的，没有货车可以出库了。" << endl;
			}
			else
			{
				int aNo = Top(Q);
				DeQueue(Q);
				cout << aNo << "号货车出库。" << endl;
			}
			break;
		}
		}
	}
	DestroyQueue(Q);
	return 0;
}
