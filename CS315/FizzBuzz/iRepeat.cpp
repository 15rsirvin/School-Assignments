#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    int a;

    cin >> a;

    for(int i=0; i < a; i++)
    {
        string input;
        bool done;
        int output;
        cin >> input;

        while( done != true)
        {
            for(int j = 1; j <= input.size(); j++)
            {
                string subString = input.substr(0,j);
                if (input.size() % subString.size() == 0)
                {
                    bool s = true;
                    for(int k = 0; k <= (input.size() / subString.size()) -1; i++)
                    {
                        if( subString != input.substr(k * subString.size()))
                            s = false;
                    }
                    if (s == true)
                        done = true;
                }
                if(done)
                    cout << j << endl;
            }
        }
        


        
    }
    return 0;
}