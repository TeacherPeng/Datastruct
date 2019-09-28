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

// ͼ��Ŀ¼(��ͼ��Ϊ����������Ա���
struct Books
{
	Book *data;
	int bufferlen; // �����Դ洢���ٱ�ͼ�����Ϣ��¼
	int tablelen;  // �����ж��ٱ�ͼ�����Ϣ��¼
};

// ��ʼ��
int InitLibrary(Books &aLib, int aBufferLen)
{
	aLib.data = new Book[aBufferLen];
	aLib.bufferlen = aBufferLen;
	aLib.tablelen = 0;
	return 0;
}

// ��һ����嵽Ŀ¼��ָ��λ��
// Լ��ָ��λ��������������򷵻�1
// Լ���洢�ռ�����������򷵻�2
int InsertBook(Books &aLib, Book aBook, int aIndex)
{
	// �������Ƿ����
	if (aIndex < 0 || aIndex > aLib.tablelen) return 1;

	// ���洢�ռ��Ƿ��п�����ÿռ�
	if (aLib.bufferlen <= aLib.tablelen) return 2;

	// ������λ�õ���β�ļ�¼�����һλ���ڲ���λ���ڳ�һ����λ��
	for (int i = aIndex; i < aLib.tablelen; i++)
		for (int i = aLib.tablelen - 1; i >= aIndex; i--)
		{
			aLib.data[i + 1] = aLib.data[i];
		}

	// ���¼�¼��д���ڳ��Ŀ�λ�С�
	aLib.data[aIndex] = aBook;

	// ������¼����
	aLib.tablelen++;

	return 0;
}

// ��ͼ��Ŀ¼��ɾ��ָ��λ�õ�ͼ���¼
// Լ��ָ��λ��������������򷵻�1
int RemoveBook(Books &aLib, int aIndex)
{
	// �������Ƿ����
	if (aIndex < 0 || aIndex >= aLib.tablelen) return 1;

	// ��ɾ��λ�ú�������м�¼��ǰ��һλ������Ҫɾ���ļ�¼��
	for (int i = aIndex + 1; i < aLib.tablelen; i++)
	{
		aLib.data[i - 1] = aLib.data[i];
	}

	// ������¼����
	aLib.tablelen--;

	return 0;
}

// ��ӡͼ��Ŀ¼
int PrintBooks(Books &aLib)
{
	for (int i = 0; i < aLib.tablelen; i++)
	{
		cout << aLib.data[i].name << "\t"
			<< aLib.data[i].author << "\t"
			<< aLib.data[i].code << endl;
	}
	return 0;
}

// ����������ͼ���¼������ҵ���������ţ��±꣩�����û���ҵ���Լ������-1��
int FindBook(Books &aLib, char aName[])
{
	// ˳���������
	for (int i = 0; i < aLib.tablelen; i++)
	{
		if (strcmp(aLib.data[i].name, aName) == 0)
			return i;
	}
	return -1;
}

// ����
int DestroyLibrary(Books &aLib)
{
	delete[]aLib.data;
	aLib.data = nullptr;
	aLib.bufferlen = 0;
	aLib.tablelen = 0;
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
	InitLibrary(lib, 100);

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
			if (InsertBook(lib, aBook, aIndex) == 0)
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
			int aIndex = FindBook(lib, aName);
			if (aIndex < 0)
				cout << "û���ҵ���ͬ�����ļ�¼��" << endl;
			else if (RemoveBook(lib, aIndex) == 0)
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
			int aIndex = FindBook(lib, aName);
			if (aIndex < 0)
				cout << "û���ҵ���ͬ�����ļ�¼��" << endl;
			else
				cout << aIndex << ".\t"
				<< lib.data[aIndex].name << "\t"
				<< lib.data[aIndex].author << "\t"
				<< lib.data[aIndex].code << endl;
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
