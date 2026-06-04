/*
================================================================================
Problem Name: Bipartite Graph
Difficulty: Medium
Category: Graph Theory / BFS / DFS / Graph Coloring
================================================================================

Problem Description:
Given an adjacency list of a graph adj of V vertices. Check whether the graph is 
bipartite or not.

A graph is bipartite if we can split its set of vertices into two independent 
subsets U U and V V such that every edge in the graph connects a vertex in U 
and a vertex in V. In other words, we can color the graph using 2 colors such 
that no two adjacent vertices have the same color.

--------------------------------------------------------------------------------
Example 1:
Input: 
V = 4
adj = [[1, 3], [0, 2], [1, 3], [0, 2]]

Graph Visualization:
   0 --- 1
   |     |
   3 --- 2

Output: true
Explanation: We can color node 0 and 2 with color A, and node 1 and 3 with color B.
No two adjacent nodes have the same color.

--------------------------------------------------------------------------------
Example 2:
Input: 
V = 3
adj = [[1, 2], [0, 2], [0, 1]]

Graph Visualization:
     0
    / \
   1 - 2

Output: false
Explanation: The graph is a triangle (odd length cycle), which cannot be 2-colored.

--------------------------------------------------------------------------------
Constraints:
- 1 <= V <= 10^5
- 0 <= E <= 10^5
- The graph may consist of multiple connected components.
- There are no self-loops or multiple edges.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
bool check(int start,int V,vector<int> adj[],int color[]){
    queue<int> q;
    q.push(start);
    color[start]=0;
    while(!q.empty()){
        int node= q.front();
        q.pop();
        for(auto it: adj[node]){
            // if the adjacent node is not coloured then give it the opposite color of the node
            if(color[it]==-1){
                color[it] = !color[node];
                q.push(it);
            }
            else if(color[it] == color[node]){
                return false;
            }
        }
    }
    return true;
}
public:
    // Function to check if the graph is bipartite.
    bool isBipartite(int V, vector<int> adj[]) {
        // TODO: Implement the bipartite graph check using BFS or DFS.
        // Return true if the graph is bipartite, otherwise return false.
        int color[V];
        for(int i=0;i<V;i++) color[i]=-1;
        for(int i=0;i<V;i++){
            if(color[i] == -1){
                if(check(i,V,adj, color) == false )
                 return false;
            }
        }
        return true;
    }
};
