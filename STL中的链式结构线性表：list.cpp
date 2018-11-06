#include <iostream>
#include <list>
using namespace std;
int main()
{
	list<int> list1;

	// 添加数据
	for (int i = 0; i < 10; i++) list1.push_back(i);

	// 迭代器遍历输出
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) cout << *it << ", ";
	cout << endl;

	// 在每个数据前插入其10倍
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) list1.insert(it, *it * 10);

	// 迭代器遍历输出
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) cout << *it << ", ";
	cout << endl;

	// 迭代器遍历并删除所有3的倍数
	list<int>::iterator it = list1.begin();
	while (it != list1.end())
	{
		if (*it % 3 == 0) it = list1.erase(it); else it++;
	}

	// 迭代器遍历输出
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) cout << *it << ", ";
	cout << endl;

	return 0;
}
