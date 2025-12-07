#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int V,E; cin>>V>>E;
        vector<tuple<int,int,int>> edges;
        for(int i=0;i<E;i++){ int u,v,w; cin>>u>>v>>w; edges.push_back({u,v,w}); }
        int S; cin>>S;
        const long long INF=1e18;
        vector<long long> dist(V, INF);
        dist[S]=0;
        for(int i=0;i<V-1;i++){
            for(auto &e:edges){
                int u,v,w; tie(u,v,w)=e;
                if(dist[u]!=INF && dist[u]+w < dist[v]) dist[v]=dist[u]+w;
            }
        }
        // check negative cycle
        for(auto &e:edges){
            int u,v,w; tie(u,v,w)=e;
            if(dist[u]!=INF && dist[u]+w < dist[v]){
                cout<<"-1\n"; return;
            }
        }
        for(int i=0;i<V;i++) cout<<(dist[i]==INF? (long long)1e9 : dist[i])<<(i+1==V?'\n':' ');
    }
};
