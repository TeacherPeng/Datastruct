#include <iostream>
using namespace std;

// ����ʽ�ṹʵ�ֶ��У�����Ԫ��Ϊ�������
struct QueueNode
{
	int data;
	QueueNode *next;
};
struct Queue
{
	QueueNode *head, *tail;
};

// ��ʼ��
int InitQueue(Queue &Q)
{
	Q.head = Q.tail = nullptr;
	return 0;
}

// �ж϶����Ƿ�Ϊ��
bool Empty(Queue Q)
{
	return Q.head == nullptr;
}

// ��ȡ����Ԫ��
int Top(Queue Q)
{
	return Q.head->data;
}

// ���
int EnQueue(Queue &Q, int data)
{
	// �����½��
	QueueNode *p = new QueueNode;
	p->data = data;
	p->next = nullptr;

	// ���
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

// ���ӣ�Լ�����п�ʱ����1
int DeQueue(Queue &Q)
{
	if (Empty(Q)) return 1;
	
	// �ݴ���׽��
	QueueNode *p = Q.head;
	
	// ժ�����׽��
	Q.head = Q.head->next;
	if (Q.head == nullptr) Q.tail = nullptr;

	// ɾ��ժ�µĶ��׽��
	delete p;
	
	return 0;
}

// ����
int DestroyQueue(Queue &Q)
{
	while (!Empty(Q))
		DeQueue(Q);
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
	InitQueue(Q);
	int op;
	while ((op = ShowMenu()) != 0)
	{
		switch (op)
		{
		case 1:
		{
			// �������
			int aNo;
			cout << "�������������ţ�";
			cin >> aNo;
			if (EnQueue(Q, aNo) != 0)
				cout << "���ʧ�ܣ�" << endl;
			else
				cout << aNo << "�Ż��������ϡ�" << endl;
			break;
		}
		case 2:
		{
			// ��������
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
