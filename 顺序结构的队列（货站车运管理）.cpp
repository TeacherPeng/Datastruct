#include <iostream>
using namespace std;

// 用顺序结构实现队列，数据元素为货车编号
struct Queue
{
	int *datas;
	int bufferlen;
	int head, tail; // head为出队端，tail为入队端 
};

// 初始化
int InitQueue(Queue &Q, int n)
{
	Q.datas = new int[n];
	Q.bufferlen = n;
	Q.head = Q.tail = 0;
	return 0;
}

// 撤销
int DestroyQueue(Queue &Q)
{
	delete[]Q.datas;
	Q.datas = NULL;
	Q.bufferlen = 0;
	Q.head = Q.tail = 0;
	return 0;
}

// 判断队列是否为空
bool Empty(Queue &Q)
{
	return Q.head == Q.tail;
}

bool Full(Queue &Q)
{
	return ((Q.tail + 1) % Q.bufferlen) == Q.head;
}

// 读取队首元素
int Top(Queue &Q)
{
	return Q.datas[Q.head];
}

// 入队，约定队列已满返回1
int EnQueue(Queue &Q, int data)
{
	if (Full(Q)) return 1;
	Q.datas[Q.tail] = data;
	Q.tail = (Q.tail + 1) % Q.bufferlen;
	return 0;
}

// 出队，约定队列空时返回1
int DeQueue(Queue &Q)
{
	if (Empty(Q)) return 1;
	Q.head = (Q.head + 1) % Q.bufferlen;
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
	InitQueue(Q, 100);
	int op;
	while ((op = ShowMenu()) != 0)
	{
		switch (op)
		{
		case 1:
		{
			// 货车进站
			int aNo;
			cout << "请输入入库货车号：";
			cin >> aNo;
			if (EnQueue(Q, aNo) != 0)
				cout << "入库失败！" << endl;
			else
				cout << aNo << "号货车入库完毕。" << endl;
			cout << aNo << "号货车入库完毕。" << endl;
			break;
		}
		case 2:
		{
			// 货车出站
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