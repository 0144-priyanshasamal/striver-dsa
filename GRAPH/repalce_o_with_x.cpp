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
// Implementation 1: GFG Style (Using DFS and Visited Array)
// =============================================================================
class SolutionGFG {
private:
    void dfs(int r, int c, vector<vector<int>>& vis, vector<vector<char>>& mat, int dRow[], int dCol[]) {
        vis[r][c] = 1;
        int n = mat.size();
        int m = mat[0].size();
        
        for (int i = 0; i < 4; i++) {
            int nRow = r + dRow[i];
            int nCol = c + dCol[i];
            
            // Check boundary, check if it's 'O', and check if not visited
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m) {
                if (!vis[nRow][nCol] && mat[nRow][nCol] == 'O') {
                    dfs(nRow, nCol, vis, mat, dRow, dCol);
                }
            }
        }
    }

public:
    vector<vector<char>> fill(int n, int m, vector<vector<char>> mat) {
        vector<vector<int>> vis(n, vector<int>(m, 0));
        
        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};
        
        // Traverse first row and last row
        for (int j = 0; j < m; j++) {
            // First row
            if (!vis[0][j] && mat[0][j] == 'O') {
                dfs(0, j, vis, mat, dRow, dCol);
            }
            // Last row
            if (!vis[n - 1][j] && mat[n - 1][j] == 'O') {
                dfs(n - 1, j, vis, mat, dRow, dCol);
            }
        }
        
        // Traverse first column and last column
        for (int i = 0; i < n; i++) {
            // First column
            if (!vis[i][0] && mat[i][0] == 'O') {
                dfs(i, 0, vis, mat, dRow, dCol);
            }
            // Last column
            if (!vis[i][m - 1] && mat[i][m - 1] == 'O') {
                dfs(i, m - 1, vis, mat, dRow, dCol);
            }
        }
        
        // If a cell is 'O' and has not been visited, it means it is surrounded.
        // So, replace it with 'X'.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && mat[i][j] == 'O') {
                    mat[i][j] = 'X';
                }
            }
        }
        
        return mat;
    }
};

// =============================================================================
// Implementation 2: LeetCode 130 - Surrounded Regions (In-place DFS, Space Optimized)
// =============================================================================
// This implementation modifies the board directly. Instead of using a 'vis' array,
// boundary-connected 'O's are temporarily replaced with '#' to save space.
class SolutionLeetCode {
private:
    void dfs(int r, int c, vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        
        board[r][c] = '#'; // Mark as boundary-connected
        
        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};
        
        for (int i = 0; i < 4; i++) {
            int nRow = r + dRow[i];
            int nCol = c + dCol[i];
            
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && board[nRow][nCol] == 'O') {
                dfs(nRow, nCol, board);
            }
        }
    }

public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;
        int n = board.size();
        int m = board[0].size();
        
        // Step 1: Run DFS from boundary 'O's and temporarily change them to '#'
        for (int i = 0; i < n; i++) {
            // Left boundary
            if (board[i][0] == 'O') dfs(i, 0, board);
            // Right boundary
            if (board[i][m - 1] == 'O') dfs(i, m - 1, board);
        }
        for (int j = 0; j < m; j++) {
            // Top boundary
            if (board[0][j] == 'O') dfs(0, j, board);
            // Bottom boundary
            if (board[n - 1][j] == 'O') dfs(n - 1, j, board);
        }
        
        // Step 2: Update the board
        // - Replace remaining 'O's (surrounded) with 'X'
        // - Restore '#'s (boundary-connected) back to 'O'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == '#') {
                    board[i][j] = 'O';
                }
            }
        }
    }
};
