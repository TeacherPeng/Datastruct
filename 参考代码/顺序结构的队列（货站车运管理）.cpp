#include <iostream>
using namespace std;

// ��˳��ṹʵ�ֶ��У�����Ԫ��Ϊ�������
struct Queue
{
	int *datas;
	int bufferlen;
	int head, tail; // headΪ���Ӷˣ�tailΪ��Ӷ� 
};

// ��ʼ��
int InitQueue(Queue &Q, int n)
{
	Q.datas = new int[n];
	Q.bufferlen = n;
	Q.head = Q.tail = 0;
	return 0;
}

// ����
int DestroyQueue(Queue &Q)
{
	delete[]Q.datas;
	Q.datas = nullptr;
	Q.bufferlen = 0;
	Q.head = Q.tail = 0;
	return 0;
}

// �ж϶����Ƿ�Ϊ��
bool Empty(Queue &Q)
{
	return Q.head == Q.tail;
}

bool Full(Queue &Q)
{
	return ((Q.tail + 1) % Q.bufferlen) == Q.head;
}

// ��ȡ����Ԫ��
int Top(Queue &Q)
{
	return Q.datas[Q.head];
}

// ��ӣ�Լ��������������1
int EnQueue(Queue &Q, int data)
{
	if (Full(Q)) return 1;
	Q.datas[Q.tail] = data;
	Q.tail = (Q.tail + 1) % Q.bufferlen;
	return 0;
}

// ���ӣ�Լ�����п�ʱ����1
int DeQueue(Queue &Q)
{
	if (Empty(Q)) return 1;
	Q.head = (Q.head + 1) % Q.bufferlen;
	return 0;
}

// �����˵�
int ShowMenu()
{
	cout << "1. �������" << endl;
	cout << "2. ��������" << endl;
	cout << "0. �˳�" << endl;
	cout << "��ѡ�������";

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
			// ������վ
			int aNo;
			cout << "�������������ţ�";
			cin >> aNo;
			if (EnQueue(Q, aNo) != 0)
				cout << "���ʧ�ܣ�" << endl;
			else
				cout << aNo << "�Ż��������ϡ�" << endl;
			cout << aNo << "�Ż��������ϡ�" << endl;
			break;
		}
		case 2:
		{
			// ������վ
			if (Empty(Q))
			{
				cout << "�������ǿյģ�û�л������Գ����ˡ�" << endl;
			}
			else
			{
				int aNo = Top(Q);
				DeQueue(Q);
				cout << aNo << "�Ż������⡣" << endl;
			}
			break;
		}
		}
	}
	DestroyQueue(Q);
	return 0;
}