#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, vector<vector<int>>& adj,
         vector<bool>& vis, vector<int>& component) {
    
    vis[node] = true;

    component.push_back(node);

    for (int neighbor : adj[node]) {
        if (!vis[neighbor]) {
            dfs(neighbor, adj, vis, component);
        }
    }
}

vector<vector<int>> getComponents(int V, vector<vector<int>>& edges,vector<vector<int> > &adj) {
    
    vector<bool> vis(V, false);

    vector<vector<int>> res;

    for (int i = 0; i < V; ++i) {
        if (!vis[i]) {
            
            vector<int> component;

            dfs(i, adj, vis, component);

            res.push_back(component);
        }
    }

    return res;
}

int main() {
    int V = 5;

    vector<vector<int>> edges = {{0, 1}, {1, 2}, {3, 4}};
    vector<vector<int>> adj(V);

    for (auto edge : edges) {
        int u = edge[0];
        int v = edge[1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> res = getComponents(V, edges, adj);
    cout << res.size() << endl;

    return 0;
}


// T.C. = O(V+E)
// S.C. = O(V)