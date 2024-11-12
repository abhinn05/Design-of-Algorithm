#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSet {
public:
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

pair<vector<Edge>, int> kruskal(int numVertices, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());  // Sort edges by weight
    DisjointSet ds(numVertices);
    vector<Edge> mst;
    int mstWeight = 0;

    for (const auto& edge : edges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            mst.push_back(edge);
            mstWeight += edge.weight;
            ds.unionSets(edge.u, edge.v);
        }
    }

    return {mst, mstWeight};
}

int main() {
    // Example graph represented as edge list (u, v, weight)
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 4}, {3, 4, 5}
    };
    int numVertices = 5;

    // Call the Kruskal function
    pair<vector<Edge>, int> result = kruskal(numVertices, edges);
    
    // Unpack the result manually
    vector<Edge> mst = result.first;
    int totalWeight = result.second;

    // Output the result
    cout << "Edges in MST:\n";
    for (const auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }
    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}
