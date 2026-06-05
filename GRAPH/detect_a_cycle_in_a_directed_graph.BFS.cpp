/*
================================================================================
Problem Name: Detect Cycle in a Directed Graph (using BFS - Kahn's Algorithm)
Difficulty: Medium
Category: Graph Theory / BFS / Cycle Detection
================================================================================

Problem Description:
Given a directed graph with V vertices and E edges, check whether it contains any 
cycle or not using BFS (Kahn's Algorithm).

Recall that Kahn's Algorithm (BFS-based Topological Sort) can only find a 
topological sort of a Directed Acyclic Graph (DAG). If a cycle exists, 
the topological sort will not be able to include all V vertices because 
some vertices will never have their in-degree reduced to 0.

Thus, if the count of vertices in the topological sort is less than V, 
the graph contains a cycle (return true). Otherwise, it does not (return false).

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
Explanation: Node 3 has a self-loop, which forms a cycle.

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
public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        // TODO: Implement BFS-based cycle detection (Kahn's Algorithm).
        // 1. Compute in-degrees of all vertices.
        // 2. Queue all vertices with in-degree 0.
        // 3. Keep a count of visited nodes.
        // 4. Perform BFS, reducing neighbor in-degrees and queueing when they reach 0.
        // 5. If count of visited nodes is equal to V, return false (no cycle).
        // 6. Otherwise, return true (cycle exists).
        
        return false;
    }
};
