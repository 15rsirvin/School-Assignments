#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
    
    int s;

    cin >> s;

    vector< set<int> > cards;
    bool isTie = false;

    for (int i =0; i < s; i++)
    {
        set<int> nums;

        for(int j =0; j < 25; j++)
        {
            int temp;
            cin >> temp;

            nums.insert(temp);
        }
        cards.push_back(nums);
    }

    for (int i = 0; i < cards.size(); i++)
    {
        for (int j = i+1; j < cards.size(); j++)
        {
            for (auto it = cards.at(i).begin(); it != cards.at(i).end() ; it++)
            {
                if(cards.at(j).count(*it) != 0)
                {
                    cout << (i +1) << " " << (j +1) << " ";
                    isTie = true;
                    break;
                }
            }
        }
    }

    if(!isTie)
    {
        cout << "no ties" << endl;
    }


    return 0;
}