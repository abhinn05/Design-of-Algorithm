#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;  // (weight, vertex)

vector<pii> prim(int numVertices, vector<vector<int>>& graph) {
    vector<int> key(numVertices, INT_MAX);      // Min edge weight to each vertex
    vector<int> parent(numVertices, -1);        // To store MST
    vector<bool> inMST(numVertices, false);     // Track included vertices

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    key[0] = 0;
    pq.push({0, 0});  // Start from vertex 0

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (int v = 0; v < numVertices; v++) {
            int weight = graph[u][v];
            if (weight != 0 && weight != INT_MAX && !inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    vector<pii> mst;
    for (int v = 1; v < numVertices; v++) {
        if (parent[v] != -1) {
            mst.push_back({parent[v], v});
        }
    }
    return mst;
}

int main() {
    vector<vector<int>> graph = {
        {0, 4, 3, INT_MAX, INT_MAX},
        {4, 0, 1, 2, INT_MAX},
        {3, 1, 0, 4, 5},
        {INT_MAX, 2, 4, 0, 6},
        {INT_MAX, INT_MAX, 5, 6, 0}
    };
    int numVertices = 5;

    vector<pii> mst = prim(numVertices, graph);

    cout << "Edges in MST (Prim's):\n";
    for (const auto& edge : mst) {
        cout << edge.first << " - " << edge.second << endl;
    }

    return 0;
}
