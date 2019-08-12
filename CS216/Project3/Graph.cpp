/* File: Graph.cpp
 * Course: CS216-01x
 * Project: Project 3
 * Purpose: the implementation of member functions for the Graph class.
 *          it represents a undirected graph;
 *          it uses adjacency matrix representation (store 0 if no edge exists; store non-zero value(weight) if an edge exists)
 *
 */
#include <cassert>
#include "Graph.h"
#include <set>
#include <queue>

// constructor
Graph::Graph(int numVertices):adj(Matrix<int>(numVertices, numVertices, 0))
{
}

// to check if an edge exists between v and w
// return true if an edge exists
// otherwise return false
bool Graph::hasEdge(int v, int w)
{
    assert(v>=0 && v < adj.GetSizeX() && w >=0 && w < adj.GetSizeX());
    if (adj(v, w)==0)
        return false;
    return true;
}

// add an edge between v and w (marked with value of edge)
void Graph::addEdge(int v, int w, int edge)
{
    assert(v>=0 && v < adj.GetSizeX() && w >=0 && w < adj.GetSizeX());
    adj(v,w) = edge;
    adj(w,v) = edge;
}

// return marked value from the edge v to w
int Graph::getEdge(int v, int w)
{
    assert(v>=0 && v < adj.GetSizeX() && w >=0 && w < adj.GetSizeX());
    return adj(v,w);
}

// Apply BFS traversal to find the shortest path from the given source s
// store the shortest path distance from the given source s in distance vector
// store the very next vertice to go throgh on the shortest path back to the given source s. For example go_through[w] = v, it means the shortest path from w to s needs to go through v: w->v--...->s
void Graph::BFS(int s, vector<int>& distance, vector<int>& go_through)
{
    //Intialize visited set, queue, and add source to visited
    set<int> visited;
    queue<int> toVisit;
    visited.insert(s);

    distance.at(s) = 0;
    toVisit.push(s);

    int current  = -1;
    // While the Queue isn't empty (Still Nodes to Visit)
    while(toVisit.size() != 0)
    {
        current = toVisit.front(); //Get Thing from front of queue (doesnt remove it)
        toVisit.pop(); // remove thing from front of queue

        for(int i = 0; i < adj.GetSizeY(); i++) // Loop over nodes in adjaceny matrix 
        {
            // if there is an edge between current poistion and i, AND you haven already visited it
            if( adj(current,i) != 0 && visited.count(i) == 0) 
            {
                visited.insert(i); //add i to visited (so you only add this node to queue once)
                toVisit.push(i); //put node (by index) in queue
                distance[i] = distance[current] +1; 
                go_through[i] = current;
                // above, set distance (in vector we passed by reference) for i to distance[i] + 1, since it is adjacent to where we are, it is one away.
            }
        }
    }

}

