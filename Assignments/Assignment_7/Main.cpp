#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;


bool bfs(vector<vector<int>>& residualGraph, int source, int sink, vector<int>& parent) 
{
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; ++v) 
        {
            if (!visited[v] && residualGraph[u][v] > 0) 
            { 
                if (v == sink) 
                {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return false;
}

int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int n = graph.size();
    vector<vector<int>> residualGraph = graph; 
    vector<int> parent(n); 

    int maxFlow = 0;

    
    while (bfs(residualGraph, source, sink, parent)) 
    {
        int pathFlow = INT_MAX;

        
        for (int v = sink; v != source; v = parent[v]) 
        {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        
        for (int v = sink; v != source; v = parent[v]) 
        {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    cout << "Enter the adjacency matrix for the graph (enter capacities for edges, 0 if no edge exists):\n";
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            cin >> graph[i][j];
        }
    }

    int source = 0; 
    int sink = n - 1; 

    cout << "The maximum possible flow is " << fordFulkerson(graph, source, sink) << endl;

    return 0;
}
