#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void topoUtil(int u, vector<int>&vis, vector<vector<int>>&adj, vector<int>&res){
        vis[u]=1;
        for(int v:adj[u]) if(!vis[v]) topoUtil(v,vis,adj,res);
        res.push_back(u);
    }
    void solve() {
        int V,E; cin>>V>>E;
        vector<vector<int>> adj(V);
        for(int i=0;i<E;i++){ int u,v; cin>>u>>v; adj[u].push_back(v); }
        vector<int> vis(V,0), res;
        for(int i=0;i<V;i++) if(!vis[i]) topoUtil(i,vis,adj,res);
        reverse(res.begin(), res.end());
        for(int i=0;i<V;i++) cout<<res[i]<<(i+1==V?'\n':' ');
    }
};
