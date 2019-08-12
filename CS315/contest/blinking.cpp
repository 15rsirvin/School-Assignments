#include <iostream>
#include <numeric>

using namespace std;

int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b)
{
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

int main()
{
    int p, q, s;

    cin >> p >> q >> s;

    string outPut = "no";

    int LCM = lcm(p,q);

    if( LCM <= s)
    {
        outPut = "yes";
    }

    cout << outPut << endl;
}