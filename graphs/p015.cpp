// A C++ Program to detect cycle in an undirected graph
#include <bits/stdc++.h>
using namespace std;

bool isCycleUtil(int v, vector<vector<int>> &adj, vector<bool> &visited, int parent)
{
    visited[v] = true;

    for (int i : adj[v])
    {
        if (!visited[i])
        {
            if (isCycleUtil(i, adj, visited, v))
                return true;
        }
        else if (i != parent)
            return true;
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
bool isCycle(int V, vector<vector<int>> &edges)
{
    
    vector<vector<int>> adj = constructadj(V,edges);
    vector<bool> visited(V, false);

    for (int u = 0; u < V; u++)
    {
        if (!visited[u])
        {
            if (isCycleUtil(u, adj, visited, -1))
                return true;
        }
    }

    return false;
}
