#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

int main() {
    int V = 5;

    vector<vector<pii>> adj(V);

    // {neighbor, weight}
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});

    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});

    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});

    adj[1].push_back({4, 5});
    adj[4].push_back({1, 5});

    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    vector<bool> visited(V, false);

    pq.push({0, 0});   // {weight, node}

    int mstWeight = 0;

    while (!pq.empty()) {
        int wt = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (visited[node])
            continue;

        visited[node] = true;
        mstWeight += wt;

        for (auto it : adj[node]) {
            int adjNode = it.first;
            int edgeWt = it.second;

            if (!visited[adjNode]) {
                pq.push({edgeWt, adjNode});
            }
        }
    }

    cout << "Weight of MST = " << mstWeight << endl;

    return 0;
}
