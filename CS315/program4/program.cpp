#include<iostream>
#include <vector>

using namespace std;

int main()
{
    int num;

    cin >> num;

    vector<int> answers;

    vector<int> top{ 1, 2, 3};
    vector<int> mid{ 4, 5, 6};
    vector<int> bot{ 7, 8, 9};
    vector<int> zero{ -1, 0, -1};

    vector<vector<int>> numPad{top,mid,bot,zero}; 

    for (int i= 0; i < num; i++)
    {
        int input;
        cin >> input;

        int dig1, dig2, dig3;
        int finDig1, finDig2, finDig3;

        dig1 = (input / 100);
        dig3 = input % 10;
        dig2 = (input % 100) - dig3;

        int loc = numPad.at(0).at(0);
        int a,b;
        a = 0;
        b = 0;

        bool found2 = false;

        while(found2 == false && a <= 3 && b <= 2)
        {
            if(a < 3 && dig2 > numPad.at(a+1).at(b) && numPad.at(a+1).at(b) != -1)
            {
                a += 1;
            }

            else if(b < 2 && dig2 > numPad.at(a).at(b +1) && numPad.at(a).at(b+1) != -1)
            {
                b += 1;
            }
            else{
                found2 = true;
            }
        }
        finDig2 = numPad.at(a).at(b);

        bool found3 = false;

        while(found3 == false && a <= 3 && b <= 2)
        {
            if(a < 3 && dig3 > numPad.at(a+1).at(b) && numPad.at(a+1).at(b) != -1)
            {
                a += 1;
            }

            else if(b < 2 && dig3 > numPad.at(a).at(b +1) && numPad.at(a).at(b+1) != -1)
            {
                b += 1;
            }
            else if(dig3 == 0)
            {
                a =3;
                b =1;
                found3 = true;
            }
            else{
                found3 = true;
            }
        }
        finDig3 = numPad.at(a).at(b);

        cout << dig1 << endl 
                << finDig2 << endl
                << finDig3 << endl;

        int answer = (dig1 * 100) + (finDig2 * 10) + finDig3;

        answers.push_back(answer);
    }

    for(int i = 0; i < answers.size(); i++)
    {
        cout << answers.at(i) << endl;
    }
}
