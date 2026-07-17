/*
================================================================================
Problem Name: Making A Large Island (LeetCode 827)
Difficulty: Hard
Category: Graph Theory / Disjoint Set Union (DSU)
================================================================================

Problem Description:
You are given an n x n binary matrix grid. You are allowed to change at most one 
0 to be a 1. Your goal is to return the size of the largest island in the grid 
after applying this operation.

An island is defined as a 4-directionally connected group of 1s.

--------------------------------------------------------------------------------
Example 1:
Input: grid = [[1, 0], [0, 1]]
Output: 3
Explanation: Change one 0 to 1 (e.g., at (0, 1)) to connect two 1s, resulting 
in an island of size 3.

--------------------------------------------------------------------------------
Example 2:
Input: grid = [[1, 1], [1, 0]]
Output: 4
Explanation: Change the 0 at (1, 1) to 1, creating one island of size 4.

--------------------------------------------------------------------------------
Example 3:
Input: grid = [[1, 1], [1, 1]]
Output: 4
Explanation: No 0s exist to change; the largest island is already of size 4.

--------------------------------------------------------------------------------
Constraints:
- n == grid.length
- n == grid[i].length
- 1 <= n <= 500
- grid[i][j] is either 0 or 1.

================================================================================
*/

#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Disjoint Set Union (DSU) structure using path compression and union by size.
class DisjointSet {
public:
    vector<int> parent, size;
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]); // Path compression
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        DisjointSet ds(n * n);
        
        // Direction vectors for moving 4-directionally (up, down, left, right)
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Step 1: Traverse the grid and union adjacent cells containing 1s
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 0) continue;
                
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        int nodeNo = r * n + c;
                        int adjNodeNo = nr * n + nc;
                        ds.unionBySize(nodeNo, adjNodeNo);
                    }
                }
            }
        }
        
        int mx = 0;
        
        // Step 2: Try converting each 0 to 1 and calculate the potential largest island size
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 1) continue;
                
                unordered_set<int> components;
                for (int i = 0; i < 4; i++) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        components.insert(ds.findUPar(nr * n + nc));
                    }
                }
                
                int sizeTotal = 1; // 1 for the converted cell itself
                for (auto it : components) {
                    sizeTotal += ds.size[it];
                }
                mx = max(mx, sizeTotal);
            }
        }
        
        // Step 3: Handle edge cases where the grid might not have any 0s, or checking if any
        // original island is already larger than the maximum found through a flipped 0.
        for (int cell = 0; cell < n * n; cell++) {
            int r = cell / n;
            int c = cell % n;
            if (grid[r][c] == 1) {
                mx = max(mx, ds.size[ds.findUPar(cell)]);
            }
        }
        
        return mx;
    }
};
