/*
================================================================================
Problem Name: Detect Cycle in a Directed Graph (using DFS)
Difficulty: Medium
Category: Graph Theory / DFS / Cycle Detection
================================================================================

Problem Description:
Given a directed graph with V vertices and E edges, check whether it contains any 
cycle or not. A cycle in a directed graph exists if there is a path that starts 
from a vertex and ends at the same vertex.

The graph is represented as an adjacency list adj, where adj[i] is a list of 
vertices adjacent to vertex i.

--------------------------------------------------------------------------------
Example 1:
Input: 
V = 4
adj = [[1], [2], [3], [3]]

Graph Visualization:
   0 ---> 1 ---> 2 ---> 3 <---+
                        |     | (self-loop / back edge)
                        +-----+

Output: true
Explanation: Node 3 has a self-loop (an edge pointing to itself), which forms a cycle.

--------------------------------------------------------------------------------
Example 2:
Input: 
V = 4
adj = [[1], [2], [3], []]

Graph Visualization:
   0 ---> 1 ---> 2 ---> 3

Output: false
Explanation: The graph is a simple linear path without any cycles.

--------------------------------------------------------------------------------
Constraints:
- 1 <= V <= 10^5
- 0 <= E <= 10^5
- 0 <= adj[i][j] < V
- The graph may consist of multiple disconnected components.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper function to perform DFS and detect cycles in a directed graph
    bool dfsCheck(int node, vector<int> adj[], int vis[], int pathVis[]) {
        // TODO: Implement DFS cycle detection.
        // Mark the current node as visited in both 'vis' and 'pathVis'.
        // Recursively visit all adjacent nodes. If an adjacent node is not visited, 
        // recursively check it. If an adjacent node is already on the current 
        // recursion path ('pathVis' is 1), then a cycle has been detected.
        // Before backtracking, unmark the node from the current recursion path ('pathVis').
        vis[node]=1;
        pathVis[node]=1;

        for(auto it: adj[node]){
            if(!vis[it]){
                if(dfsCheck(it,adj,vis,pathVis) == true)
                return true;
            }
            else if(pathVis[it]){
                return true;
            }
        }
        
        pathVis[node]=0;
        return false;
    }

public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        // TODO: Initialize visited and path-visited arrays, and check all components.
        int vis[V] = {0};
        int pathVis[V] ={0};
        for(int i = 0; i<V;i++){
           if(!vis[i]){
               if(dfsCheck(i, adj,vis,pathVis) == true) return true;
           }
        }
        return false;
    }
};
