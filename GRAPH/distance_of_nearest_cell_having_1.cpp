/*
================================================================================
Problem Name: Distance of Nearest Cell Having 1 (GFG) / 01 Matrix (LeetCode 542)
Difficulty: Medium
Category: Graph Theory / Multi-Source BFS / Grid Traversal
================================================================================

Problem Description:
Given a binary grid of size N x M. Find the distance of nearest 1 in the grid for each cell.
The distance is calculated as |r1 - r2| + |c1 - c2| (Manhattan distance).

Note:
- In the GFG version, we find the distance of the nearest '1' for each cell in a grid of 0s and 1s.
- In the LeetCode 542 version ("01 Matrix"), we find the distance of the nearest '0' for each cell in a grid of 0s and 1s.
Both variations use the identical Multi-Source BFS technique. Here, we implement both variations for full reference.

--------------------------------------------------------------------------------
Example 1 (GFG - Nearest 1):
Input: grid = {{0,1,1,0}, {1,1,0,0}, {0,0,1,1}}
Output: {{1,0,0,1}, {0,0,1,1}, {1,1,0,0}}
Explanation: 
- For grid[0][0], nearest 1 is at grid[0][1] or grid[1][0] at distance 1.
- For grid[0][3], nearest 1 is at grid[0][2] at distance 1.
- For grid[1][2], nearest 1 is at grid[0][2] or grid[2][2] at distance 1.
- For grid[2][0], nearest 1 is at grid[1][0] at distance 1.

--------------------------------------------------------------------------------
Complexity:
- Time Complexity: O(N * M)
  Every cell is pushed and popped from the queue at most once. Grid traversal and neighbor checks take O(1) time per cell.
- Space Complexity: O(N * M)
  Required for the queue and the auxiliary visited/distance matrix.

================================================================================
*/

#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

// =============================================================================
// Implementation 1: GFG - Distance of Nearest Cell Having 1
// =============================================================================
// Uses Multi-Source BFS. All cells with '1' are inserted into the queue at the 
// beginning (source nodes) with initial distance 0.
class SolutionGFG {
public:
    vector<vector<int>> nearest(vector<vector<int>> grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Visited grid to keep track of visited cells
        vector<vector<int>> vis(n, vector<int>(m, 0));
        // Distance grid to store the result
        vector<vector<int>> dist(n, vector<int>(m, 0));

        // Queue to store coordinates of cells: {row, col}
        queue<pair<int, int>> q;

        // Step 1: Push all cells containing 1 into the queue and mark them visited
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                    vis[i][j] = 1;
                    dist[i][j] = 0; // Distance to nearest 1 is 0 for itself
                } else {
                    vis[i][j] = 0;
                }
            }
        }

        // 4-directional move arrays (Up, Right, Down, Left)
        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};

        // Step 2: Multi-Source BFS propagation
        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nRow = r + dRow[i];
                int nCol = c + dCol[i];

                // Check bounds and check if neighbor is not yet visited
                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !vis[nRow][nCol]) {
                    vis[nRow][nCol] = 1;
                    dist[nRow][nCol] = dist[r][c] + 1;
                    q.push({nRow, nCol});
                }
            }
        }

        return dist;
    }
};

// =============================================================================
// Implementation 2: LeetCode 542 - 01 Matrix (Nearest 0, Space-Optimized BFS)
// =============================================================================
// This implementation finds the nearest '0' and is space-optimized by avoiding the 
// auxiliary 'vis' matrix. It initializes non-zero cell distances to INT_MAX to 
// double as the "unvisited" indicator.
class SolutionLeetCode {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();

        queue<pair<int, int>> q;

        // Step 1: Initialize the distance matrix
        // Cells with 0 will have distance 0 and are added to queue.
        // Cells with 1 are initialized to INT_MAX (unvisited status).
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 0) {
                    q.push({i, j});
                } else {
                    mat[i][j] = INT_MAX;
                }
            }
        }

        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};

        // Step 2: Multi-Source BFS to propagate shortest path distance
        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++) {
                int nRow = r + dRow[i];
                int nCol = c + dCol[i];

                // If neighbor is valid and can achieve a smaller distance
                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m) {
                    if (mat[nRow][nCol] > mat[r][c] + 1) {
                        mat[nRow][nCol] = mat[r][c] + 1;
                        q.push({nRow, nCol});
                    }
                }
            }
        }

        return mat;
    }
};
