#include <iostream>
#include <vector>
#include <queue>
#include <climits>  // For INT_MAX


using namespace std;

bool isSpanningTree(int numVertices, vector<vector<int>>& graph, vector<pair<int, int>>& edges) {
    vector<bool> visited(numVertices, false);
    queue<int> q;
    q.push(0);  // Start from the first vertex
    visited[0] = true;
    int count = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& edge : edges) {
            if (edge.first == u && !visited[edge.second]) {
                visited[edge.second] = true;
                q.push(edge.second);
                count++;
            } else if (edge.second == u && !visited[edge.first]) {
                visited[edge.first] = true;
                q.push(edge.first);
                count++;
            }
        }
    }

    return count == numVertices;
}

int main() {
    int numVertices = 5;
    vector<vector<int>> graph = {
        {0, 4, 3, INT_MAX, INT_MAX},
        {4, 0, 1, 2, INT_MAX},
        {3, 1, 0, 4, 5},
        {INT_MAX, 2, 4, 0, 6},
        {INT_MAX, INT_MAX, 5, 6, 0}
    };

    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {1, 3}, {3, 4}};

    if (isSpanningTree(numVertices, graph, edges)) {
        cout << "The edges form a valid spanning tree.\n";
    } else {
        cout << "The edges do not form a valid spanning tree.\n";
    }

    return 0;
}
