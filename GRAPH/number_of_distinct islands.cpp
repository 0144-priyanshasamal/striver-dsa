/*
================================================================================
Problem Name: Number of Distinct Islands (GFG / LeetCode 694)
Difficulty: Medium
Category: Graph Theory / Matrix / Depth-First Search (DFS)
================================================================================

Problem Description:
Given a 2D binary matrix where 1 represents land and 0 represents water. 
An "island" is a group of 1s that are connected 4-directionally (up, down, left, 
right). Two islands are considered distinct if their shapes are different. The 
shape of an island is defined by the relative positions of its land cells. 
Translation or rotation does not make an island distinct.

Your task is to find the number of distinct islands in the given matrix.

--------------------------------------------------------------------------------
Example 1:
Input: grid = 
{{
  {1,1,0,0,0},
  {1,1,0,0,0},
  {0,0,0,1,1},
  {0,0,0,1,1}
}}

Output: 1

Explanation:
There are two islands, but they have the same shape (a 2x2 square of 1s).
Island 1: Top-left 2x2 square
Island 2: Bottom-right 2x2 square
Since their shapes are identical, they are not distinct. Hence, the answer is 1.

--------------------------------------------------------------------------------
Example 2:
Input: grid = 
{{
  {1,1,0,1,1},
  {1,0,0,0,0},
  {0,0,0,0,1},
  {1,1,0,1,1}
}}

Output: 3

Explanation:
Island 1: Top-left 'L' shape
Island 2: Top-right 'L' shape
Island 3: Bottom-right 2x2 square
These three islands have different shapes.

--------------------------------------------------------------------------------
Example 3:
Input: grid = 
{{
  {1,1,1},
  {0,1,0},
  {1,1,1}
}}

Output: 1

Explanation: All 1s form a single island with a hole in the center, 
which has a unique shape.

--------------------------------------------------------------------------------
Complexity:
- Time Complexity: O(N * M)
  We visit each cell at most a constant number of times.
- Space Complexity: O(N * M)
  For the visited matrix and recursion stack space.

================================================================================
*/

#include <vector>
#include <queue>
#include <set>
#include <utility>

using namespace std;

class Solution {
private:
    void dfs(int row, int col, vector<vector<int>> &vis, vector<vector<int>> &grid, vector<pair<int,int>> &vec, int row0, int col0){
        vis[row][col] = 1;
        vec.push_back({row - row0, col - col0});
        int n = grid.size();
        int m = grid[0].size();
        int delRow[] = {-1, 0, +1, 0};
        int delCol[] = {0, -1, 0, +1};
        for(int i = 0; i < 4; i++) {
            int nrow = row + delRow[i];
            int ncol = col + delCol[i];
            if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && !vis[nrow][ncol] && grid[nrow][ncol] == 1){
                dfs(nrow, ncol, vis, grid, vec, row0, col0);
            }
        }
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        set<vector<pair<int,int>>> st;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(!vis[i][j] && grid[i][j] == 1){
                    vector<pair<int,int>> vec;
                    dfs(i, j, vis, grid, vec, i, j);
                    st.insert(vec);
                }
            }
        }
        return st.size();
    }
};
