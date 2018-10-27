#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s1, s2;
	getline(cin, s1); // 整行输入
	cin >> s2;        // 标准输入
	cout << "s1长度为" << s1.size() << ", s2长度为" << s2.size() << endl;
	string s3 = s1;
	string s4 = s1 + s2;
	cout << "s3 is " << s3 << endl;
	cout << "s4 is " << s4 << endl;
	if (s1 == s2)
		cout << "s1与s2内容相同！" << endl;
	else
		cout << "s1与s2内容不相同！" << endl;
	cout << "顺序遍历s1：" << endl;
	for (size_t i = 0; i < s1.size(); i++)
		cout << s1[i];
	cout << endl;
	cout << "顺序遍历s2：" << endl;
	for (const char *p = s2.c_str(); *p != '\0'; p++)
		cout << *p;
	cout << endl;
	cout << "顺序遍历s3：" << endl;
	for (char c : s3)
		cout << c;
	cout << endl;
	return 0;
}
