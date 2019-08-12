#include <iostream>

using namespace std;

int sumN(int x);

int main()
{
    int userInput;

    cin >> userInput;

    cout << sumN(userInput) << endl;

    return 0;
}

int sumN(int n)
{
    return (n* (n+1) / 2);
}