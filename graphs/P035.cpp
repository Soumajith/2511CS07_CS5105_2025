#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int n,m; cin>>n>>m;
        vector<vector<int>> edges(m, vector<int>(3));
        vector<vector<pair<int,int>>> adj(n);
        for(int i=0;i<m;i++){ cin>>edges[i][0]>>edges[i][1]>>edges[i][2]; int u=edges[i][0], v=edges[i][1], w=edges[i][2]; adj[u].push_back({v,w}); adj[v].push_back({u,w}); }
        int distTh; cin>>distTh;
        const long long INF=1e18;
        vector<vector<long long>> dist(n, vector<long long>(n, INF));
        for(int i=0;i<n;i++){
            priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
            dist[i][i]=0; pq.push({0,i});
            while(!pq.empty()){
                auto [d,u]=pq.top(); pq.pop();
                if(d!=dist[i][u]) continue;
                for(auto &p:adj[u]){
                    int v=p.first; int w=p.second;
                    if(d+w < dist[i][v]){ dist[i][v]=d+w; pq.push({dist[i][v], v}); }
                }
            }
        }
        int bestCity=-1, bestCnt=INT_MAX;
        for(int i=0;i<n;i++){
            int cnt=0;
            for(int j=0;j<n;j++) if(i!=j && dist[i][j]<=distTh) cnt++;
            if(cnt<=bestCnt){ bestCnt=cnt; bestCity=i; }
        }
        cout<<bestCity<<"\n";
    }
};
