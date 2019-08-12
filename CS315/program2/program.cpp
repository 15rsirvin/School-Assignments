#include<iostream>
#include <vector>

using namespace std;

int main()
{
    int testcases;

    cin >> testcases;

    vector<int> answers;

    for (int i = 0; i < testcases; i++)
    {
        int M,D;

        cin >> M >> D;

        int curr = 6;
        int ans = 0;
        

        for(int j =0; j < D; j++)
        {
            int monthDays;

            cin >> monthDays;

            // Is Friday 13
            int day = curr;
            if(curr == 6 && monthDays >= 13)
            {
                ans+=1;
            }

            int diff = monthDays % 7;

            if( curr - diff > 0)
            {
                curr = curr - diff;
            }
            else{
                 
                 curr = (curr - diff) + 7;
            }
        }



        answers.push_back(ans);
    }


    for(int i = 0; i < answers.size(); i++)
    {
        cout << answers.at(i) << endl;
    }
}