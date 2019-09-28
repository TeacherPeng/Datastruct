#include <iostream>	
#include <cstring>
using namespace std;

// ͼ����Ϣ
struct Book
{
	char name[1024];
	char author[50];
	char code[20];
};

// ��¼���
struct BookNode
{
	Book data;
	BookNode* next;
};

typedef BookNode* Books;

// ��ʼ��
int InitLibrary(Books &L)
{
	// ����ͷ���
	L = new BookNode;
	L->next = nullptr;
	return 0;
}

// ��һ����嵽Ŀ¼��ָ��λ�õĺ���
// Լ��ָ��λ��������������򷵻�1
int InsertAfter(BookNode* p, Book aBook)
{
	// �������Ƿ����
	if (p == nullptr) return 1;

	// �����½��
	BookNode* q = new BookNode;
	q->data = aBook;

	// ���½��ҽӵ�ָ��������
	q->next = p->next;
	p->next = q;

	return 0;
}

// ��ͼ��Ŀ¼��ɾ��ָ��λ�ú����ͼ���¼
// Լ��ָ��λ��������������򷵻�1
int RemoveAfter(BookNode* p)
{
	// �������Ƿ����
	if (p == nullptr || p->next == nullptr) return 1;

	// ����ɾ���Ľ�������ժ����
	BookNode* q = p->next;
	p->next = q->next;

	// ɾ��Ŀ����
	delete q;

	return 0;
}

// ��ӡͼ��Ŀ¼
int PrintBooks(Books& L)
{
	for (BookNode* p = L->next; p != nullptr; p = p->next)
	{
		cout << p->data.name << "\t"
			<< p->data.author << "\t"
			<< p->data.code << endl;
	}
	return 0;
}

// ����������ͼ���¼
// ����ҵ�������ָ��ǰһ����ָ��
// ���û���ҵnullptr������NULL��
BookNode* FindPrev(Books &L, char aName[])
{
	// ˳���������
	for (BookNode* p = L; p->next != nullptr; p = p->next)
	{
		if (strcmp(p->next->data.name, aName) == 0)
			return p;
	}
	return nullptr;
}

// ����
int DestroyLibrary(Books& L)
{
	while (L != nullptr)
	{
		BookNode* p = L;
		L = L->next;
		delete p;
	}
	return 0;
}

int ShowMenu()
{
	cout << "1. ����ͼ��" << endl;
	cout << "2. ������ɾ��ͼ��" << endl;
	cout << "3. ����������ͼ��" << endl;
	cout << "4. ��ӡͼ��Ŀ¼" << endl;
	cout << "0. �˳�" << endl;
	cout << "��ѡ��";

	int op;
	cin >> op;
	return op;
}

int main()
{
	Books lib;
	InitLibrary(lib);

	int op;
	while ((op = ShowMenu()) != 0)
	{
		switch (op)
		{
		case 1:
		{
			// ����ͼ�飨���ñ�׼���룬�������������ͱ����в��ܺ��пհ׷���
			Book aBook;
			int aIndex;
			cout << "���������� ���� ���� ���� ����λ�ã�";
			cin >> aBook.name >> aBook.author >> aBook.code >> aIndex;

			// ��λ����λ��
			BookNode* aPos = lib;
			for (int i = 0; i < aIndex && aPos != nullptr; i++)
				aPos = aPos->next;

			if (aPos == nullptr)
				cout << "��λʧ�ܣ�" << endl;
			else if (InsertAfter(aPos, aBook) == 0)
				cout << "�����¼�ɹ���" << endl;
			else
				cout << "�����¼ʧ�ܣ�" << endl;
			break;
		}
		case 2:
		{
			// ������ɾ��ͼ��
			char aName[1024];
			cout << "������Ҫɾ��ͼ���������";
			cin >> aName;
			BookNode* aPos = FindPrev(lib, aName);
			if (aPos == nullptr)
				cout << "û���ҵ�Ҫɾ����ͼ�飡" << endl;
			else if (RemoveAfter(aPos) == 0)
				cout << "ɾ��ͼ��ɹ���" << endl;
			else
				cout << "ɾ��ͼ��ʧ�ܣ�" << endl;
			break;
		}
		case 3:
		{
			// ����������ͼ��
			char aName[1024];
			cout << "������Ҫ���ҵ�ͼ���������";
			cin >> aName;
			BookNode* p = FindPrev(lib, aName);
			if (p == nullptr || p->next == nullptr)
				cout << "û���ҵ���ͬ�����ļ�¼��" << endl;
			else
				cout << p->next->data.name << "\t"
					<< p->next->data.author << "\t"
					<< p->next->data.code << endl;
			break;
		}
		case 4:
		{
			// ��ӡͼ��Ŀ¼
			PrintBooks(lib);
			break;
		}
		}
	}

	DestroyLibrary(lib);
	return 0;
}
