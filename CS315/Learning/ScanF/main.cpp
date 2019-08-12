#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main() {
    int a, b;
    vector<string> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    scanf("%d %d", &a, &b);
    
    
    for( int i = a; i <= b; i++)
    {
        if( i <= 9)
        {
            string num = words.at(i - 1);
            printf("%s \n", num);
        }
        else if( i%2 == 0)
        {
            printf("even \n");
        }
        else
        {
            printf("odd \n");
        }
    }
    return 0;
}