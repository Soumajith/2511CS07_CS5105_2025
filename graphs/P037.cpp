#include <bits/stdc++.h>
using namespace std;
struct DSU{ vector<int> p; DSU(int n):p(n,-1){} int find(int x){ return p[x]<0?x:p[x]=find(p[x]); } bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; if(p[a]>p[b]) swap(a,b); p[a]+=p[b]; p[b]=a; return true; } };
class Solution {
public:
    void solve() {
        int V,E; cin>>V>>E;
        vector<tuple<int,int,int>> edges;
        for(int i=0;i<E;i++){ int u,v,w; cin>>u>>v>>w; edges.push_back({w,u,v}); }
        sort(edges.begin(), edges.end());
        DSU d(V);
        long long total=0;
        for(auto &t:edges){
            int w,u,v; tie(w,u,v)=t;
            if(d.unite(u,v)) total += w;
        }
        cout<<total<<"\n";
    }
};
