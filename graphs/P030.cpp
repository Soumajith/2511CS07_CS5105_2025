#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int V,E; cin>>V>>E;
        vector<vector<pair<int,int>>> adj(V);
        for(int i=0;i<E;i++){ int u,v,w; cin>>u>>v>>w; adj[u].push_back({v,w}); adj[v].push_back({u,w}); }
        int S; cin>>S;
        const long long INF=1e18;
        vector<long long> dist(V,INF);
        set<pair<long long,int>> st;
        dist[S]=0; st.insert({0,S});
        while(!st.empty()){
            auto it=st.begin(); int u=it->second; st.erase(it);
            for(auto &p:adj[u]){
                int v=p.first; int w=p.second;
                if(dist[u]+w < dist[v]){
                    if(dist[v]!=INF) st.erase({dist[v],v});
                    dist[v]=dist[u]+w; st.insert({dist[v],v});
                }
            }
        }
        for(int i=0;i<V;i++) cout<<dist[i]<<(i+1==V?'\n':' ');
    }
};
