#include <iostream>
#include <stack>
#include <string> 
using namespace std;

int main()
{
	string exp;
	while (getline(cin, exp))
	{
		stack<int> s;
		for (int i = 0; i < exp.size(); i++)
		{
		    char ch = exp[i];
			if (ch == '(')
			{
				s.push(i);
			}
			else if (ch == ')')
			{
				if (s.empty())
				{
					cout << "err" << endl;
					break;
				}
				cout << s.top() << ", " << i << endl;
				s.pop();
			}
		}
		if (!s.empty()) cout << "err" << endl;
	}
	return 0;
}
