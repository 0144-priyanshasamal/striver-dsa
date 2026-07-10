/*
================================================================================
Problem Name: Bellman-Ford Algorithm (Distance from Source)
Difficulty: Medium
Category: Graph Theory / Shortest Path / Dynamic Programming
================================================================================

Problem Description:
Given a weighted, directed graph with V vertices and E edges, and a source vertex S.
Find the shortest distance of all the vertices from the source vertex S. If a 
vertex is not reachable from S, its distance should be represented as 1e8.
If the graph contains a negative weight cycle (i.e. a cycle whose edge weights sum 
to a negative value), return a list containing only -1.

Note:
- The edges are represented as a 2D list/vector where edges[i] = [u, v, wt]
  denotes a directed edge from u to v with weight wt.
- The Bellman-Ford algorithm works on graphs with negative weights, unlike Dijkstra's.

--------------------------------------------------------------------------------
Example 1:
Input:
V = 3, E = 3
edges = [[0, 1, 5], [1, 2, -3], [2, 0, 2]]
S = 0

Graph Visualization:
        (5)
     0 ----> 1
     ^      /
  (2)|     /(-3)
     |    v
     2 <--

Output: 
[0, 5, 2]
Explanation: 
- Distance from 0 to 0 is 0.
- Distance from 0 to 1 is 5 (via 0 -> 1).
- Distance from 0 to 2 is 2 (via 0 -> 1 -> 2, weight = 5 + (-3) = 2).

--------------------------------------------------------------------------------
Example 2:
Input:
V = 3, E = 3
edges = [[0, 1, 2], [1, 2, -5], [2, 0, 1]]
S = 0

Graph Visualization:
        (2)
     0 ----> 1
     ^      /
  (1)|     /(-5)
     |    v
     2 <--

Output: 
[-1]
Explanation: 
The graph contains a negative weight cycle:
0 -> 1 -> 2 -> 0 has total weight 2 + (-5) + 1 = -2 < 0.
Thus, we return [-1].

--------------------------------------------------------------------------------
Constraints:
- 1 <= V <= 500
- 1 <= E <= V*(V-1)
- -10^6 <= wt <= 10^6
- 0 <= S < V

Expected Time Complexity: O(V * E)
Expected Auxiliary Space: O(V)

================================================================================
*/

#include <vector>

using namespace std;

class Solution {
public:
    /*
     * Function to implement Bellman-Ford Algorithm
     * V: number of vertices
     * edges: vector of vectors where each element is [u, v, wt] representing edge u -> v with weight wt
     * S: source vertex
     */
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        // Initialize distance array with 1e8 as infinity
        vector<int> dist(V, 1e8);
        
        // Distance from source to source is 0
        dist[S] = 0;

        // Relax all edges V - 1 times
        for (int i = 0; i < V - 1; i++) {
            for (auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];

                // If u is reachable and path via u is shorter, update dist[v]
                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Perform V-th relaxation to check for negative weight cycles
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            // If we can still relax the edge, then there is a negative cycle
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return {-1};
            }
        }

        return dist;
    }
};
