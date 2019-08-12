#include <iostream>
#include <vector>
#include <stack>


using namespace std;


int main()
{
    vector<vector<int>> graph;
    vector<vector<int>> visited;

    int a,b;

    cin >> a >> b;

    for (int i =0; i < a; i++)
    {
        string currLine;
        vector <int> subGraph;

        cin >> currLine;



        for(int j =0; j < b; j++)
        {
            if(currLine.at(j) == '.')
            {
                subGraph.push_back(0);
            }
            else
            {
                subGraph.push_back(1);
            }
        }
        graph.push_back(subGraph);

    vector <int> subVisited(b,0);
    visited.push_back(subVisited);
    }

    int count = 0;
    for (int i =0;i < a; i++)
    {
        for (int j =0; j < b; j++)
        {
            if((graph.at(i).at(j)) == 1 && (visited.at(i).at(j) == 0))
            {
                visited.at(i).at(j) = 1;

                int currx = i; int curry = j;
                bool done = false;

                while (!done)
                {
                    done = true;
                    for(int z = currx-1; z <= currx+1; z++)
                    {
                        for(int q = curry-1; q <= curry+1; q++)
                        {
                            
                            if ( (q >= 0 && z >=0) && (q < a && z < b) && (graph.at(z).at(q) == 1) && (visited.at(z).at(q) ==0))
                            {
                                currx = z;
                                curry = q;

                                visited.at(currx).at(curry) = 1;
                                done = false;
                            }
                        }
                    }

                    
                }

                count += 1;
            }
        }
    }

    cout << count << endl;

    

}