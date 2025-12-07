#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int timer;
    void dfs(int u,int p, vector<vector<int>>&adj, vector<int>&tin, vector<int>&low, vector<int>&vis, vector<int>&isArt){
        vis[u]=1; tin[u]=low[u]=++timer;
        int children=0;
        for(int v:adj[u]){
            if(v==p) continue;
            if(vis[v]) low[u]=min(low[u], tin[v]);
            else{
                children++;
                dfs(v,u,adj,tin,low,vis,isArt);
                low[u]=min(low[u], low[v]);
                if(p!=-1 && low[v] >= tin[u]) isArt[u]=1;
            }
        }
        if(p==-1 && children>1) isArt[u]=1;
    }
    void solve() {
        int n,m; cin>>n>>m;
        vector<vector<int>> adj(n);
        for(int i=0;i<m;i++){ int u,v; cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u); }
        vector<int> tin(n,0), low(n,0), vis(n,0), isArt(n,0);
        timer=0;
        for(int i=0;i<n;i++) if(!vis[i]) dfs(i,-1,adj,tin,low,vis,isArt);
        for(int i=0;i<n;i++) if(isArt[i]) cout<<i<<"\n";
    }
};
