#include <iostream>
using namespace std;

// ��˳��ṹʵ��ջ������Ԫ��Ϊ������
struct Stack
{
	int *datas;
	int bufferlen;
	int top;  // ��ջԪ�ص��±�
};

// ��ʼ��
int InitStack(Stack &S, int n)
{
	S.datas = new int[n];
	S.bufferlen = n;
	S.top = 0;
	return 0;
}

// ����
int DestroyStack(Stack &S)
{
	delete[]S.datas;
	S.datas = nullptr;
	S.bufferlen = 0;
	S.top = 0;
	return 0;
}

// �ж�ջ�Ƿ�Ϊ��
bool Empty(Stack &S)
{
	return S.top == 0;
}

// ��ȡջ��Ԫ��
int Top(Stack &S)
{
	return S.datas[S.top - 1];
}

// ��ջ��Լ��ջ��������1
int Push(Stack &S, int data)
{
	if (S.top >= S.bufferlen) return 1;
	S.datas[S.top] = data;
	S.top++;
	return 0;
}

// ��ջ��Լ��ջ��ʱ����1
int Pop(Stack &S)
{
	if (Empty(S)) return 1;
	S.top--;
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
	InitStack(S, 100);
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
