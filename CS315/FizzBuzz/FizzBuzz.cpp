#include <iostream>

using namespace std;

int main()
{
    int a,b,c;
    cin >> a >> b >> c;
    if( b % a != 0)
    {
        for (int i =1; i <= c; i++)
        {
            if (i % (a * b) == 0)
                cout << "FizzBuzz" << endl;
            else if (i % (a) == 0)
                cout << "Fizz" << endl;
            else if (i % b == 0)
                cout << "Buzz" << endl;
            else
                cout << i << endl;
        }
    }
    else
    {
        for (int i =1; i <= c; i++)
        {
            if ((i % b) == 0)
                cout << "FizzBuzz" << endl;
            else if (i % (a) == 0)
                cout << "Fizz" << endl;
            else
                cout << i << endl;
        }
    }

    return 0;
}


