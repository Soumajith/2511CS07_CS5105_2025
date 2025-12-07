#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int n,m; cin>>n>>m;
        vector<vector<pair<int,int>>> adj(n);
        for(int i=0;i<m;i++){ int u,v,w; cin>>u>>v>>w; adj[u].push_back({v,w}); }
        int src,dst,k; cin>>src>>dst>>k;
        const long long INF=1e18;
        vector<long long> dist(n, INF), ways(n,0);
        vector<int> stops(n, INT_MAX);
        priority_queue<tuple<long long,int,int>, vector<tuple<long long,int,int>>, greater<>> pq;
        pq.push({0, src, 0});
        vector<long long> bestCost(n, INF);
        while(!pq.empty()){
            auto [cost,u,stopsu]=pq.top(); pq.pop();
            if(u==dst){ cout<<cost<<"\n"; return; }
            if(stopsu>k+1) continue;
            for(auto &p:adj[u]){
                int v=p.first; int w=p.second;
                if(stopsu+1<=k+1 && cost + w < bestCost[v]){
                    bestCost[v]=cost+w;
                    pq.push({cost+w, v, stopsu+1});
                } else if(stopsu+1<=k+1 && bestCost[v]==INF){
                    pq.push({cost+w, v, stopsu+1});
                }
            }
        }
        cout<<"-1\n";
    }
};
