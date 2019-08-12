#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>

using namespace std;

int main()
{
    int n, m, w;

    cin >> n >> w;

    m = (n *(n-1) )/2;

    cout << n << " " << m << endl;
    assert(w > n);

    for(int i =0; i < n -1; i++)
    {
        for(int j = i +1; j < n; j++)
            cout << i << " " << j << " " << w-j << endl;
    }
    cout << 0 << " " << 0 << endl;

    return 0;
}