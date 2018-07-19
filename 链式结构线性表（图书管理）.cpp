#include <iostream>	
#include <cstring>
using namespace std;

// 图书信息
struct Book
{
	char name[1024];
	char author[50];
	char code[20];
};

// 记录结点
struct BookNode
{
	Book data;
	BookNode* next;
};

typedef BookNode* Books;

// 初始化
int InitLibrary(Books &L)
{
	// 创建头结点
	L = new BookNode;
	L->next = NULL;
	return 0;
}

// 将一本书插到目录的指定位置的后面
// 约定指定位置如果不合理，则返回1
int InsertAfter(BookNode* p, Book aBook)
{
	// 检查参数是否合理
	if (p == NULL) return 1;

	// 创建新结点
	BookNode* q = new BookNode;
	q->data = aBook;

	// 将新结点挂接到指定结点后面
	q->next = p->next;
	p->next = q;

	return 0;
}

// 从图书目录中删除指定位置后面的图书记录
// 约定指定位置如果不合理，则返回1
int RemoveAfter(BookNode* p)
{
	// 检查参数是否合理
	if (p == NULL || p->next == NULL) return 1;

	// 将待删除的结点从链上摘下来
	BookNode* q = p->next;
	p->next = q->next;

	// 删除目标结点
	delete q;

	return 0;
}

// 打印图书目录
int PrintBooks(Books& L)
{
	for (BookNode* p = L->next; p != NULL; p = p->next)
	{
		cout << p->data.name << "\t"
			<< p->data.author << "\t"
			<< p->data.code << endl;
	}
	return 0;
}

// 按书名查找图书记录
// 如果找到，返回指向前一结点的指针
// 如果没有找到，约定返回NULL。
BookNode* FindPrev(Books &L, char aName[])
{
	// 顺序遍历查找
	for (BookNode* p = L; p->next != NULL; p = p->next)
	{
		if (strcmp(p->next->data.name, aName) == 0)
			return p;
	}
	return NULL;
}

// 撤销
int DestroyLibrary(Books& L)
{
	while (L != NULL)
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
	cout << "2. 按书名删除图书" << endl;
	cout << "3. 按书名查找图书" << endl;
	cout << "4. 打印图书目录" << endl;
	cout << "0. 退出" << endl;
	cout << "请选择：";

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
			// 添加图书（采用标准输入，书名、作者名和编码中不能含有空白符）
			Book aBook;
			int aIndex;
			cout << "请依次输入 书名 作者 编码 插入位置：";
			cin >> aBook.name >> aBook.author >> aBook.code >> aIndex;

			// 定位插入位置
			BookNode* aPos = lib;
			for (int i = 0; i < aIndex && aPos != NULL; i++)
				aPos = aPos->next;

			if (aPos == NULL)
				cout << "定位失败！" << endl;
			else if (InsertAfter(aPos, aBook) == 0)
				cout << "插入记录成功！" << endl;
			else
				cout << "插入记录失败！" << endl;
			break;
		}
		case 2:
		{
			// 按书名删除图书
			char aName[1024];
			cout << "请输入要删除图书的书名：";
			cin >> aName;
			BookNode* aPos = FindPrev(lib, aName);
			if (aPos == NULL)
				cout << "没有找到要删除的图书！" << endl;
			else if (RemoveAfter(aPos) == 0)
				cout << "删除图书成功！" << endl;
			else
				cout << "删除图书失败！" << endl;
			break;
		}
		case 3:
		{
			// 按书名查找图书
			char aName[1024];
			cout << "请输入要查找的图书的书名：";
			cin >> aName;
			BookNode* p = FindPrev(lib, aName);
			if (p == NULL || p->next == NULL)
				cout << "没有找到相同书名的记录！" << endl;
			else
				cout << p->next->data.name << "\t"
					<< p->next->data.author << "\t"
					<< p->next->data.code << endl;
			break;
		}
		case 4:
		{
			// 打印图书目录
			PrintBooks(lib);
			break;
		}
		}
	}

	DestroyLibrary(lib);
	return 0;
}
