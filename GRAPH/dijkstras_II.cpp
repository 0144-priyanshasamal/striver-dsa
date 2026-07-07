/*
================================================================================
Problem Name: Dijkstra's Shortest Path Algorithm using Set
Difficulty: Medium
Category: Graph Theory / Shortest Path / Greedy
================================================================================

Problem Description:
Given a weighted, undirected and connected graph of V vertices and an adjacency list 
adj where adj[i] is a list of vectors containing two integers where the first integer 
is the neighbor vertex and the second integer is the weight of the edge. 
Given a source vertex S, find the shortest distance of all the vertices from the 
source vertex S.

Using std::set allows us to erase existing (older) paths when a shorter path is found. 
This keeps the container size bounded by V, unlike a priority queue where multiple 
outdated paths for the same node can exist simultaneously.

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
#include <set>

using namespace std;

class Solution {
public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex S.
    // adj[i] contains vector of size 2 where:
    // adj[i][0] = neighbor node
    // adj[i][1] = weight of the edge
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        // Create a set for storing the nodes as a pair of (dist, node)
        // Set automatically keeps the elements sorted in ascending order.
        set<pair<int, int>> st;

        // Initialize distance array with a large value representing infinity (1e9)
        vector<int> dist(V, 1e9);

        // Distance of source to itself is 0
        dist[S] = 0;
        
        // Insert the source node into the set with distance 0
        st.insert({0, S});

        while (!st.empty()) {
            // The first element in the set is always the one with the minimum distance
            auto it = *(st.begin());
            int d = it.first;
            int node = it.second;
            st.erase(st.begin());

            // Traverse all adjacent neighbors of the current node
            for (auto neighbor : adj[node]) {
                int adjNode = neighbor[0];
                int edgeWeight = neighbor[1];

                // Relaxation step: Check if a shorter path to adjNode is found
                if (d + edgeWeight < dist[adjNode]) {
                    
                    // If the node was previously reached (i.e. distance is not infinity),
                    // we can erase the older path representation from the set to save space
                    // and avoid redundant operations.
                    if (dist[adjNode] != 1e9) {
                        st.erase({dist[adjNode], adjNode});
                    }

                    // Update the shortest distance
                    dist[adjNode] = d + edgeWeight;
                    
                    // Insert the updated path representation into the set
                    st.insert({dist[adjNode], adjNode});
                }
            }
        }
        return dist;
    }
};
