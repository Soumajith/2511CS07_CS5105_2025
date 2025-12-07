#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int V,E; cin>>V>>E;
        vector<vector<int>> adj(V);
        vector<int> indeg(V,0);
        for(int i=0;i<E;i++){ int u,v; cin>>u>>v; adj[u].push_back(v); indeg[v]++; }
        queue<int>q;
        for(int i=0;i<V;i++) if(indeg[i]==0) q.push(i);
        vector<int> order;
        while(!q.empty()){
            int u=q.front(); q.pop(); order.push_back(u);
            for(int v:adj[u]){ indeg[v]--; if(indeg[v]==0) q.push(v); }
        }
        for(size_t i=0;i<order.size();++i) cout<<order[i]<<(i+1==order.size()?'\n':' ');
    }
};
