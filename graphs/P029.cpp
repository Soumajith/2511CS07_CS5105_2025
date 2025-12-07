#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int n,m; cin>>n>>m;
        vector<vector<pair<int,int>>> adj(n);
        vector<int> indeg(n,0);
        for(int i=0;i<m;i++){ int u,v,w; cin>>u>>v>>w; adj[u].push_back({v,w}); indeg[v]++; }
        int src=0;
        vector<int> topo;
        queue<int>q; for(int i=0;i<n;i++) if(indeg[i]==0) q.push(i);
        while(!q.empty()){ int u=q.front(); q.pop(); topo.push_back(u); for(auto &p:adj[u]) if(--indeg[p.first]==0) q.push(p.first); }
        const long long INF = 1e18;
        vector<long long> dist(n, INF); dist[src]=0;
        for(int u:topo){
            if(dist[u]==INF) continue;
            for(auto &p:adj[u]){
                int v=p.first; int w=p.second;
                if(dist[u]+w < dist[v]) dist[v]=dist[u]+w;
            }
        }
        for(int i=0;i<n;i++) cout<<(dist[i]==INF?-1: (long long)dist[i])<<(i+1==n?'\n':' ');
    }
};
