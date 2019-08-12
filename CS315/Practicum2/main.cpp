#include <iostream>
#include <vector>

using namespace std;

class union_find
{
    private: vector<int> p, root;
    public: void init(int n)
    {
        p.resize(n);
        root.assign(n,0);
        for(int i=0; i<n; i++)
        {
            p[i] =i;
        }
    }

    int find(int k)
    {
        return k == p[k] ? k : (p[k] = find(p[k]));
    }

    int dstunion(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
            return 0;
        else
        {
            if (root[a] > root[b])
                p[b] =a;
            
            else
            {
                p[a] = p[b];
                if(root[a] == root[b])
                    root[b]++;
            }
            return -1;
        }
    }
};

struct GraphEdge 
{
    int x,y;
}

