#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int n,m; cin>>n>>m;
        vector<vector<int>> adj(n);
        for(int i=0;i<m;i++){ int u,v; cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u); }
        int src; cin>>src;
        vector<int> dist(n, -1);
        queue<int>q; q.push(src); dist[src]=0;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:adj[u]) if(dist[v]==-1){ dist[v]=dist[u]+1; q.push(v); }
        }
        for(int i=0;i<n;i++) cout<<dist[i]<<(i+1==n?'\n':' ');
    }
};
