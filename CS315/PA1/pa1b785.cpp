/*
 * NAME: pa1b785.cpp
 * synopsis: ./a.out < test1.txt    
 * Compilation: g++ pa1b785.cpp
 * Description: for an input file that starts with two integers, and is followed by a single line of text
 *              it writes a list of the ASCII values for each charachter seperated by a space.
 * AUTHOR: Robert Irvin
 * SID: 8785
 * DATE: October 2018
 * RunningTime: O(n)
 * BUGS:
 * References:
*/
#include <string>
#include <iostream>

using namespace std;

int main() {
        int a, b;

        // Get inputs a, b, and the two lines
        string str1, str2;
        scanf("%d %d\n", &a, &b);
        getline(cin,str1);

        // Print a and b for first line of output
        cout << a << " " << b << endl;

        // Convert from string to ASCII char (mod b) while printing
        for (int i=0 ; i<str1.length() ; i++) {
              int val = int(str1[i]);
              int cryptVal = (val * a) % b;
              cout << cryptVal << " ";
        }
        cout << endl;

}// End of Main Funciton
