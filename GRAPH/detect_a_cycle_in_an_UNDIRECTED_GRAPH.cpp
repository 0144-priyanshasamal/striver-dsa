/*
Problem: Detect Cycle in an Undirected Graph
Difficulty: Medium
Topics: Graph, DFS, BFS, Union Find

Description:
Given an undirected graph with V vertices (numbered from 0 to V-1) and E edges, 
represented as an adjacency list adj where adj[i] is a list of vertices adjacent to vertex i. 
Determine if the graph contains at least one cycle. If it contains a cycle, 
return true; otherwise, return false.

Examples:

Example 1:
Input: 
V = 5, E = 5
adj = [[1], [0, 2, 4], [1, 3], [2, 4], [1, 3]]
Visual:
  0 --- 1 --- 2
        |     |
        4 --- 3
Output: true
Explanation: There is a cycle in the graph: 1 -> 2 -> 3 -> 4 -> 1.

Example 2:
Input: 
V = 4, E = 3
adj = [[1], [0, 2], [1, 3], [2]]
Visual:
  0 --- 1 --- 2 --- 3
Output: false
Explanation: The graph is a simple linear path and does not contain any cycles.

Constraints:
* 1 <= V <= 10^5
* 0 <= E <= 10^5
* 0 <= adj[i][j] < V
* The graph is undirected and may consist of multiple connected components.
* There are no self-loops or multiple edges between the same pair of vertices.

Expected Time Complexity: O(V + E)
Expected Auxiliary Space: O(V)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool detect(int src, vector<int> adj[], vector<int>& vis) {
        vis[src] = 1;
        queue<pair<int, int>> q;
        q.push({src, -1});
        
        while (!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();
            
            for (auto adjacentNode : adj[node]) {
                if (!vis[adjacentNode]) {
                    vis[adjacentNode] = 1;
                    q.push({adjacentNode, node});
                }
                else if (adjacentNode != parent) {
                    return true;
                }
            }
        }
        return false;
    }

public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                if (detect(i, adj, vis)) {
                    return true;
                }
            }
        }
        return false;
    }
};
