/*
================================================================================
Problem Name: Floyd-Warshall Algorithm (All Pairs Shortest Path)
Difficulty: Medium
Category: Graph Theory / Shortest Path / Dynamic Programming
================================================================================

Problem Description:
Given an edge-weighted directed graph represented as an adjacency matrix of size V x V.
Find the shortest distance between all pairs of vertices. matrix[i][j] denotes the 
weight of the edge from vertex i to vertex j. If matrix[i][j] = -1, it means there is 
no edge from i to j. Modify the matrix in-place.

--------------------------------------------------------------------------------
Example 1:
Input: 
matrix = [
  [0, 2, -1, -1], 
  [1, 0, 3, -1], 
  [-1, -1, 0, 1], 
  [3, 5, 4, 0]
]

Output:
[
  [0, 2, 5, 6], 
  [1, 0, 3, 4], 
  [4, 6, 0, 1], 
  [3, 5, 4, 0]
]

Explanation: 
- The shortest distance from 0 to 2 is 5 (via path 0 -> 1 -> 2, weight = 2 + 3 = 5).
- The shortest distance from 0 to 3 is 6 (via path 0 -> 1 -> 2 -> 3, weight = 2 + 3 + 1 = 6).
- The shortest distance from 1 to 3 is 4 (via path 1 -> 2 -> 3, weight = 3 + 1 = 4).

--------------------------------------------------------------------------------
Example 2:
Input:
matrix = [
  [0, 25],
  [-1, 0]
]

Output:
[
  [0, 25],
  [-1, 0]
]

Explanation: 
There is no path from 1 to 0, so matrix[1][0] remains -1.

--------------------------------------------------------------------------------
Constraints:
- 1 <= V <= 100
- -1 <= matrix[i][j] <= 1000

Expected Time Complexity: O(V^3)
Expected Auxiliary Space: O(1) (In-place)

================================================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
     * Function to find the shortest distance between every pair of vertices.
     * matrix[i][j] = weight of edge from i to j, or -1 if there is no edge.
     * The function updates the matrix in-place.
     */
    void shortest_distance(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Standard Floyd-Warshall Algorithm:
        // Try every vertex k as an intermediate node
        for (int k = 0; k < n; k++) {
            // Pick source vertex i
            for (int i = 0; i < n; i++) {
                // Pick destination vertex j
                for (int j = 0; j < n; j++) {
                    // If vertex k cannot be an intermediate node, skip
                    if (matrix[i][k] == -1 || matrix[k][j] == -1) {
                        continue;
                    }

                    // If there is no existing path from i to j, update it
                    if (matrix[i][j] == -1) {
                        matrix[i][j] = matrix[i][k] + matrix[k][j];
                    }
                    // If a path exists, check if path through k is shorter
                    else {
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
                }
            }
        }
    }
};
