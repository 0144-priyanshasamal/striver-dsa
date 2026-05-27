/*
================================================================================
Problem Name: Rotting Oranges (LeetCode 994 / GFG)
Difficulty: Medium
Category: Graph Theory / BFS / Multi-Source BFS / Grid Propagation
================================================================================

Problem Description:
You are given an m x n grid where each cell can have one of three values:
- 0 representing an empty cell,
- 1 representing a fresh orange, or
- 2 representing a rotten orange.

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange 
becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. 
If this is impossible, return -1.

--------------------------------------------------------------------------------
Example 1:
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Explanation:
- Minute 0: [[2,1,1], [1,1,0], [0,1,1]] (Fresh: 6, Rotten: 1)
- Minute 1: [[2,2,1], [2,1,0], [0,1,1]] (Fresh: 4, Rotten: 3)
- Minute 2: [[2,2,2], [2,2,0], [0,1,1]] (Fresh: 2, Rotten: 5)
- Minute 3: [[2,2,2], [2,2,0], [0,2,1]] (Fresh: 1, Rotten: 6)
- Minute 4: [[2,2,2], [2,2,0], [0,2,2]] (Fresh: 0, Rotten: 7)
All fresh oranges are rotten. Minimum time elapsed is 4 minutes.

--------------------------------------------------------------------------------
Example 2:
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: 
The orange in the bottom left corner (row 2, column 0) is never rotten, 
because rotting only happens 4-directionally.

--------------------------------------------------------------------------------
Example 3:
Input: grid = [[0,2]]
Output: 0
Explanation: 
Since there are already no fresh oranges at minute 0, the answer is just 0.

--------------------------------------------------------------------------------
Complexity:
- Time Complexity: O(m * n)
  Each cell is visited and processed at most once. We iterate through the grid 
  initially to find the coordinates of all rotten and fresh oranges, and then 
  perform a standard BFS traversal.
- Space Complexity: O(m * n)
  - Method 1: O(m * n) auxiliary space for the `vis` matrix and queue storing elements.
  - Method 2: O(m * n) space only for the queue, as the grid is updated in-place 
    without an auxiliary `vis` matrix.

--------------------------------------------------------------------------------
Constraints:
- m == grid.length
- n == grid[i].length
- 1 <= m, n <= 10
- grid[i][j] is 0, 1, or 2.

================================================================================
*/

#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

// =============================================================================
// Method 1: Multi-Source BFS with Visited Grid & Explicit Time Tracking
// =============================================================================
// This approach is highly intuitive and explicitly tracks the state of traversal
// without modifying the original grid. It keeps track of coordinates along with
// the time stamp in the queue: {{row, col}, time}.
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Queue to store {{row, col}, time}
        queue<pair<pair<int, int>, int>> q;

        // Visited grid to keep track of rotten oranges
        vector<vector<int>> vis(n, vector<int>(m, 0));
        int cntFresh = 0;

        // Step 1: Push all initially rotten oranges to the queue and count fresh ones
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.push({{i, j}, 0});
                    vis[i][j] = 2; // Mark as visited (rotten)
                } else {
                    vis[i][j] = 0;
                }

                if (grid[i][j] == 1) {
                    cntFresh++;
                }
            }
        }

        int maxTime = 0;
        int cntRotted = 0;

        // Direction arrays for moving up, right, down, and left
        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, 1, 0, -1};

        // Step 2: Multi-source BFS propagation
        while (!q.empty()) {
            int r = q.front().first.first;
            int c = q.front().first.second;
            int t = q.front().second;
            q.pop();

            maxTime = max(maxTime, t);

            for (int i = 0; i < 4; i++) {
                int nRow = r + dRow[i];
                int nCol = c + dCol[i];

                // Check boundary, check if not already rotted (visited), and check if it is a fresh orange
                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m &&
                    vis[nRow][nCol] == 0 && grid[nRow][nCol] == 1) {
                    
                    q.push({{nRow, nCol}, t + 1});
                    vis[nRow][nCol] = 2; // Mark as visited/rotten
                    cntRotted++;
                }
            }
        }

        // Step 3: If not all fresh oranges were rotted, return -1
        if (cntRotted != cntFresh) {
            return -1;
        }

        return maxTime;
    }
};

// =============================================================================
// Method 2: Space-Optimized BFS (In-place Grid Update, Level-by-Level)
// =============================================================================
// This approach is more space-efficient by modifying the input grid in-place 
// (replacing fresh oranges with rotten ones) and using a level-by-level queue traversal 
// (processing the queue size at each step) to track elapsed minutes.
class SolutionOptimized {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> q;
        int freshCount = 0;

        // Step 1: Collect initial rotten positions and count fresh oranges
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }

        int minutes = 0;
        // 4-directional offsets
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        // Step 2: Level-by-level BFS
        while (!q.empty() && freshCount > 0) {
            int currentLevelSize = q.size();
            
            for (int i = 0; i < currentLevelSize; ++i) {
                pair<int, int> curr = q.front();
                int r = curr.first;
                int c = curr.second;
                q.pop();

                for (int j = 0; j < 4; j++) {
                    int nr = r + dirs[j][0];
                    int nc = c + dirs[j][1];

                    // Check bounds and if neighbor is a fresh orange
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // Rot in-place
                        q.push({nr, nc});
                        freshCount--;
                    }
                }
            }
            minutes++;
        }

        // Step 3: Return minutes if all fresh oranges rotted, else -1
        return (freshCount == 0) ? minutes : -1;
    }
};
