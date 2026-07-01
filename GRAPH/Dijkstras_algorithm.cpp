/*
================================================================================
Problem Name: Dijkstra's Shortest Path Algorithm using Priority Queue
Difficulty: Medium
Category: Graph Theory / Shortest Path / Greedy
================================================================================

Problem Description:
Given a weighted, undirected and connected graph of V vertices and an adjacency list 
adj where adj[i] is a list of vectors containing two integers where the first integer 
is the neighbor vertex and the second integer is the weight of the edge. 
Given a source vertex S, find the shortest distance of all the vertices from the 
source vertex S.

--------------------------------------------------------------------------------
Example 1:
Input:
V = 3, E = 3
adj = {{{1, 1}, {2, 6}}, {{2, 3}, {0, 1}}, {{1, 3}, {0, 6}}}
S = 2

Graph Visualization:
       (1)
     0 --- 1
      \   /
    (6)\ /(3)
        2

Output: 
[4, 3, 0]
Explanation: 
The source vertex is S = 2.
- The distance from 2 to 2 is 0.
- The distance from 2 to 1 is 3 (via direct edge 2 -> 1).
- The distance from 2 to 0 is 4 (via path 2 -> 1 -> 0, weight = 3 + 1 = 4).
  Note that direct edge 2 -> 0 has weight 6, but path 2 -> 1 -> 0 is shorter.

--------------------------------------------------------------------------------
Example 2:
Input:
V = 2, E = 1
adj = {{{1, 9}}, {{0, 9}}}
S = 0

Graph Visualization:
       (9)
     0 --- 1

Output: 
[0, 9]
Explanation: 
The source vertex S = 0.
- Distance from 0 to 0 is 0.
- Distance from 0 to 1 is 9.

--------------------------------------------------------------------------------
Constraints:
- 1 <= V <= 10^5
- 0 <= E <= 10^5
- 0 <= S < V
- Edge weights are non-negative (Dijkstra's algorithm does not support negative weight cycles/edges).

Expected Time Complexity: O(E * log(V))
Expected Auxiliary Space: O(V + E)

================================================================================
*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex S.
    // adj[i] contains vector of size 2 where:
    // adj[i][0] = neighbor node
    // adj[i][1] = weight of the edge
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        // Create a priority queue for storing the nodes as a pair of (dist, node)
        // We use greater<pair<int, int>> to make it a min-heap, which retrieves
        // the node with the minimum distance at the top.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Initialize distance array with a large value representing infinity (1e9)
        vector<int> dist(V, 1e9);

        // Distance of source to itself is 0
        dist[S] = 0;
        
        // Push the source node into the priority queue with distance 0
        pq.push({0, S});

        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Optimization: If the extracted distance is larger than the 
            // current minimum distance recorded for this node, we skip it.
            // This prevents redundant processing of stale path entries.
            if (d > dist[node]) continue;

            // Traverse all adjacent neighbors of the current node
            for (auto it : adj[node]) {
                int adjNode = it[0];
                int edgeWeight = it[1];

                // Relaxation step: Check if a shorter path to adjNode is found
                if (d + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = d + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
};
