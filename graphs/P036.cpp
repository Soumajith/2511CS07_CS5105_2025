#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int V,E; cin>>V>>E;
        vector<vector<pair<int,int>>> adj(V);
        for(int i=0;i<E;i++){ int u,v,w; cin>>u>>v>>w; adj[u].push_back({v,w}); adj[v].push_back({u,w}); }
        vector<int> vis(V,0);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0,0});
        long long total=0;
        while(!pq.empty()){
            auto [w,u]=pq.top(); pq.pop();
            if(vis[u]) continue;
            vis[u]=1; total += w;
            for(auto &p:adj[u]) if(!vis[p.first]) pq.push({p.second, p.first});
        }
        cout<<total<<"\n";
    }
};
