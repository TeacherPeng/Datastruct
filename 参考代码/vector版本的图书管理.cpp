#include <iostream>	
#include <vector>
#include <cstring>
using namespace std;

// 图书信息
struct Book
{
	char name[1024];
	char author[50];
	char code[20];
};
using Books = vector<Book>;

// 打印图书目录
int PrintBooks(Books &aLib)
{
	for (int i = 0; i < aLib.size(); i++)
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
	for (int i = 0; i < aLib.size(); i++)
	{
		if (strcmp(aLib.data[i].name, aName) == 0)
			return i;
	}
	return -1;
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
			if (lib.insert(lib.begin() + aIndex, aBook) != lib.end())
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
			else 
            {
                lib.erase(lib.begin() + aIndex);
				cout << "删除图书成功！" << endl;
            }
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

	return 0;
}
