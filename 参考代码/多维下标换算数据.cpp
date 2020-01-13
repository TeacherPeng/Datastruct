#include <iostream>
#include <vector>
#include <random>
using namespace std;

// 输入每行为一个测试样例：维数 各维长度 各维下标
// 输出多维下标对应的一维下标
int main()
{
    default_random_engine r;

    // 20道题
    for (int i = 0; i < 20; i++)
    {
        int n = r() % 10 + 2;  // 维数范围2~11
        cout << n;
        vector<int> l(n);
        for (int j = 0; j < n; j++)
        {
            l[j] = r() % 20 + 1; // 维长范围1~20
            cout << ' ' << l[j];
        }
        for (int j = 0; j < n; j++)
        {
            int m = r() % l[j];
            cout << ' ' << m;
        }
        cout << endl;
    }

    return 0;
}