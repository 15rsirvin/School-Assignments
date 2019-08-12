/*
 * NAME: pa2785.cpp
 * synopsis: ./a.out < test1.txt    
 * Compilation: g++ pa2785.cpp
 * Class: cs315003s18
 * Description: Takes as input two number n and m followed by m triplet integers (3 integers seperated by spaces) that represent an edge. The first two numbers are the nodes the edge connects, and the last is the
 *              weight. This program finds the MST of the graph using kruskals algorithm, and stores its total cost. Using a modified kruskals algorithm, the program then forces all the edges connected to one node to 
 *              be in the MST and finds finds the total cost of MST with this "hub" node. This is done for all nodes so as to find which node as the hub produces the tree that costs the least. The first line of the output
 *              is the Total weight of all edges given. The second line of the output is the total cost of the MST with no restrictions. The third line is the Node picked to be the "hub" (that produces the smallest MST
 *              when its edges are forced into the spanning tree). The fourth line is the cost of the spanning tree of the picked "hub" that is minimized for cost but still contains all edges attached to the hub.
 * AUTHOR: Robert Irvin
 * SID: 8785
 * DATE: November 2018
 * RunningTime: O(N * E  * log(N))
 * BUGS: 
 * References: Practicum 3 mst-simple.cpp is the foundation for my code. The union find and graph classes are unchanged.
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>

using namespace std;

class union_find
{
    private: vector<int> p, root;
    public: void init (int n){
        p.resize(n);
        root.assign(n,0);
        for( int i=0; i<n; i++)
        {
            p[i] = i;
        }
    }
    int find(int k){
        return k == p[k] ? k : (p[k] = find(p[k]));
    }
    int dstunion (int a , int b)
    {
        a = find(a);
        b = find(b);
        if ( a == b)
        {
            return 0;
        }
        if ( root[a] > root[b])
        {
            p[b] = a;
        }
        else
        {
            p[a] = b;
            if( root[a] == root[b])
                root[b]++;
        }
        return 1;

    }
};

struct GraphEdge{
    int x, y , w;
    void readinput(){
        scanf("%d%d%d", &x, &y, &w);
    }
    bool operator< (const GraphEdge &e) const{
        return w < e.w;
    }
};

int main()
{
    while(1)
    {
        int n,m;
        scanf("%d%d", &n, &m);
        if(!n && !m)
            break;
        double res = 0;
        vector<GraphEdge> e(m);
        for(int i =0; i <m; i++)
        {
            e[i].readinput();
            res += e[i].w;
        }
        sort(e.begin(), e.end());
        union_find uf;
        uf.init(n);
        int cnt =0;
        double mst =0;
        for( int i=0; cnt <n-1 && i<m; i++)
        {
            if(uf.dstunion(e[i].x, e[i].y))
            {
                res -= e[i].w;
                cnt++;
                mst += e[i].w;
            }
        }

        // New Code: everything above was provided in Practicum

        // 1.) Make a vector to hold cost of choosing each source and forcing all of its edges into spanning tree
        vector<double> costOfSources;
        costOfSources.resize(n);
        costOfSources.assign(n,0);

        // 2.) loop over changing source nodes for the "hub"
        for(int i =0; i<n; i++)
        {
            double sst = 0; // cost of spanning tree
            vector<GraphEdge> eCopy = e; // make copy of e so that we can alter values

            // 3.) Go through edges. If it touches the current source, add the weight to sst and then set it to zero in eCopy. In effect this forces algorithm to add it to the "mst"
            for(int j =0; j<m; j++)
            {
                if(eCopy[j].x == i || eCopy[j].y == i)
                {
                    sst += eCopy[j].w;
                    eCopy[j].w = 0;
                }
            }

            // 4.) make a new union find object, reset cnt of edges in mst to zero, sort the copy of e. 
            union_find uf2;
            uf2.init(n);
            cnt = 0;
            sort(eCopy.begin(),eCopy.end()); 

            // 5.) Perform kruskals algorithm, adding safe edges to sst. (note: those forced to zero are added first)
            for( int i=0; cnt <n-1 && i<m; i++)
            {
                if(uf2.dstunion(eCopy[i].x, eCopy[i].y))// if safe
                {
                    cnt++;
                    sst += eCopy[i].w;
                }
            }

            // 6.) Set the cost of the MST for this source (i.e. at index i in the vector)
            costOfSources.at(i) = sst;
        }

        // 7.) Find which node gave the tree with the least cost
        int nodeChoice = 0;
        double smallestCost = costOfSources.at(0); // set smallest to first thing in vector
        for(int i = 1; i < n; i++) // loop over all elements except 0
        {
            if(costOfSources.at(i) < smallestCost) // if smaller is found, update
            {
                smallestCost = costOfSources.at(i);
                nodeChoice = i;
            }
        }

        // 8.) Print results for non-special case 
        cout << res + mst << endl;
        cout << mst << endl;
        cout << nodeChoice << endl;
        cout << smallestCost << endl;

        // 9.)  SPECIAL CASE: If #nodes < 20, print the adjacency matrix of Least expensive netrwork for selected Node.
        if(n <= 20 )
        {
            // 10) Create a 2-d vector of size n x n
            vector <vector <double> > adjMatrix;
            for (int i =0; i < n; i++)
            {
                vector<double> row;
                for(int j =0; j < n; j++)
                {
                    row.push_back(-1); // Note: '-' will represent no connection in final matrix
                }
                adjMatrix.push_back(row);
            }

            // 11) Re-Find Network for Selected Node, adding selected edges to adjMatrix
            for(int j =0; j<m; j++)
            {
                if(e[j].x == nodeChoice || e[j].y == nodeChoice)
                {
                    adjMatrix.at(e[j].x).at(e[j].y) = e[j].w;
                    adjMatrix.at(e[j].y).at(e[j].x) = e[j].w;
                    e[j].w = 0;
                }
            }
            sort(e.begin(),e.end());
            union_find uf2;
            uf2.init(n);
            cnt = 0;
            for( int i=0; cnt <n-1 && i<m; i++)
            {
                if(uf2.dstunion(e[i].x, e[i].y))
                {
                    cnt++;
                    if(e[i].w != 0)
                    {
                        adjMatrix.at(e[i].x).at(e[i].y) = e[i].w;
                        adjMatrix.at(e[i].y).at(e[i].x) = e[i].w;
                    }
                }
            }

            //12.) Print adjMatrix
            for(int i = 0; i<n ; i++)
            {
                for (int j =0; j < n; j++)
                {   
                    if(adjMatrix[i][j] == -1)
                        cout <<" - ";
                    else
                        cout << " " << adjMatrix[i][j] << " ";
                }
                cout << "\n";
            }
        }
    }// End of while loop (program will run until n = m = 0 in input)
    return 0;
}// End of Main