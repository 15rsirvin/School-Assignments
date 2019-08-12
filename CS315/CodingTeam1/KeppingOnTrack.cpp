#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    int nodes;

    cin >> nodes;

    vector <vector<int> > graph;
    vector<vector<int>> visited;
    vector<int> disconectVales;
    for(int i = 0; i < nodes +1; i++)
    {
        vector<int> subGraph(nodes + 1,0);

        graph.push_back(subGraph);
    }
    visited = graph;

    for(int i = 0; i < nodes + 1; i++)
    {
        int a,b;

        cin >> a >> b;

        graph.at(a).at(b) = 1;
        graph.at(b).at(a) = 1;

    }

    for(int i = 0; i < nodes; i++)
    {
        
    }




    






    
    return 0;
}