/*
================================================================================
Problem Name: Number of Islands (LeetCode 200 / GFG)
Difficulty: Medium
Category: Graph Theory / Breadth-First Search (BFS) / Queue
================================================================================

Problem Description:
Given an m x n 2D binary grid 'grid' which represents a map of '1's (land) and 
'0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands 
horizontally or vertically. You may assume all four edges of the grid are all 
surrounded by water.

--------------------------------------------------------------------------------
Note on Variations:
- LeetCode 200 (Standard): Land cells can only be connected horizontally or 
  vertically (4 directions: Up, Right, Down, Left).
- GeeksforGeeks (GFG): Land cells can be connected horizontally, vertically, 
  or diagonally (8 directions).

Both Queue-based (BFS) implementations are provided below for complete reference.

--------------------------------------------------------------------------------
Example 1 (LeetCode 200 - 4 Directions):
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2 (LeetCode 200 - 4 Directions):
Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

--------------------------------------------------------------------------------
Constraints:
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 300
- grid[i][j] is '0' or '1'.

================================================================================
*/

#include <vector>
#include <queue>
#include <utility>

using namespace std;

// =============================================================================
// Implementation 1: LeetCode 200 (4-Directional Queue-Based BFS)
// =============================================================================
class Solution {
public:

    void dfs(int r,int c,vector<vector<char>>& grid){
         int rows = grid.size();
        int cols = grid[0].size();

        // Boundary + water check
        if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] == '0')
            return;

        // Mark visited
        grid[r][c] = '0';

        // Explore 4 directions
        dfs(r + 1, c, grid);
        dfs(r - 1, c, grid);
        dfs(r, c + 1, grid);
        dfs(r, c - 1, grid);

    }
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        int count=0;

        for(int r=0;r<rows;r++){
            for(int c =0;c<cols;c++){
                // new island found
                if(grid[r][c] == '1'){
                    count++;

                    // after one is found get all other beside it for the entire island
                    dfs(r,c,grid);
                }
            }
        }
        return count;
    }
};
