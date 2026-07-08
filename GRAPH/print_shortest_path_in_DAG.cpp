/*
================================================================================
Problem Name: Print Shortest Path in Weighted Undirected Graph (Dijkstra's Algorithm)
Difficulty: Medium
Category: Graph Theory / Shortest Path / Greedy
================================================================================

Problem Description:
You are given a weighted undirected graph having n vertices numbered from 1 to n 
and m edges. Find the shortest path between vertex 1 and vertex n. 

If there exists multiple paths with the minimum path weight, return any of them. 
If no path exists from vertex 1 to vertex n, return a vector containing [-1].

Input:
- n: An integer representing the number of vertices.
- m: An integer representing the number of edges.
- edges: A 2D integer vector where edges[i] = [u, v, w] denotes a weighted 
  undirected edge between u and v with weight w.

Output:
Return a vector of integers representing the shortest path from vertex 1 to vertex n.
The first element of the returned vector must be the total weight of the shortest path,
followed by the sequence of nodes along the path (starting at 1 and ending at n).

--------------------------------------------------------------------------------
Example 1:
Input:
n = 5, m = 6
edges = [[1, 2, 2], [2, 5, 5], [1, 4, 1], [4, 3, 3], [3, 5, 1], [1, 3, 4]]

Output:
[5, 1, 4, 3, 5]

Explanation:
The path 1 -> 4 -> 3 -> 5 has a total weight of 1 + 3 + 1 = 5, which is the 
minimum possible weight path from 1 to 5. The output vector has the weight (5) 
as the first element, followed by the nodes [1, 4, 3, 5].

--------------------------------------------------------------------------------
Example 2:
Input:
n = 4, m = 3
edges = [[1, 2, 3], [1, 3, 10], [2, 3, 4]]

Output:
[7, 1, 2, 3]

Explanation:
The path 1 -> 2 -> 3 has a total weight of 3 + 4 = 7, which is shorter than 
the direct edge 1 -> 3 (weight 10).

--------------------------------------------------------------------------------
Example 3:
Input:
n = 3, m = 1
edges = [[1, 2, 5]]

Output:
[-1]

Explanation:
There is no path connecting vertex 1 to vertex 3.

--------------------------------------------------------------------------------
Constraints:
- 2 <= n <= 10^5
- 1 <= m <= 10^5
- 1 <= u, v <= n
- 1 <= w <= 10^5
- The graph does not contain self-loops or multiple edges.

Expected Time Complexity: O(m * log(n))
Expected Auxiliary Space: O(n + m)

================================================================================
*/

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {
        // Create adjacency list. Graph is 1-indexed.
        vector<pair<int, int>> adj[n + 1];
        for (auto& it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        // Min-heap: stores pairs of {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // dist[i] stores the shortest distance from 1 to i
        vector<int> dist(n + 1, 1e9);
        
        // parent[i] stores the parent node of i in the shortest path tree
        vector<int> parent(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        
        dist[1] = 0;
        pq.push({0, 1});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            
            if (d > dist[node]) continue;
            
            for (auto& edge : adj[node]) {
                int neighbor = edge.first;
                int weight = edge.second;
                
                if (d + weight < dist[neighbor]) {
                    dist[neighbor] = d + weight;
                    parent[neighbor] = node;
                    pq.push({dist[neighbor], neighbor});
                }
            }
        }
        
        // If node n is unreachable, return {-1}
        if (dist[n] == 1e9) {
            return {-1};
        }
        
        // Reconstruct the path from node n to node 1
        vector<int> path;
        int node = n;
        while (parent[node] != node) {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(1);
        
        // Reverse the path to get it from 1 to n
        reverse(path.begin(), path.end());
        
        // The first element of the returned list must be the path weight,
        // followed by the nodes on the path.
        vector<int> result;
        result.push_back(dist[n]);
        result.insert(result.end(), path.begin(), path.end());
        
        return result;
    }
};
