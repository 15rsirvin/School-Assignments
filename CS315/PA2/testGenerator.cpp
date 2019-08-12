#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>

using namespace std;

int main()
{
    int n, m;
    double w;

    cin >> n >> m >> w;

    cout << n << " " << m << endl;

    for(int i =0; i<n-1; i++)
    {
        cout << i << " " << i+1 << " " << w << endl;
    }
    cout << 0 << " " << 0 << endl;

    return 0;
}