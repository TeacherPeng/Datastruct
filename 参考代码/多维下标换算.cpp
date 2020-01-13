#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        vector<long long> l(n);
        for (int i = 0; i < n; i++)
            cin >> l[i];
        
        vector<long long> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];

        long long index = 0;
        for (int i = 0; i < n; i++)
        {
            long long m = a[i];
            for (int j = i + 1; j < n; j++)
            {
                m *= l[j];
            }
            index += m;
        }
        cout << index << endl;
    }
    return 0;
}