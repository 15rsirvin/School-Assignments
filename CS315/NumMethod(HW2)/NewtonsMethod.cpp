#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

//Prototype Functions
double f(double x);
double f_prime(double x);
void Newton(double x, int nMax);


int main()
{
    Newton(1.5, 5);
    return 0;
}

double f(double x)
{
    return pow(x, 3.0) - pow(x, 2.0) - x - 1;
}

double f_prime(double x) 
{
    return (3 * pow(x, 2.0)) - (2 * x) - 1;
}

void Newton(double x, int nMax)
{
    // Find value of f(x) and store
    double fx = f(x);

    // Print Table Header
    cout << left << setw(5) << setfill(' ') << "n";
    cout << left << setw(15) << setfill(' ') << "xn";
    cout << left << setw(5)  << setfill(' ') << "f(xn)";
    cout << endl;

    cout << left << setw(5) << setfill(' ') << "0";
    cout << left << setw(15) << setfill(' ') << x;
    cout << left << setw(5)  << setfill(' ') << fx;
    cout << endl;

    for (int i = 1; i <= nMax; i++)
    {
        double fp = f_prime(x);
        double d = fx / fp;
        x = x - d;
        fx  = f(x);

        cout << left << setw(5) << setfill(' ') << i;
        cout << left << setw(15) << setfill(' ') << x;
        cout << left << setw(10)  << setfill(' ') << fx;
        cout << endl;
    }
}

