#include <bits/stdc++.h>
using namespace std;

bool bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<pair<int, int>> q;
    q.push({start, -1});
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int neighbor : adj[node]) {

            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push({neighbor, node});
            } 
            else if (neighbor != parent) {
                return true;
            }
        }
    }
    return false;
}

vector<vector<int>> constructadj(int V, vector<vector<int>> &edges){
    
    vector<vector<int>> adj(V);
    for (auto it : edges)
    {
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }
    
    return adj;
}

bool isCycle(int V, vector<vector<int>>& edges) {
    
    vector<vector<int>> adj = constructadj(V, edges);
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++) {
        
        if (!visited[i]) {
            if (bfs(i, adj, visited)) {
                return true;
            }
        }
    }
    
    return false;
}