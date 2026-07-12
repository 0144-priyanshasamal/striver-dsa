#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {

        vector<vector<int>> dist(n, vector<int>(n, 1e9));

        // Distance from a city to itself is 0
        for (int i = 0; i < n; i++)
            dist[i][i] = 0;

        // Fill edge weights
        for (auto &it : edges) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];

            dist[u][v] = wt;
            dist[v][u] = wt;
        }

        // Floyd-Warshall
        for (int via = 0; via < n; via++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][via] == 1e9 || dist[via][j] == 1e9)
                        continue;

                    dist[i][j] = min(dist[i][j],
                                     dist[i][via] + dist[via][j]);
                }
            }
        }

        int city = -1;
        int minReachable = INT_MAX;

        for (int i = 0; i < n; i++) {
            int count = 0;

            for (int j = 0; j < n; j++) {
                if (dist[i][j] <= distanceThreshold)
                    count++;
            }

            // Tie -> larger index wins
            if (count <= minReachable) {
                minReachable = count;
                city = i;
            }
        }

        return city;
    }
};
