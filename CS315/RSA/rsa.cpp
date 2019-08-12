#include <iostream> 
#include <vector>

#define ll long long

using namespace std;

ll modular_pow(ll base, ll exponent, int modulus);
int modularInverse(int a, int N);

int main()
{
    vector<string> letters{"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

    int k , p , q;
    cin >> k >> p >> q;

    // Find Values of phi, m, and u
    int phi = (p-1) * (q-1);
    int m = p*q;
    int u = modularInverse(k,phi);
    int input;

    // Take encoded messages
    while (cin >> input)
    {
        // Find decoded output
        int ans = modular_pow(input,u, m);

        // Convert To string to find groups of 2 characters
        string message = to_string(ans);

        for (int i =0; i < message.length(); i += 2)
        {
            string let = message.substr(i,2);

            int val = stoi(let); // convert substr of size 2 back to int

            cout << letters.at(val - 11) << " "; // decode and print (adding a space)

        }
    }
}

// Uses Extended Euclid Algorithm to solve for modular inverse
int modularInverse(int a, int N)
{
    // coeffiecients for Extended Euclid
    int x1 = 1, y1 = 0, R1 = N;
    int x2 = 0, y2 = 1, R2 = a;
    int x3, y3;
    int R3 = 0;

    while(R3 != 1)
    {
        //Find Next Row in Euclid algorithm
        int scale = (R1/R2);
        x3 = x1 - (scale * x2);
        y3 = y1 - (scale * y2);
        R3 = R1 % R2;

        // Shift Rows up by 1
        x1 = x2;
        y1 = y2;
        R1 = R2;

        x2 = x3;
        y2 = y3;
        R2 = R3;
    }

    // Make sure that we get a positive value (congruent to y2 mod N)
    while(y2 < 0)
    {
        y2 += N;
    }
    // I'm not sure if its possible to get y2 > N, but this will make sure you dont.
    y2 = y2 % N;

    return y2;
}


// Source: https://www.sanfoundry.com/cpp-program-implement-modular-exponentiation-algorithm/
ll modular_pow(ll base, ll exponent, int modulus)
{   
    ll result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result =((result * base) % modulus);
        exponent = exponent >> 1;
        base = ( (base * base) % modulus ) ;
    }

    result = result % modulus;
    return result;
}