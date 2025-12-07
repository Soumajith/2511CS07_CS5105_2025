#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool dfs(int u, vector<int>&vis, vector<vector<int>>&adj){
        vis[u]=1;
        for(int v:adj[u]){
            if(vis[v]==0){
                if(dfs(v,vis,adj)) return true;
            } else if(vis[v]==1) return true;
        }
        vis[u]=2;
        return false;
    }
    void solve() {
        int V,E; cin>>V>>E;
        vector<vector<int>> adj(V);
        for(int i=0;i<E;i++){ int u,v; cin>>u>>v; adj[u].push_back(v); }
        vector<int> vis(V,0);
        for(int i=0;i<V;i++){
            if(vis[i]==0){
                if(dfs(i,vis,adj)){ cout<<"1\n"; return; }
            }
        }
        cout<<"0\n";
    }
};
