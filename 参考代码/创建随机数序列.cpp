#include <iostream>
#include <random>
using namespace std;

int CreateRands(int datas[], int n, int m)
{
    for (int i = 0; i < n; i++)
        datas[i] = i + 1;
    for (int i = 0; i < m; i++)
        swap(datas[rand() % n], datas[rand() % n]);
    return 0;
}

int main()
{
    default_random_engine e;
    int m = 20;
    const int maxn = 100;
    int datas[maxn];
    for (int i = 0; i < m; i++)
    {
        int n = (e() % maxn) + 1;
        cout << n;
        for (int j = 0; j < n; j++)
            datas[j] = j + 1;
        for (int j = 0; j < n + n; j++)
            swap(datas[e() % n], datas[e() % n]);
        for (int j = 0; j < n; j++)
            cout << ' ' << datas[j];
        cout << endl;
    }
    return 0;
}