#include <iostream>
using namespace std;

// ����ʽ�ṹʵ��ջ������Ԫ��Ϊ������
struct StackNode
{
	int data;
	StackNode *next;
};
typedef StackNode *Stack;

// ��ʼ��
int InitStack(Stack &S)
{
	S = nullptr;
	return 0;
}

// �ж�ջ�Ƿ�Ϊ��
bool Empty(Stack S)
{
	return S == nullptr;
}

// ��ȡջ��Ԫ��
int Top(Stack S)
{
	return S->data;
}

// ��ջ
int Push(Stack &S, int data)
{
	// �����½��
	StackNode *p = new StackNode;
	p->data = data;

	// ��ջ
	p->next = S;
	S = p;

	return 0;
}

// ��ջ��Լ��ջ��ʱ����1
int Pop(Stack &S)
{
	if (Empty(S)) return 1;
	// �ݴ�ջ��Ԫ��
	StackNode *p = S;
	// ժ��ջ��Ԫ��
	S = S->next;
	// ɾ��ժ�µ�ջ��Ԫ��
	delete p;
	return 0;
}

// ����
int DestroyStack(Stack &S)
{
	while (!Empty(S))
		Pop(S);
	return 0;
}

// �����˵�
int ShowMenu()
{
	cout << "1. �����ջ" << endl;
	cout << "2. �����ջ" << endl;
	cout << "0. �˳�" << endl;
	cout << "��ѡ�������";

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
			// �����ջ
			int aNo;
			cout << "�������ջ����ţ�";
			cin >> aNo;
			if (Push(S, aNo) != 0)
				cout << "�����ջʧ�ܣ�" << endl;
			else
				cout << aNo << "�ų����ջ��ϡ�" << endl;
			cout << aNo << "�ų����ջ��ϡ�" << endl;
			break;
		}
		case 2:
		{
			// �����ջ
			if (Empty(S))
			{
				cout << "��ջ���ǿյģ�û�г�����Գ�ջ�ˡ�" << endl;
			}
			else
			{
				int aNo = Top(S);
				Pop(S);
				cout << aNo << "�ų����ջ��" << endl;
			}
			break;
		}
		}
	}
	DestroyStack(S);
	return 0;
}
