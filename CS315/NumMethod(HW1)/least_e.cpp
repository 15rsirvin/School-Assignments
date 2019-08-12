#include <iostream> 

using namespace std;

int main()
{
    double e = 1.0;
    double e_prev;

    while(1.0 + e != 1)
    {
        e_prev = e;
        e /= 2;
    }

    cout << e_prev << endl;

    return 0;
}

// Output was 2.22045e-16