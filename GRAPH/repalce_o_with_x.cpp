/*
================================================================================
Problem Name: Replace O's with X's (GFG) / Surrounded Regions (LeetCode 130)
Difficulty: Medium
Category: Graph Theory / Matrix / Depth-First Search (DFS) / Breadth-First Search (BFS)
================================================================================

Problem Description:
Given a matrix of size N x M where every cell contains either 'O' or 'X'. 
Replace all 'O' with 'X' if they are surrounded by 'X'. 
An 'O' cell is considered surrounded by 'X' if all its adjacent cells (up, down, 
left, and right) are surrounded by 'X' or are 'X' themselves. 

Essentially, any 'O' that is connected to the boundary of the matrix (either 
directly on the boundary or via a path of 'O's) cannot be surrounded by 'X'. 
Therefore, they should not be replaced. All other 'O's must be replaced with 'X'.

--------------------------------------------------------------------------------
Example 1:
Input: 
mat = {{'X', 'X', 'X', 'X'},
       {'X', 'O', 'X', 'X'},
       {'X', 'O', 'O', 'X'},
       {'X', 'O', 'X', 'X'},
       {'X', 'X', 'O', 'O'}}

Output: 
{{'X', 'X', 'X', 'X'},
 {'X', 'X', 'X', 'X'},
 {'X', 'X', 'X', 'X'},
 {'X', 'X', 'X', 'X'},
 {'X', 'X', 'O', 'O'}}

Explanation: 
- The 'O's at (1,1), (2,1), (2,2), (3,1) are surrounded by 'X' because they 
  do not lead to any boundary cell. Hence, they are replaced with 'X'.
- The 'O's at (4,2) and (4,3) are on the boundary, so they cannot be surrounded 
  and remain 'O'.

--------------------------------------------------------------------------------
Complexity:
- Time Complexity: O(N * M)
  We traverse the boundary cells and run DFS starting from boundary 'O's. 
  In the worst case, every cell is visited at most a constant number of times.
- Space Complexity: O(N * M)
  For the visited matrix and recursion stack space of DFS.

================================================================================
*/

#include <vector>
#include <queue>

using namespace std;

// =============================================================================
// Corrected Implementation of User's Solution
// =============================================================================
class Solution {
private:
    void dfs(int row, int col, vector<vector<int>> &vis, vector<vector<char>> &mat) {
        vis[row][col] = 1;     
        int n = mat.size();
        int m = mat[0].size();
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int nRow = row + delRow[i];
            int nCol = col + delCol[i];
            
            // Fixed: Use char literals ('O') instead of string literals ("O")
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && mat[nRow][nCol] == 'O' && !vis[nRow][nCol]) {
                dfs(nRow, nCol, vis, mat);
            }
        }     
    }

public:
    vector<vector<char>> fill(int n, int m, vector<vector<char>> mat) {
        vector<vector<int>> vis(n, vector<int>(m, 0));
        
        // Step 1: Traverse first row and last row to mark boundary 'O's
        for (int j = 0; j < m; j++) {
            // first row 
            if (!vis[0][j] && mat[0][j] == 'O') {
                dfs(0, j, vis, mat);
            }
            // last row
            if (!vis[n - 1][j] && mat[n - 1][j] == 'O') {
                dfs(n - 1, j, vis, mat);
            }
        }
        
        // Step 2: Traverse first column and last column to mark boundary 'O's
        for (int i = 0; i < n; i++) {
            // first column
            if (!vis[i][0] && mat[i][0] == 'O') {
                dfs(i, 0, vis, mat);
            }
            // last column
            if (!vis[i][m - 1] && mat[i][m - 1] == 'O') {
                dfs(i, m - 1, vis, mat);
            }
        }

        // Step 3: Replace all unvisited 'O's with 'X'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && mat[i][j] == 'O') {
                    mat[i][j] = 'X';
                }
            }
        }

        // Step 4: Return the modified matrix
        return mat;
    }
};

