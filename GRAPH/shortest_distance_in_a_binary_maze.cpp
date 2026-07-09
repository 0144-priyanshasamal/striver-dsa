/*
================================================================================
Problem Name: Shortest Distance in a Binary Maze
Difficulty: Medium
Category: Graph Theory / Breadth-First Search (BFS) / Shortest Path
================================================================================

Problem Description:
Given an n x m binary matrix 'grid' where each cell is either 0 (blocked) or 1 
(open). You need to find the shortest path from a given source cell to a 
destination cell. The path can only be created out of cells with value 1. 
If the path is not possible, return -1.

Note: You can move in only four directions: up, down, left, and right.

--------------------------------------------------------------------------------
Example 1:
Input:
grid = [
    [1, 1, 1, 1],
    [1, 1, 0, 1],
    [1, 1, 1, 1],
    [1, 1, 0, 0],
    [1, 0, 0, 0]
]
source = (0, 1)
destination = (2, 2)

Output: 3
Explanation: 
The shortest path from (0, 1) to (2, 2) is:
(0, 1) -> (0, 2) -> (1, 2) -> (2, 2)
The number of steps is 3.

--------------------------------------------------------------------------------
Example 2:
Input:
grid = [
    [1, 1, 1, 1, 1],
    [1, 1, 0, 1, 0],
    [1, 1, 0, 1, 1],
    [1, 1, 0, 0, 0],
    [1, 0, 0, 0, 0]
]
source = (0, 0)
destination = (4, 0)

Output: 4
Explanation:
The shortest path from (0, 0) to (4, 0) is:
(0, 0) -> (1, 0) -> (2, 0) -> (3, 0) -> (4, 0)
The number of steps is 4.

--------------------------------------------------------------------------------
Constraints:
- 1 <= n, m <= 500
- grid[i][j] is either 0 or 1
- source and destination are valid cells within the grid
- grid[source.first][source.second] == 1
- grid[destination.first][destination.second] == 1

Expected Time Complexity: O(n * m)
Expected Auxiliary Space: O(n * m)

================================================================================
*/

#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source, pair<int, int> destination) {
        // If source or destination is blocked, no path can exist
        if (grid[source.first][source.second] == 0 || grid[destination.first][destination.second] == 0) {
            return -1;
        }
        
        // If source is already at destination
        if (source == destination) {
            return 0;
        }
        
        int n = grid.size();
        int m = grid[0].size();
        
        // Distance array initialized to a large value (infinity)
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        
        // Queue to store coordinates of grid cells
        queue<pair<int, int>> q;
        
        // Initialize source
        dist[source.first][source.second] = 0;
        q.push(source);
        
        // Direction vectors for moving up, down, left, and right
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            
            // Explore all 4 adjacent directions
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                
                // Check if the neighbor cell is valid, not blocked, and has a shorter path
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] == 1) {
                    if (dist[r][c] + 1 < dist[nr][nc]) {
                        dist[nr][nc] = dist[r][c] + 1;
                        
                        // If we reached the destination, we can return the distance immediately
                        if (nr == destination.first && nc == destination.second) {
                            return dist[nr][nc];
                        }
                        
                        q.push({nr, nc});
                    }
                }
            }
        }
        
        // Destination is unreachable
        return -1;
    }
};
