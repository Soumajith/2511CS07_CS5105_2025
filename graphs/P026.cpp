#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int N,E; cin>>N>>E;
        vector<vector<int>> adj(N), radj(N);
        vector<int> out(N,0);
        for(int i=0;i<E;i++){ int u,v; cin>>u>>v; adj[u].push_back(v); radj[v].push_back(u); out[u]++; }
        queue<int>q;
        vector<int> safe(N,0);
        for(int i=0;i<N;i++) if(out[i]==0){ q.push(i); safe[i]=1; }
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:radj[u]){
                out[v]--; if(out[v]==0){ q.push(v); safe[v]=1; }
            }
        }
        vector<int> res;
        for(int i=0;i<N;i++) if(safe[i]) res.push_back(i);
        for(size_t i=0;i<res.size();++i) cout<<res[i]<<(i+1==res.size()?'\n':' ');
    }
};
