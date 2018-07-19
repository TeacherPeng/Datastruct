#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> list1;

	// 添加数据
	for (int i = 0; i < 10; i++)
		list1.push_back(i);

	// 下标方式遍历输出
	for (int i = 0; i < list1.size(); i++)
		cout << list1[i] << ", ";
	cout << endl;

	// 插入数据
	list1.insert(list1.begin(), 10); // 将10插入到下标0位置
	list1.insert(list1.begin() + 2, 20); // 将20插入到下标2位置

	// 下标方式遍历输出
	for (int i = 0; i < list1.size(); i++)
		cout << list1[i] << ", ";
	cout << endl;

	// 删除下标为5的数据
	list1.erase(list1.begin() + 5); 

	// 下标方式遍历输出
	for (int i = 0; i < list1.size(); i++)
		cout << list1[i] << ", ";
	cout << endl;

	// 下标方式遍历输出
	for (int i = 0; i < list1.size(); i++) 
		cout << list1[i] << ", ";
	cout << endl;

	// 迭代器遍历输出
	for (vector<int>::iterator it = list1.begin(); it != list1.end(); it++)
		cout << *it << ", ";
	cout << endl;

	return 0;
}
