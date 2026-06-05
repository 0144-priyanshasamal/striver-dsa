/*
================================================================================
Problem Name: Find Eventual Safe States (LeetCode 802 / GFG)
Difficulty: Medium
Category: Graph Theory / DFS / Cycle Detection
================================================================================

Problem Description:
There is a directed graph of n nodes with each node labeled from 0 to n - 1. 
The graph is represented by a 0-indexed 2D integer array graph where graph[i] 
is an integer array of nodes adjacent to node i, meaning there is an edge from 
node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe node 
if every possible path starting from that node leads to a terminal node (or another safe node).

Return an array containing all the safe nodes of the graph. The answer should 
be sorted in ascending order.

--------------------------------------------------------------------------------
Example 1:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]

Example 2:
Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]

--------------------------------------------------------------------------------
Constraints:
- n == graph.length
- 1 <= n <= 10^4
- 0 <= graph[i].length <= n
- 0 <= graph[i][j] <= n - 1
- graph[i] is sorted in a strictly increasing order.
- The graph may contain self-loops.
- The number of edges in the graph is in the range [0, 4 * 10^4].

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper function to perform DFS and detect cycles in a directed graph
    bool dfsCheck(int node, vector<int> adj[], int vis[], int pathVis[], int check[]) {
        vis[node] = 1;
        pathVis[node] = 1;
        check[node] = 0;

        for (auto it : adj[node]) {
            if (!vis[it]) {
                if (dfsCheck(it, adj, vis, pathVis, check) == true)
                    return true;
            }
            else if (pathVis[it]) {
                return true;
            }
        }
        check[node] = 1;
        pathVis[node] = 0;
        return false;
    }

public:
    // Function to find eventual safe nodes (GeeksforGeeks representation)
    vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        vector<int> pathVis(V, 0);
        vector<int> check(V, 0);
        vector<int> safeNodes;
        
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfsCheck(i, adj, vis.data(), pathVis.data(), check.data());
            }
        }
        
        for (int i = 0; i < V; i++) {
            if (check[i] == 1) {
                safeNodes.push_back(i);
            }
        }
        return safeNodes;
    }
};
