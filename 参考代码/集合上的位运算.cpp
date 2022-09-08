#include <iostream>
using namespace std;

using SmallSet = long;

int Set(SmallSet &aSet, int aIndex)
{
    aSet |= (1 << aIndex);
    return 0;
}

int Reset(SmallSet &aSet, int aIndex)
{
    aSet &= ~(1 << aIndex);
    return 0;
}

int Reverse(SmallSet &aSet, int aIndex)
{
    aSet ^= (1 << aIndex);
    return 0;
}

SmallSet ComplementarySet(SmallSet aFullSet, SmallSet aSet)
{
    return aFullSet & ~aSet;
}

SmallSet IntersectionSet(SmallSet aSet1, SmallSet aSet2)
{
    return aSet1 & aSet2;
}

SmallSet UnionSet(SmallSet aSet1, SmallSet aSet2)
{
    return aSet1 | aSet2;
}

SmallSet DifferenceSet(SmallSet aSet1, SmallSet aSet2)
{
    return aSet1 ^ aSet2;
}

bool Has(SmallSet aSet, int aIndex)
{
    return (aSet & (1 << aIndex)) != 0;
}

int Print(SmallSet aSet)
{
    cout << "{";
    for (int aIndex = 0; aSet != 0; aIndex++, aSet >>= 1)
    {
        if (Has(aSet, 0))
            cout << aIndex << ", ";
    }
    cout << "}" << endl;
    return 0;
}

int main()
{
    SmallSet aSet = 11;
    Print(aSet);

    cout << "Set 4: ";
    Set(aSet, 4);
    Print(aSet);

    cout << "Reset 3: ";
    Reset(aSet, 3);
    Print(aSet);

    cout << "Complementary :";
    SmallSet aSet2 = ComplementarySet(0xff, aSet);
    Print(aSet2);

    cout << "Reverse 5: ";
    Reverse(aSet, 5);
    Print(aSet);

    cout << "Reverse 5: ";
    Reverse(aSet, 5);
    Print(aSet);

    return 0;
}