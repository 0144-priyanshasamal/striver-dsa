/*
================================================================================
Problem Name: Number of Enclaves (LeetCode 1020 / GFG)
Difficulty: Medium
Category: Graph Theory / Matrix / Depth-First Search (DFS) / Breadth-First Search (BFS)
================================================================================

Problem Description:
You are given an m x n binary matrix 'grid', where 0 represents a boundary cell or 
water cell, and 1 represents a land cell.

A move consists of walking from one land cell to another adjacent (4-directionally) 
land cell or walking off the boundary of the grid.

Return the number of land cells in 'grid' for which we cannot walk off the boundary 
of the grid in any number of moves.

--------------------------------------------------------------------------------
Example 1:
Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Output: 3
Explanation: 
- There are three 1s that are enclosed by 0s (at (1,2), (2,1), (2,2)).
- The 1 at (1,0) is on the boundary. We can walk off the boundary from it.
- Therefore, we return 3.

Example 2:
Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 0
Explanation: 
- All 1s are either on the boundary or can reach the boundary.

--------------------------------------------------------------------------------
Complexity:
- Time Complexity: O(N * M)
- Space Complexity: O(N * M)
================================================================================
*/

#include <vector>
#include <queue>
#include <utility>

using namespace std;

// =============================================================================
// Implementation 1: Depth-First Search (DFS) Approach
// =============================================================================
class SolutionDFS {
private:
    void dfs(int r, int c, vector<vector<int>>& grid, vector<vector<int>>& vis) {
        vis[r][c] = 1;
        int n = grid.size();
        int m = grid[0].size();
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};
        for (int i = 0; i < 4; i++) {
            int nRow = r + delRow[i];
            int nCol = c + delCol[i];
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && grid[nRow][nCol] == 1 && !vis[nRow][nCol]) {
                dfs(nRow, nCol, grid, vis);
            }
        }
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        
        // Traverse boundary cells
        for (int j = 0; j < m; j++) {
            // first row
            if (grid[0][j] == 1 && !vis[0][j]) {
                dfs(0, j, grid, vis);
            }
            // last row
            if (grid[n - 1][j] == 1 && !vis[n - 1][j]) {
                dfs(n - 1, j, grid, vis);
            }
        }
        for (int i = 0; i < n; i++) {
            // first column
            if (grid[i][0] == 1 && !vis[i][0]) {
                dfs(i, 0, grid, vis);
            }
            // last column
            if (grid[i][m - 1] == 1 && !vis[i][m - 1]) {
                dfs(i, m - 1, grid, vis);
            }
        }
        
        // Count unvisited 1s
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    count++;
                }
            }
        }
        return count;
    }
};

// =============================================================================
// Implementation 2: Breadth-First Search (BFS) Approach (Multi-Source)
// =============================================================================
class SolutionBFS {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        queue<pair<int, int>> q;
        
        // Push all boundary 1s into the queue and mark visited
        for (int j = 0; j < m; j++) {
            if (grid[0][j] == 1 && !vis[0][j]) {
                q.push({0, j});
                vis[0][j] = 1;
            }
            if (grid[n - 1][j] == 1 && !vis[n - 1][j]) {
                q.push({n - 1, j});
                vis[n - 1][j] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            if (grid[i][0] == 1 && !vis[i][0]) {
                q.push({i, 0});
                vis[i][0] = 1;
            }
            if (grid[i][m - 1] == 1 && !vis[i][m - 1]) {
                q.push({i, m - 1});
                vis[i][m - 1] = 1;
            }
        }
        
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};
        
        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            
            for (int i = 0; i < 4; i++) {
                int nRow = r + delRow[i];
                int nCol = c + delCol[i];
                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && grid[nRow][nCol] == 1 && !vis[nRow][nCol]) {
                    vis[nRow][nCol] = 1;
                    q.push({nRow, nCol});
                }
            }
        }
        
        // Count unvisited 1s
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    count++;
                }
            }
        }
        return count;
    }
};
