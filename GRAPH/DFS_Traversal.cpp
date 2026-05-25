/*
================================================================================
Problem Name: DFS Traversal of Graph
Difficulty: Easy
Category: Graph Theory / Depth-First Search (DFS)
================================================================================

Problem Description:
Given a connected undirected/directed graph represented as an adjacency list, perform a 
Depth-First Search (DFS) traversal starting from vertex 0 and return a list containing the 
vertices in the order they are visited.

The graph has V vertices labeled from 0 to V - 1. 

Note: To ensure a deterministic and unique traversal order, when traversing 
the adjacent nodes of a vertex, visit them in the order they appear in the 
adjacency list.

--------------------------------------------------------------------------------
Example 1:
Input: 
V = 5
adj = [[1, 2, 4], [0], [0, 3], [2], [0]]

Graph Visualization:
       0
     / | \
    1  2  4
       |
       3

Output: 
[0, 1, 2, 3, 4]

Explanation: 
- Start from 0. Visit 0 -> dfs = [0]
- Neighbor of 0: 1. Visit 1 -> dfs = [0, 1]
- Neighbor of 1: 0 (already visited). Backtrack to 0.
- Next neighbor of 0: 2. Visit 2 -> dfs = [0, 1, 2]
- Neighbor of 2: 0 (visited), 3. Visit 3 -> dfs = [0, 1, 2, 3]
- Neighbor of 3: 2 (visited). Backtrack to 2, then backtrack to 0.
- Next neighbor of 0: 4. Visit 4 -> dfs = [0, 1, 2, 3, 4]
- DFS Traversal: [0, 1, 2, 3, 4]

--------------------------------------------------------------------------------
Constraints:
- 1 <= V <= 10^4
- 0 <= E <= 2 * 10^4
- adj[i] contains a list of vertices connected to vertex i.
- The graph is guaranteed to be connected.

================================================================================
*/

#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to perform recursive DFS traversal
    void dfsHelper(int node, vector<vector<int>>& adj, vector<int>& vis, vector<int>& dfs) {
        vis[node] = 1;
        dfs.push_back(node);
        
        // Traverse all adjacent vertices of the current node
        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfsHelper(it, adj, vis, dfs);
            }
        }
    }

public:
    // Function to return Depth First Traversal of given graph.
    vector<int> dfsOfGraph(int V, vector<vector<int>>& adj) {
        vector<int> dfs;
        vector<int> vis(V, 0);
        
        // Start DFS traversal from vertex 0 (assuming the graph is 0-indexed and connected)
        dfsHelper(0, adj, vis, dfs);
        
        return dfs;
    }
};
