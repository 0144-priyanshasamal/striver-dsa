/*
================================================================================
Problem Name: Prerequisite Tasks (LeetCode 207: Course Schedule)
Difficulty: Medium
Category: Graph Theory / BFS / Kahn's Algorithm / Cycle Detection
================================================================================

Problem Description:
There are a total of N tasks you have to pick, labeled from 0 to N-1. Some tasks 
may have prerequisites, for example to pick task 0 you have to first finish task 1, 
which is expressed as a pair: [0, 1].

Given the total number of tasks N, a list of prerequisite pairs P, find if it is 
possible to finish all tasks. Return true if possible, else return false.

--------------------------------------------------------------------------------
Example 1:
Input: 
N = 4, P = 3
prerequisites = [[1, 0], [2, 1], [3, 2]]

Output: true
Explanation: 
- To do task 1, you must do task 0.
- To do task 2, you must do task 1.
- To do task 3, you must do task 2.
- A valid order is task 0 -> task 1 -> task 2 -> task 3. It is possible.

Example 2:
Input:
N = 2, P = 2
prerequisites = [[1, 0], [0, 1]]

Output: false
Explanation: 
- To do task 1, you must do task 0.
- To do task 0, you must do task 1.
- This represents a cycle, so it is impossible to finish all tasks.

--------------------------------------------------------------------------------
Constraints:
- 1 <= N <= 10^4
- 1 <= P <= 5 * 10^4
- prerequisites[i].first, prerequisites[i].second < N

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to check if it is possible to finish all tasks.
    bool isPossible(int N, int P, vector<pair<int, int>>& prerequisites) {
        // Build the adjacency list from the prerequisites list.
        vector<vector<int>> adj(N);
        for(auto it : prerequisites){
            adj[it.first].push_back(it.second);
        }
        
        // Calculate in-degree of each node.
        vector<int> indegree(N, 0);
        for(int i = 0; i < N; i++){
            for(int node : adj[i]){
                indegree[node]++;
            }
        }
        
        // Add nodes with in-degree 0 to the queue.
        queue<int> q;
        for(int i = 0; i < N; i++){
            if(indegree[i] == 0){
                q.push(i);
            }
        }
        
        // Process BFS to build topological order.
        vector<int> topo;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            topo.push_back(node);
            for(auto it : adj[node]){
                indegree[it]--;
                if(indegree[it] == 0) {
                    q.push(it);
                }
            }    
        }
        
        // If topological sort contains all nodes, no cycle exists.
        return topo.size() == N;
    }
};
