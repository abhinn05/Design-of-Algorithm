#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int n, int s, vector<vector<pair<int, int>>>& adj) {
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        int nodeDist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (auto& edge : adj[node]) {
            int adjDist = edge.second;
            int adjNode = edge.first;

            if (dist[node] + adjDist < dist[adjNode]) {
                dist[adjNode] = dist[node] + adjDist;
                pq.push({dist[adjNode], adjNode});
            }
        }
    }

    return dist;
}

int main() {
    int n, m, s;
    cout << "Enter number of cities (nodes) n, roads (edges) m, and starting city s:\n";
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> adj(n);

    cout << "Enter each road in the format (u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> distances = dijkstra(n, s, adj);

    cout << "Minimum distances from city " << s << ":\n";
    for (int i = 0; i < n; i++) {
        if (distances[i] == INT_MAX) {
            cout << "City " << i << ": infinity" << endl;
        } else {
            cout << "City " << i << ": " << distances[i] << endl;
        }
    }

    return 0;
}


// Enter number of cities (nodes) n, roads (edges) m, and starting city s:
// 5 6 0
// Enter each road in the format (u v w):
// 0 1 3 0 2 4 1 3 2 1 2 5 2 4 6 4 3 1
// Minimum distances from city 0:
// City 0: 0
// City 1: 3
// City 2: 4
// City 3: 5
// City 4: 6


