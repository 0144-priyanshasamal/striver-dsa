/*
================================================================================
Problem Name: Kruskal's Algorithm for Minimum Spanning Tree (MST)
Difficulty: Medium
Category: Graph Theory / Minimum Spanning Tree / Disjoint Set Union (DSU)
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
#include <algorithm>

using namespace std;

// Disjoint Set (Union-Find) structure for cycle detection and merging components.
class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    // Find the ultimate parent of a node with Path Compression
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Union by Rank
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    // Union by Size
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // We will store all edges in a list/vector as: {weight, {u, v}}
        vector<pair<int, pair<int, int>>> edges;
        
        // Extract all unique undirected edges from the adjacency list
        for (int i = 0; i < V; i++) {
            for (auto neighbor : adj[i]) {
                int adjNode = neighbor[0];
                int wt = neighbor[1];
                int node = i;
                
                // Since it is an undirected graph, each edge is present twice.
                // We add it only once to the edges list (e.g. when node < adjNode)
                if (node < adjNode) {
                    edges.push_back({wt, {node, adjNode}});
                }
            }
        }
        
        // Sort all edges in non-decreasing order of their weights
        // O(E * log(E)) which is equivalent to O(E * log(V)) since E <= V^2
        sort(edges.begin(), edges.end());
        
        DisjointSet ds(V);
        int mstWt = 0;
        
        // Traverse through all sorted edges
        for (auto edge : edges) {
            int wt = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            
            // If the current edge doesn't form a cycle (i.e. u and v belong to different components)
            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt;
                // Union the components
                ds.unionBySize(u, v);
            }
        }
        
        return mstWt;
    }
};
