#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int num, roll;
    int highest = 0;
    
    vector<int> nums(6,0);
  

    cin >> num;

    vector<int> input(num,0);

    for(int i =0; i < num; i++)
    {
        cin >> roll;
        
        nums.at(roll -1) += 1;
        input.at(i) = roll;    
    }

    int index;

    for(int i =0; i < 6; i++)
    {
        if(nums.at(i) == 1)
        {
            if(i+1 > highest)
            {
                highest = i+1;
            }
        }
    }

    for(int i =0; i < num; i++)
    {
        if(input.at(i) == highest)
        {
            index = i +1;
        }
    }

    if (highest != 0)
        cout << index << endl;

    else    
        cout << "none" << endl;
}