/*
 *Course: CS216-00x
 *Project: Demo
 *Purpose: it asks the user for age and name
 *         then display to the screen
 */

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int age;
    string name;

    cout << "Enter your age: ";
    cin >> age;
    cout << "Enter your name: ";
    getline(cin, name);

    cout << endl;
    cout << name << " is " << age 
        << " years old." << endl;
    return 0;
}

