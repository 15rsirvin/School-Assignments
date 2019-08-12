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
 * BUGS: Doesn't work for graph with edges of weight 0. (I'm not sure if it's supposed to) Use assert(w>0) to catch this when reading edges and kill program.
 * References: Practicum 3 mst-simple.cpp is the foundation for my code. The union find and graph classes are unchanged.
*/

-------------------------------------------
Algorithm: A Modified Kruskal
-------------------------------------------
	The algorithm I used to solve this problem is a modification of Kruskal's algorithm for finding minimum spanning trees. The program itself can be broken down into a few parts

Finding MST:
	To find the MST with no extra requirments we simply run Kruscal's algorithm. We make a union find object (that is an object with each node in its own set) and put the edges in a vector which we sort by weight. We loop over the entire  vector of edges (starting with those with the lowest weight) and check if they are safe(that is doesn't make a cycle). To see if they are safe, we use the union find object and check if the two nodes the edge we are examining connects are already in the same set (if they are adding this edge will create a cycle). If the nodes aren't in the same set we add this edge to the MST (just its weight) and then put the two nodes in the union find object into the same set. If they are in the same set we do nothing. We then go to the next edge in the vector (the one with the next lowest weight) and repeat until we have added n-1 edges to the MST (which we count as we go). 
O(E log(E) )

Finding Central Node to Minimize Tree Cost:
	Next, we find the node that if all of its edges were forced into a spanning tree, we could get the smallest total cost for said tree. First we make a vector of size n to store the costs of the spanning trees produced by each node. We then go into a for loop, each time making a new union find object and a copy of the original vector edges. We go through each of the edges (in the copy vector) and we find all the edges that  touch the current source node in the loop. We add these weights to the cost of the tree, and then set their weights equal to zero so that kruskals algorithm will add them first since they will have the smallest weights. We then perform the same operation as above adding the smallest safe edges(this will start with the ones we set to zero) until we have  n-1 safe edges creating a spanning tree. (Note: each node can connect up to n-1 other nodes. This means that if the source we are looking at connects to all other nodes, these forced edges will exactly form a spanning tree) The total weight of this tree is added to the vector of costs at the index of the node we are currently looking at. After all of the nodes have been examined, we then do one loop over the vector of costs we just made to find the minimum value. we record this value and its weight to report. If there are multiple nodes with the same cost the first one found is the one we keep. 

Special Case - Printing Adjaceny Matrix of Spanning tree of minimizing vertex:
	If n is less than 20 we want to print the tree we just found for the vertex that has the smallest spanning tree. However, we did not store any of these trees since that would mean potentially storing thousands of matricies in the above loop to only need one. So, now we run Kruskals (modified) algorithm again, making a new  union find object and a 2-d array with filled with "-1"'s. We use the original vector of edges since this will be our last pass and modifiying the data doesn't matter. We use a for loop to go through the edges and find the ones that touch our source node. We add these  weights to the 2-d vector at vect[x][y] and vect[y][x] and then set the weight of the edge equal to zero. Now, we sort the vector of edges by weight, go through them from smallest to greatest and add safe edges to our 2-d array until we have all n-1 edges. Now, we loop through the 2-d array and print " - " for values that are -1, else print the actuall value surounded by spaces. This is formated by rows so as to look like a matrix. 
	
	
-------------------------------------------
Expected Run Time: 
-------------------------------------------
	The most expensive part of the algorithm comes from looping over Kruscals algorithm on each node. So, this gives us a worst case runtime of O(N * E log(E) ). 

-------------------------------------------
Testing Run times:
-------------------------------------------
	These run times were found using the Unix time command. The only value reported is the "real" time. The samples used to test the times all came from the provided test inputs. The number of Edges in each case is E = N+1, so we can apporximate the above as O( N^2 log(N) ). 

	10-Nodes: 0m0.007s 
	100-Nodes: 0m0.008s
	1,000-Nodes: 0m0.249s
	10,000-Nodes: 0m34.024s

This matches up with the theoretical values. From 10 to 100 nodes there is a small change. This is likely becuase the algorithm is not where the bulk of the run time is coming from at these small values. From 100 to 1,000, 10 times as many nodes causes the program to take 311 times longer. From 1,000 to 10,000 10 times as many nodes causes the program to take 136 times longer. Each time increase is more than N^2 but less than N^3 so it is approximatly what we would expect for O(N^2 log(N)).

	

	

	
