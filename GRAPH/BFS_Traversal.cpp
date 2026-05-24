/*
================================================================================
Problem Name: BFS Traversal of Graph
Difficulty: Easy/Medium
Category: Graph Theory / Breadth-First Search
================================================================================

Problem Description:
Given a directed graph represented as an adjacency list, perform a Breadth-First 
Search (BFS) traversal starting from vertex 0 and return a list containing the 
vertices in the order they are visited.

The graph has V vertices labeled from 0 to V - 1. 

Note: To ensure a deterministic and unique traversal order, when traversing 
the adjacent nodes of a vertex, visit them in the order they appear in the 
adjacency list.

--------------------------------------------------------------------------------
Example 1:
Input: 
V = 5
adj = [[1, 2, 3], [], [4], [], []]

Graph Visualization:
       0
     / | \
    1  2  3
       |
       4

Output: 
[0, 1, 2, 3, 4]

Explanation: 
- Start from 0. Nodes directly connected to 0 are 1, 2, and 3.
- Visit 1, 2, and 3 in order.
- Next, visit the neighbors of the already visited vertices in FIFO order:
  - Neighbors of 1: none
  - Neighbors of 2: 4 (visit 4)
  - Neighbors of 3: none
- BFS Traversal: [0, 1, 2, 3, 4]

--------------------------------------------------------------------------------
Example 2:
Input: 
V = 4
adj = [[1, 2], [2], [0, 3], []]

Output: 
[0, 1, 2, 3]

Explanation: 
- Start from 0. Nodes directly connected to 0 are 1 and 2.
- Visit 1 and 2.
- Neighbors of 1: 2 (already visited).
- Neighbors of 2: 0 (already visited) and 3. Visit 3.
- Neighbors of 3: none.
- BFS Traversal: [0, 1, 2, 3]

--------------------------------------------------------------------------------
Constraints:
- 1 <= V <= 10^4
- 0 <= E <= 2 * 10^4
- adj[i] contains a list of vertices connected to vertex i.
- The graph is guaranteed to be connected.

================================================================================
*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfsOfGraph(int V, vector<vector<int>>& adj) {
        vector<int> bfs;
        vector<int> vis(V, 0);
        queue<int> q;
        
        // Start BFS traversal from vertex 0
        q.push(0);
        vis[0] = 1;
        
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            bfs.push_back(node);
            
            // Traverse all adjacent vertices of the current node
            for(auto it : adj[node]) {
                if(!vis[it]) {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
        return bfs;
    }
};
