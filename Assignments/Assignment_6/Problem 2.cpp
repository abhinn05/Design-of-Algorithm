#include <bits/stdc++.h>
using namespace std;

vector<int> bellmanFord(int n, int s, vector<tuple<int, int, int>>& edges) {
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (auto& edge : edges) {
            int u, v, w;
            tie(u, v, w) = edge;

            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (auto& edge : edges) {
        int u, v, w;
        tie(u, v, w) = edge;

        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "Negative-weight cycle detected!" << endl;
            return {};  
        }
    }

    return dist;
}

int main() {
    int n, m, s;
    cout << "Enter number of cities (nodes) n, roads (edges) m, and starting city s:\n";
    cin >> n >> m >> s;

    vector<tuple<int, int, int>> edges;

    cout << "Enter each road in the format (u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    vector<int> distances = bellmanFord(n, s, edges);

    if (!distances.empty()) {
        cout << "Minimum distances from city " << s << ":\n";
        for (int i = 0; i < n; i++) {
            if (distances[i] == INT_MAX) {
                cout << "City " << i << ": infinity" << endl;
            } else {
                cout << "City " << i << ": " << distances[i] << endl;
            }
        }
    }

    return 0;
}
