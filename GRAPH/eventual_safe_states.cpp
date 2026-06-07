/*
================================================================================
Problem Name: Find Eventual Safe States (LeetCode 802 / GFG)
Difficulty: Medium
Category: Graph Theory / DFS / BFS / Kahn's Algorithm / Cycle Detection
================================================================================

Problem Description:
There is a directed graph of n nodes with each node labeled from 0 to n - 1. 
The graph is represented by a 0-indexed 2D integer array 'graph' where graph[i] 
is an integer array of nodes adjacent to node i, meaning there is a directed 
edge from node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe node 
if every possible path starting from that node leads to a terminal node (or 
another safe node).

Return an array containing all the safe nodes of the graph. The answer should 
be sorted in ascending order.

--------------------------------------------------------------------------------
Example 1:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]

Graph Visualization:
  0 ----> 1 ----> 2 ----> 3
  ^               |
  |               v
  +---------------+   (Cycle: 0 -> 1 -> 2 -> 3 -> 0)

  4 ----> 5 (Terminal)
  6 (Terminal/Isolated)

Explanation:
- Nodes 5 and 6 are terminal nodes as they have no outgoing edges.
- Every path starting from nodes 2, 4, 5, and 6 leads to either node 5 or 6.
- Nodes 0, 1, and 3 are part of a cycle (or lead to a cycle), so they are not safe.

--------------------------------------------------------------------------------
Example 2:
Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]

Explanation:
- Only node 4 is a terminal node.
- Every path starting from node 4 leads to node 4.
- All other nodes lead to cycles or can be trapped in loops.

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

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
        // BFS (Kahn's Algorithm on the reversed graph)
        vector<vector<int>> adjrev(V);
        vector<int> indegree(V, 0);
        
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                adjrev[it].push_back(i);
                indegree[i]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> safenodes;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safenodes.push_back(node);
            
            for (auto it : adjrev[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }
        
        sort(safenodes.begin(), safenodes.end());
        return safenodes;
    }
};
