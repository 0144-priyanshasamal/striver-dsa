/*
================================================================================
Problem Name: Topological Sort (using DFS or BFS/Kahn's Algorithm)
Difficulty: Medium
Category: Graph Theory / Topological Sorting / DAG
================================================================================

Problem Description:
Given a Directed Acyclic Graph (DAG) with V vertices and E edges, find any 
topological sorting of the graph.

A topological sorting of a directed graph is a linear ordering of its vertices 
such that for every directed edge u -> v, u comes before v in the ordering.

Note: There can be multiple topological sorts for a given graph. Any valid 
topological sort will be accepted.

--------------------------------------------------------------------------------
Example 1:
Input:
V = 6
adj = [[], [], [3], [1], [0, 1], [0, 2]]

Graph Visualization:
    5 ----> 0 <---- 4
    |               |
    v               v
    2 ----> 3 ----> 1

Output:
[5, 4, 2, 3, 1, 0]
Explanation:
- Node 5 has no incoming edges. Node 4 has no incoming edges.
- A valid topological order is 5, 4, 2, 3, 1, 0. 
- Another valid order could be 4, 5, 2, 3, 1, 0.

Example 2:
Input:
V = 4
adj = [[], [0], [0], [0]]

Graph Visualization:
    1 ----> 0
    2 ----> 0
    3 ----> 0

Output:
[3, 2, 1, 0]
Explanation:
- Node 3, 2, 1 have no dependency.
- Node 0 depends on all of them.
- Any ordering where 0 comes at the end is valid (e.g. 1, 2, 3, 0).

--------------------------------------------------------------------------------
Constraints:
- 2 <= V <= 10^4
- 1 <= E <= 3 * 10^4
- 0 <= adj[i][j] < V
- The graph is guaranteed to be a Directed Acyclic Graph (DAG).

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper function for DFS-based Topological Sort
    void dfs(int node, vector<int> adj[], vector<int>& vis, stack<int>& st) {
        // TODO: Implement recursive DFS for topological sort.
        // Mark the current node as visited.
        // Recursively visit all unvisited adjacent nodes.
        // After visiting all adjacent nodes, push the current node to the stack.
    }

public:
    // Function to return list containing vertices in Topological order.
    vector<int> topoSort(int V, vector<int> adj[]) {
        // TODO: Initialize visited array and stack.
        // Call the dfs helper function for all unvisited nodes.
        // Pop elements from the stack to construct the topological order and return it.
        
        vector<int> topo;
        return topo;
    }
};
