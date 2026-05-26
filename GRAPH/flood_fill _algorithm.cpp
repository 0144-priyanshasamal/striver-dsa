/*
================================================================================
Problem Name: Flood Fill Algorithm (LeetCode 733 / GFG)
Difficulty: Easy
Category: Graph Theory / Grid Traversal / DFS / BFS
================================================================================

Problem Description:
An image is represented by an m x n integer grid 'image' where image[i][j] 
represents the pixel value of the image.

You are also given three integers sr, sc, and color. You should perform a flood 
fill on the image starting from the pixel image[sr][sc].

To perform a flood fill:
1. Consider the starting pixel (sr, sc).
2. Find all pixels connected 4-directionally to the starting pixel of the same 
   color as the starting pixel.
3. Find all pixels connected 4-directionally to those pixels (also with the same 
   color), and so on.
4. Replace the color of all of the aforementioned pixels with 'color'.

Return the modified image after performing the flood fill.

--------------------------------------------------------------------------------
Example 1:
Input: 
image = [
  [1, 1, 1],
  [1, 1, 0],
  [1, 0, 1]
]
sr = 1, sc = 1, color = 2

Output: 
[
  [2, 2, 2],
  [2, 2, 0],
  [2, 0, 1]
]

Explanation: 
From the center of the image with position (sr, sc) = (1, 1) (i.e., the cell with 
value 1), all pixels connected by a path of the same color (1) are colored 
with the new color (2). Note that the bottom-right corner pixel is not colored 2, 
because it is not 4-directionally connected to the starting pixel.

--------------------------------------------------------------------------------
Example 2:
Input: 
image = [
  [0, 0, 0],
  [0, 0, 0]
]
sr = 0, sc = 0, color = 0

Output: 
[
  [0, 0, 0],
  [0, 0, 0]
]

Explanation: 
The starting pixel is already colored 0, which is the same as the target color. 
No changes are made to the image.

--------------------------------------------------------------------------------
Complexity:
- Time Complexity: O(m * n) 
  In the worst case, we might need to traverse every single pixel of the image.
- Space Complexity:
  - DFS: O(m * n) for the recursion stack space in the worst case (e.g., a highly skewed recursive path).
  - BFS: O(m * n) for the queue storage in the worst case (e.g., storing the coordinates of boundary elements).

--------------------------------------------------------------------------------
Constraints:
- m == image.length
- n == image[i].length
- 1 <= m, n <= 50
- 0 <= image[i][j], color < 2^16
- 0 <= sr < m
- 0 <= sc < n

================================================================================
*/

#include <vector>
#include <queue>
#include <utility>

using namespace std;

// =============================================================================
// Method 1: Recursive Depth-First Search (DFS) - Cleanest & Most Intuitive
// =============================================================================
class SolutionDFS {
private:
    void dfs(int r, int c, vector<vector<int>>& image, int oldColor, int newColor) {
        int rows = image.size();
        int cols = image[0].size();

        // 1. Boundary check: Check if current cell is out of grid bounds
        if (r < 0 || c < 0 || r >= rows || c >= cols) {
            return;
        }

        // 2. Color check: Only visit pixels that have the starting color
        if (image[r][c] != oldColor) {
            return;
        }

        // 3. Update the color of the current pixel
        image[r][c] = newColor;

        // 4. Explore all 4 adjacent directions (Up, Down, Left, Right)
        dfs(r - 1, c, image, oldColor, newColor); // Up
        dfs(r + 1, c, image, oldColor, newColor); // Down
        dfs(r, c - 1, image, oldColor, newColor); // Left
        dfs(r, c + 1, image, oldColor, newColor); // Right
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int oldColor = image[sr][sc];
        
        // Edge Case: If the target color is the same as the starting color,
        // no filling is required, and returning immediately prevents infinite recursion.
        if (oldColor != color) {
            dfs(sr, sc, image, oldColor, color);
        }
        
        return image;
    }
};

// =============================================================================
// Method 2: Iterative Breadth-First Search (BFS) - Avoids Stack Overflow
// =============================================================================
class SolutionBFS {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int oldColor = image[sr][sc];
        
        // Edge Case: If target color is the same as starting color, return immediately.
        if (oldColor == color) {
            return image;
        }

        int rows = image.size();
        int cols = image[0].size();
        
        // Queue to store coordinates {row, col} for BFS traversal
        queue<pair<int, int>> q;
        
        // Direction vectors for moving 4-directionally: {row_offset, col_offset}
        int delRow[] = {-1, 1, 0, 0};
        int delCol[] = {0, 0, -1, 1};

        // Start BFS from the source pixel
        q.push({sr, sc});
        image[sr][sc] = color; // Mark as visited by coloring it immediately

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            // Traverse all 4 neighbors
            for (int i = 0; i < 4; i++) {
                int nr = r + delRow[i];
                int nc = c + delCol[i];

                // Check boundary limits and check if the neighbor has the original color
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && image[nr][nc] == oldColor) {
                    image[nr][nc] = color; // Recolor the neighbor
                    q.push({nr, nc});      // Queue it for further expansion
                }
            }
        }

        return image;
    }
};
