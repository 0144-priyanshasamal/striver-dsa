/*
================================================================================
Problem Name: Kahn's Algorithm (BFS-based Topological Sort)
Difficulty: Medium
Category: Graph Theory / BFS / Topological Sorting
================================================================================

Problem Description:
Given a Directed Acyclic Graph (DAG) with V vertices and E edges, find any 
topological sorting of the graph using Kahn's Algorithm (BFS-based approach).

A topological sorting of a directed graph is a linear ordering of its vertices 
such that for every directed edge u -> v, u comes before v in the ordering.

--------------------------------------------------------------------------------
Example 1:
Input:
V = 6
adj = [[], [], [3], [1], [0, 1], [0, 2]]

Graph Visualization:
    5 ----> 0 <---- 4
    |               |
    v               v
    2 ----> 3 ----> 1

Output:
[4, 5, 2, 0, 3, 1] (or any other valid topological order)
Explanation:
- Vertices 4 and 5 have in-degree 0. They are processed first.
- Processing 4 and 5 reduces in-degree of 0, 1, 2.
- A valid topological order is constructed using BFS.

Example 2:
Input:
V = 4
adj = [[], [0], [0], [0]]

Output:
[3, 2, 1, 0]

--------------------------------------------------------------------------------
Constraints:
- 2 <= V <= 10^4
- 1 <= E <= 3 * 10^4
- 0 <= adj[i][j] < V
- The graph is guaranteed to be a Directed Acyclic Graph (DAG).

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to return list containing vertices in Topological order using Kahn's Algorithm.
    vector<int> topoSort(int V, vector<int> adj[]) {
       vector<int> indegree(V, 0);
       for(int i=0; i<V;i++){
        for(auto it:adj[i]){
            indegree[it]++;
        }
       }
       queue<int> q;
       for(int i=0; i<V;i++){
       if(indegree[i]==0){
        q.push(i);
       }
    }


        vector<int> topo;
        while(!q.empty()){
            int node=q.front();
            q.pop();
            topo.push_back(node);
        
        for(auto it: adj[node]){
          indegree[it]--;
          if(indegree[it] == 0) q.push(it);
        }
    }

        return topo;
    }
};
