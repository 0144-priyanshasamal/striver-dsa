/*
Problem: Shortest Path in Undirected Graph having Unit Distance (Cyclic Graph)
Difficulty: Medium
Topics: Graph, BFS, Shortest Path

Description:
Given an undirected graph with V vertices (numbered from 0 to V-1) and E edges, and a source vertex src. 
Find the shortest path from the source vertex src to all other vertices. 
The weight of each edge in the graph is 1 (unit distance). 
If a vertex is unreachable from the source vertex, the shortest distance to it should be -1.

Examples:

Example 1:
Input:
V = 9, E = 10
edges = [[0, 1], [0, 3], [3, 4], [4, 5], [5, 6], [1, 2], [2, 6], [6, 7], [7, 8], [6, 8]]
src = 0
Output: 
[0, 1, 2, 1, 2, 3, 3, 4, 4]
Explanation: 
The shortest path from 0 to 0 is 0.
The shortest path from 0 to 1 is 1.
The shortest path from 0 to 2 is 2, and so on.

Example 2:
Input:
V = 4, E = 2
edges = [[1, 3], [3, 0]]
src = 3
Output: 
[1, -1, -1, 0]
Explanation: 
Vertex 1 is at distance 1 from 3.
Vertex 2 is unreachable from 3, so its distance is -1.

Constraints:
* 1 <= V <= 10^5
* 0 <= E <= 10^5
* 0 <= src < V
* 0 <= edges[i][j] < V

Expected Time Complexity: O(V + E)
Expected Auxiliary Space: O(V)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the shortest path from source vertex to all other vertices.
    vector<int> shortestPath(vector<vector<int>>& edges, int N, int M, int src) {
        // Build the adjacency list from the given edges.
        vector<vector<int>> adj(N);
        for(auto &it : edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        
        // Initialize distance vector
        vector<int> dist(N, 1e9);
        dist[src] = 0;
        
        // Perform BFS starting from the source vertex:
        queue<int> q;
        q.push(src);
        while(!q.empty()){
            int node = q.front();
            q.pop();
            for(auto it : adj[node]){
                if(dist[node] + 1 < dist[it]){
                    dist[it] = 1 + dist[node];
                    q.push(it);
                }
            }
        }
        
        // Update unreachable nodes to -1 in-place
        for(int i = 0; i < N; i++){
            if(dist[i] == 1e9){
                dist[i] = -1;
            }
        }
        
        return dist;
    }
};
