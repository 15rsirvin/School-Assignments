#include<iostream>
#include<set>
#include <vector>

using namespace std;

int main()
{
    int num_times;

    int ans = 0;

    cin >> num_times;

    vector<int> answers;

    for (int i =0; i < num_times; i++)
    {
        int n;

        cin >> n;

        set<string> cities;

        for (int j = 0; j < n; j++)
        {
            string city;

            cin >> city;

            cities.insert(city);

        }

        answers.push_back(cities.size());
    }

    for(int i = 0; i < answers.size(); i++)
    {
        cout << answers.at(i) << endl;
    }
}