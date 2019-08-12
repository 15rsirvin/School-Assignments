/*
 * NAME: mst-simple.cpp
 * synopsis: ./a.out < test1.txt    
 * Compilation: g++ mst-simple.cpp
 * Class: cs315003s18
 * Description: Takes as input two number n and m followed by m triplet integers where  each the first two numbers in the triplet are the nodes the edge connects too and the third value is the weight.
 *              This program then returns the total cost of the weights, the cost of weights in the MST and the COST of weights not in the MST. it also prints out the weighted graph in matrix form.
 * AUTHOR: Robert Irvin
 * SID: 8785
 * DATE: November 2018
 * RunningTime: O(log n)
 * BUGS:
 * References:
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

int main(){
    freopen("mst-simple.in", "r",stdin);
    while(1)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        if(!n && !m)
            break;
        int res = 0;
        vector<GraphEdge> e(m);
        for (int i=0; i<m; i++)
        {
            e[i].readinput();
            res += e[i].w;
        }   
        sort(e.begin(), e.end());
        union_find uf;
        uf.init(n);
        int cnt = 0, mst =0;
        for( int i=0; cnt <n-1 && i<m; i++)
        {
            if(uf.dstunion(e[i].x, e[i].y))
            {
                res -= e[i].w;
                cnt++;
                mst += e[i].w;
            }
        }
        //printf("%d\n", res);
        // My Code
        cout << res + mst << " <---TOTAL COST OF EDGES" << endl;
        cout << res << " <---COST OF EDGES NOT IN MST" << endl;
        cout << mst << " <---COST(MST)" << endl;

        vector <vector<int>>  tot;
        for(int i = 0; i < n; i++)
        {
            vector <int> temp;
            for(int j = 0; j <n; j++)
            {
                temp.push_back(0);
            }

            tot.push_back(temp);
        }
        for(int i = 0; i < m; i++)
        {
            int x = e[i].x;
            int y = e[i].y;
            int w = e[i].w;

            tot.at(x).at(y) = w;
            tot.at(y).at(x) = w;
        }

        for (int i = 0; i < n; i++)
        {
            cout << "  ";
            for( int j = 0; j < n; j++)
            {
                int ans = tot.at(i).at(j);
                if(ans == 0)
                {
                    cout << "- ";
                }
                else
                {
                    cout << ans << " ";
                }
            }
            cout << "\n";
        }
    }
    return 0;
}