#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int N,K; cin>>N>>K;
        vector<string> dict(N);
        for(int i=0;i<N;i++) cin>>dict[i];
        vector<vector<int>> adj(26);
        for(int i=0;i<N-1;i++){
            string a=dict[i], b=dict[i+1];
            int L=min(a.size(), b.size());
            for(int j=0;j<L;j++){
                if(a[j]!=b[j]){
                    adj[a[j]-'a'].push_back(b[j]-'a'); break;
                }
            }
        }
        vector<int> indeg(26,0);
        for(int u=0;u<26;u++) for(int v:adj[u]) indeg[v]++;
        queue<int>q; for(int i=0;i<K;i++) if(indeg[i]==0) q.push(i);
        vector<int> order;
        while(!q.empty()){
            int u=q.front(); q.pop(); order.push_back(u);
            for(int v:adj[u]){ indeg[v]--; if(indeg[v]==0) q.push(v); }
        }
        for(size_t i=0;i<order.size();++i) cout<<char('a'+order[i])<<(i+1==order.size()?'\n':' ');
    }
};
