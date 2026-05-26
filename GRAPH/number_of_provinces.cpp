/*
================================================================================
Problem Name: Number of Provinces (LeetCode 547)
Difficulty: Medium
Category: Graph Theory / Connected Components (DFS / BFS / Disjoint Set)
================================================================================

Problem Description:
There are n cities. Some of them are connected, while some are not. If city a is 
connected directly with city b, and city b is connected directly with city c, 
then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other 
cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the 
i-th city and the j-th city are directly connected, and isConnected[i][j] = 0 
otherwise.

Return the total number of provinces.

--------------------------------------------------------------------------------
Example 1:
Input: isConnected = [[1, 1, 0], 
                      [1, 1, 0], 
                      [0, 0, 1]]
Output: 2

Explanation:
- City 0 and City 1 are connected, forming the 1st province.
- City 2 is in its own province (3rd city is isolated), forming the 2nd province.
- Total provinces = 2.

--------------------------------------------------------------------------------
Example 2:
Input: isConnected = [[1, 0, 0], 
                      [0, 1, 0], 
                      [0, 0, 1]]
Output: 3

Explanation:
- All three cities are isolated, each forming a separate province.
- Total provinces = 3.

--------------------------------------------------------------------------------
Constraints:
- 1 <= n <= 200
- isConnected[i][j] is 1 or 0.
- isConnected[i][i] == 1
- isConnected[i][j] == isConnected[j][i]

================================================================================
*/

#include <vector>

using namespace std;

class Solution {

    private:
      void dfs(int node,vector<int> adjLs[],vector<int>& vis){
        vis[node] = 1;
        for(auto it:adjLs[node]){
            if(!vis[it]){
                dfs(it,adjLs,vis);
            }
        }
      }
    public:


    int findCircleNum(vector<vector<int>>& isConnected) {
        int v=isConnected.size();
        vector<int> adjLs[v];
        //change adjacency matrix to list
        for(int i = 0;i<v;i++){
            for(int j=0;j<v;j++){
                if(isConnected[i][j] == 1 && i!=j){
                    adjLs[i].push_back(j);
                    adjLs[j].push_back(i);
                }
            }
        }
        vector<int> vis(v, 0);
        int cnt=0;
        for(int i=0;i<v;i++){
            if(!vis[i]){
                cnt++;
                dfs(i,adjLs,vis);
            }
        }
        return cnt;
    }
};














