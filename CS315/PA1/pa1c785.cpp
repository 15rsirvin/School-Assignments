/*
 * NAME: pa1c785.cpp
 * synopsis: ./a.out < test1.txt    
 * Compilation: g++ pa1c785.cpp
 * Description: for an input file that starts with two integers, a and N followed by a single line of text. 
 *              The third line is an arbitrary number of integers less than N, all seperated by spaces.
 *              Program outputs a and n, followed by ascii values of line of text multipled by a mod N. 
 *              The third line of output is a, q, N, where q is the modular inverese of a mod N. 
 *              The fourth Line of output is the line of integers input decoded back into ascii characters 
 *              using the modular inverse and outputed to screen.
 * AUTHOR: Robert Irvin
 * SID: 8785
 * DATE: October 2018
 * RunningTime: O(n)
 * BUGS:
 * References:
*/
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// prototype function
int modularInverse(int a, int N);

int main() {
        int a, b;

        // Get inputs a, b, and the two lines
        string str1, str2;
        scanf("%d %d\n", &a, &b);
        getline(cin,str1);
        getline(cin, str2);

        // Print a and b for first line of output
        cout << a << " " << b << endl;

        // Convert from string to ASCII char (mod b) while printing
        for (int i=0 ; i<str1.length() ; i++) {
              int val = int(str1[i]);
              int cryptVal = (val * a) % b;
              cout << cryptVal << " ";
        }
        cout << endl;

        // find modulare inverse of a and b, then print formated results
        int modInverse = modularInverse(a,b);
        cout << a << " " <<  modInverse << " " << b << endl;

        // convert from ASCII Char mod b to string while printing
        int num, decrypt;
        stringstream iss(str2);
        while (iss >> num)
        {
            decrypt = (num * modInverse) % b;

            char asciiChar = decrypt;

            cout << asciiChar;
        }
        cout << endl;
        return 0;
        
}// End of Main Funciton


// Takes as input integers a and N where a < N and gcd(a,N) = 1
// uses extended Euclidean algorithm to calculate the inverse of a (mod N)
// finds the congruent value to inverse in the residue class of N. (i.e. between 0 and N)
// outputs the modular inverse, an integer in the range (0,N)
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