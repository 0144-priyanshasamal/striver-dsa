/*
================================================================================
Problem Name: Prim's Algorithm for Minimum Spanning Tree (MST)
Difficulty: Medium
Category: Graph Theory / Minimum Spanning Tree / Greedy
================================================================================

Problem Description:
Given a weighted, undirected and connected graph of V vertices and E edges. 
The task is to find the sum of weights of the edges of the Minimum Spanning Tree (MST).

An adjacency list adj is used to represent the graph where adj[i] is a list of 
vectors containing two integers where the first integer is the neighbor vertex 
and the second integer is the weight of the edge.

--------------------------------------------------------------------------------
Example 1:
Input:
V = 3, E = 3
adj = {{{1, 5}, {2, 1}}, {{0, 5}, {2, 3}}, {{0, 1}, {1, 3}}}

Graph Visualization:
        (5)
      0 --- 1
       \   /
     (1)\ /(3)
         2

Output: 
4
Explanation: 
The Minimum Spanning Tree (MST) will include edges:
- 0 - 2 with weight 1
- 1 - 2 with weight 3
Total MST weight = 1 + 3 = 4.

--------------------------------------------------------------------------------
Constraints:
- 2 <= V <= 1000
- 1 <= E <= V * (V - 1) / 2
- 1 <= adj[i][j][1] <= 1000
- The graph is connected and has no self-loops or multiple edges.

Expected Time Complexity: O(E * log(V))
Expected Auxiliary Space: O(V + E)

================================================================================
*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // Create a priority queue to store pair of (edge_weight, node)
        // We use min-heap (greater<pair<int, int>>) to always get the minimum weight edge.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Visited array to track if a node is already part of the MST
        vector<int> vis(V, 0);
        
        // Push the starting node (node 0) with weight 0
        // Format in pq: {weight, node}
        pq.push({0, 0});
        
        int sum = 0;
        
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            
            int wt = it.first;
            int node = it.second;
            
            // If the node is already visited (part of MST), skip it
            if (vis[node] == 1) continue;
            
            // Add the edge weight to the MST sum and mark the node as visited
            vis[node] = 1;
            sum += wt;
            
            // Traverse all adjacent nodes of the current node
            for (auto neighbor : adj[node]) {
                int adjNode = neighbor[0];
                int edW = neighbor[1];
                
                // If the adjacent node is not yet included in the MST, push it to the priority queue
                if (!vis[adjNode]) {
                    pq.push({edW, adjNode});
                }
            }
        }
        
        return sum;
    }
};
