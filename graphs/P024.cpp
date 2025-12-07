#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int n,m; cin>>n>>m;
        vector<vector<int>> adj(n);
        vector<int> indeg(n,0);
        for(int i=0;i<m;i++){ int u,v; cin>>u>>v; adj[u].push_back(v); indeg[v]++; }
        queue<int>q; for(int i=0;i<n;i++) if(indeg[i]==0) q.push(i);
        vector<int> order;
        while(!q.empty()){
            int u=q.front(); q.pop(); order.push_back(u);
            for(int v:adj[u]){ indeg[v]--; if(indeg[v]==0) q.push(v); }
        }
        if((int)order.size()!=n) cout<<"No\n"; else {
            cout<<"Yes\n";
            for(int i=0;i<n;i++) cout<<order[i]<<(i+1==n?'\n':' ');
        }
    }
};
