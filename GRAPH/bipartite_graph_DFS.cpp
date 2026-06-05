/*
================================================================================
Problem Name: Bipartite Graph (using DFS)
Difficulty: Medium
Category: Graph Theory / DFS / Graph Coloring
================================================================================

Problem Description:
Given an adjacency list of a graph adj of V vertices. Check whether the graph is 
bipartite or not.

A graph is bipartite if we can split its set of vertices into two independent 
subsets U and V such that every edge in the graph connects a vertex in U 
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
    // Helper function to check if the graph is bipartite using DFS
    bool dfs(int node, int col,int color[],vector<int> adj[]) {
        // TODO: Implement the DFS coloring check.
        // Assign the current color 'col' to 'node', then recursively check neighbors.
        color[node]= col;
        for(auto it: adj[node]){
            if(color[it] == -1){
                if(dfs(it,!col,color,adj)  == false) return false;
            }
            else if(color[it]==col){
                return false;
            }
        }
        return true;
    }

public:
    // Function to check if the graph is bipartite.
    bool isBipartite(int V, vector<int> adj[]) {
        // TODO: Initialize color array and check all components using checkDFS.
        vector<int> color(V, -1);
        for(int i=0;i<V;i++){
            if(color[i]==-1){
                if(dfs(i,0,color.data(),adj) == false) return false;
            }
        }
        return true;
    }
};

