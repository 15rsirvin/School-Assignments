#include <iostream>
#include <set>

using namespace std;

int main()
{
    int a, b, c, d, e, f, g, h, i, j;

    cin >> a >> b >> c >> d >> e >> f >> g >> h >> i >> j; 

    set<int> setOfNums;

    setOfNums.insert(a % 42);
    setOfNums.insert(b % 42);
    setOfNums.insert(c % 42);
    setOfNums.insert(d % 42);
    setOfNums.insert(e % 42);
    setOfNums.insert(f % 42);
    setOfNums.insert(g % 42);
    setOfNums.insert(h % 42);
    setOfNums.insert(i % 42);
    setOfNums.insert(j % 42);

    cout << setOfNums.size() << endl;

    return 0;

}








