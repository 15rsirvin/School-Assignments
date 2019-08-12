/* 
 * File:   PowerString.cpp
 * Purpose: provide the definition of the PowerString class
 *
 * Solution 0: using stack's Last-In-First-Out feature
 *             to reverse a sequence 
 * Author: Pike
 *
 */
#include <iostream>
#include "PowerString.h"

// initialize str with ini_str passing as a parameter
PowerString::PowerString(string ini_str)
{
    this->str = ini_str;
}
// return the current value of the private data member: str
string PowerString::getString() const
{
    return str;
}

// set the value of str to be the passed in parameter input_str
void PowerString::setString(string input_str)
{
    str = input_str;
}

// return a reversed string. Note that str has not been changed
string PowerString::reverse() const
{
    string shorter = str.substr(1, str.length() -1);
    PowerString tagon(shorter);

    if(str.length() <= 1)
    {
        return str;
    }
    
    else
    {
        return tagon.reverse() + str[0];
    }
    
}

// return a palindrome which contains str then followed by
//                     the reverse of str without the last character of str
// for example, if str is "abc", it returns "abcba";
//              if str is "ab", it returns "aba", and so on.
// return value is guaranteed to be a palindrome with odd number of characters
// Note that str has not been changed
string PowerString::oddPalindrome() const
{
    string shorter = str.substr(1, str.length() -1);
    PowerString tagon(shorter);

    if (str.length() <= 1)
    {
        return str;
    }

    else
    {
        return str[0] + tagon.oddPalindrome() + str[0];
    }
}
// return true if str is a palindrome
// otherwise return false
// A palindrome is defined as a sequence of characters which reads the same backward as forward
bool PowerString::isPalindrome() const
{
    if(str.length() <= 1)
    {
        return true;
    }

    char first = str[0];
    char last = str[str.length() - 1];

    if(first == last)
    {
        string shorter = str.substr(1,str.length() - 2);
        PowerString tagon(shorter);

        return tagon.isPalindrome();
        
    }

    else
        return false;
}

// displays str followed by a new line marker
//              to the standard output
void PowerString::print() const
{
    cout << str << endl;
}

