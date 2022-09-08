#include <iostream>	
#include <cstring>
using namespace std;

// 定义数据元素
struct Book
{
	char name[1024];
	char author[50];
	char code[20];
};

// 定义链结点结构
struct BookNode
{
	Book data;
	BookNode* next;
};

using Books = BookNode*;

// 初始化单链表
int InitLibrary(Books &L)
{
	// 创建头结点
	L = new BookNode;
	L->next = nullptr;
	return 0;
}

// 在单链表的指定结点后面插入一个新的数据元素
int InsertAfter(BookNode* p, Book aBook)
{
	// 如果指定结点为空，操作失败
	if (p == nullptr) return 1;

	// 为新数据元素创建存储结点
	BookNode* q = new BookNode;
	q->data = aBook;

	// 将新结点插入在指定结点的后面
	q->next = p->next;
	p->next = q;

	return 0;
}

// 删除指定结点的后继结点
int RemoveAfter(BookNode* p)
{
	// 如果指定结点或指定结点的后继结点为空，操作失败
	if (p == nullptr || p->next == nullptr) return 1;

	// 从链表摘下指定结点的后继结点
	BookNode* q = p->next;
	p->next = q->next;

	// 删除摘下的结点
	delete q;

	return 0;
}

// 遍历输出整个单链表
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

// 顺序查找单链表书名与指定书名相同的数据元素，并返回结点指针
// 如果找不到与指定书名相同的数据元素，则返回空指针
BookNode* FindPrev(Books &L, char aName[])
{
	// 遍历单链表，查找与指定书名相同的数据元素
	for (BookNode* p = L; p->next != nullptr; p = p->next)
	{
		if (strcmp(p->next->data.name, aName) == 0)
			return p;
	}
	return nullptr;
}

// 撤销单链表
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
	cout << "1. 添加图书" << endl;
	cout << "2. 删除图书" << endl;
	cout << "3. 查找图书" << endl;
	cout << "4. 显示图书列表" << endl;
	cout << "0. 退出" << endl;
	cout << "请选择操作：";

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
			// 输入要添加的图书的信息
			Book aBook;
			int aIndex;
			cout << "请依次输入 书名 作者 书号 插入位置：";
			cin >> aBook.name >> aBook.author >> aBook.code >> aIndex;

			// 找到插入位置
			BookNode* aPos = lib;
			for (int i = 0; i < aIndex && aPos != nullptr; i++)
				aPos = aPos->next;

			if (aPos == nullptr)
				cout << "指定插入位置错误！" << endl;
			else if (InsertAfter(aPos, aBook) == 0)
				cout << "添加图书成功！" << endl;
			else
				cout << "添加图书失败！" << endl;
			break;
		}
		case 2:
		{
			// 输入要删除的图书的书名
			char aName[1024];
			cout << "请输入要删除的图书的书名：";
			cin >> aName;
			BookNode* aPos = FindPrev(lib, aName);
			if (aPos == nullptr)
				cout << "没有找到要删除的图书！" << endl;
			else if (RemoveAfter(aPos) == 0)
				cout << "删除指定图书成功！" << endl;
			else
				cout << "删除指定图书失败！" << endl;
			break;
		}
		case 3:
		{
			// 输入要查找的图书的书名
			char aName[1024];
			cout << "请输入要查找的图书的书名：";
			cin >> aName;
			BookNode* p = FindPrev(lib, aName);
			if (p == nullptr || p->next == nullptr)
				cout << "没有找到要查找的图书！" << endl;
			else
				cout << p->next->data.name << "\t"
					<< p->next->data.author << "\t"
					<< p->next->data.code << endl;
			break;
		}
		case 4:
		{
			// 显示图书列表
			PrintBooks(lib);
			break;
		}
		}
	}

	DestroyLibrary(lib);
	return 0;
}
