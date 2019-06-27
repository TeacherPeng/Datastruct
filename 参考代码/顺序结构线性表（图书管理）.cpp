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

// 图书目录(以图书为数据项的线性表）
struct Books
{
	Book *data;
	int bufferlen; // 最多可以存储多少本图书的信息记录
	int tablelen;  // 现在有多少本图书的信息记录
};

// 初始化
int InitLibrary(Books &aLib, int aBufferLen)
{
	aLib.data = new Book[aBufferLen];
	aLib.bufferlen = aBufferLen;
	aLib.tablelen = 0;
	return 0;
}

// 将一本书插到目录的指定位置
// 约定指定位置如果不合理，则返回1
// 约定存储空间如果已满，则返回2
int InsertBook(Books &aLib, Book aBook, int aIndex)
{
	// 检查参数是否合理
	if (aIndex < 0 || aIndex > aLib.tablelen) return 1;

	// 检查存储空间是否有空余可用空间
	if (aLib.bufferlen <= aLib.tablelen) return 2;

	// 将插入位置到表尾的记录向后移一位，在插入位置腾出一个空位。
	for (int i = aIndex; i < aLib.tablelen; i++)
		for (int i = aLib.tablelen - 1; i >= aIndex; i--)
		{
			aLib.data[i + 1] = aLib.data[i];
		}

	// 将新记录填写在腾出的空位中。
	aLib.data[aIndex] = aBook;

	// 修正记录个数
	aLib.tablelen++;

	return 0;
}

// 从图书目录中删除指定位置的图书记录
// 约定指定位置如果不合理，则返回1
int RemoveBook(Books &aLib, int aIndex)
{
	// 检查参数是否合理
	if (aIndex < 0 || aIndex >= aLib.tablelen) return 1;

	// 将删除位置后面的所有记录向前移一位，覆盖要删除的记录。
	for (int i = aIndex + 1; i < aLib.tablelen; i++)
	{
		aLib.data[i - 1] = aLib.data[i];
	}

	// 修正记录个数
	aLib.tablelen--;

	return 0;
}

// 打印图书目录
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

// 按书名查找图书记录，如果找到，返回序号（下标），如果没有找到，约定返回-1。
int FindBook(Books &aLib, char aName[])
{
	// 顺序遍历查找
	for (int i = 0; i < aLib.tablelen; i++)
	{
		if (strcmp(aLib.data[i].name, aName) == 0)
			return i;
	}
	return -1;
}

// 撤销
int DestroyLibrary(Books &aLib)
{
	delete[]aLib.data;
	aLib.data = NULL;
	aLib.bufferlen = 0;
	aLib.tablelen = 0;
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
	InitLibrary(lib, 100);

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
			if (InsertBook(lib, aBook, aIndex) == 0)
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
			int aIndex = FindBook(lib, aName);
			if (aIndex < 0)
				cout << "没有找到相同书名的记录！" << endl;
			else if (RemoveBook(lib, aIndex) == 0)
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
			int aIndex = FindBook(lib, aName);
			if (aIndex < 0)
				cout << "没有找到相同书名的记录！" << endl;
			else
				cout << aIndex << ".\t"
				<< lib.data[aIndex].name << "\t"
				<< lib.data[aIndex].author << "\t"
				<< lib.data[aIndex].code << endl;
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
