#include <bits/stdc++.h>
using namespace std;
struct DSU{ vector<int> p; DSU(int n):p(n,-1){} int find(int x){ return p[x]<0?x:p[x]=find(p[x]); } bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; if(p[a]>p[b]) swap(a,b); p[a]+=p[b]; p[b]=a; return true; } int size(int x){ return -p[find(x)]; } };
class Solution {
public:
    void solve() {
        int n; cin>>n;
        vector<vector<int>> g(n, vector<int>(n));
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>g[i][j];
        DSU d(n*n);
        int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(g[i][j]==1){
            for(auto &di:dirs){
                int ni=i+di[0], nj=j+di[1];
                if(ni>=0&&ni<n&&nj>=0&&nj<n && g[ni][nj]==1) d.unite(i*n+j, ni*n+nj);
            }
        }
        int best=0;
        unordered_map<int,int> compSize;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(g[i][j]==1) compSize[d.find(i*n+j)] = d.size(i*n+j);
        for(auto &p:compSize) best = max(best, p.second);
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(g[i][j]==0){
            unordered_set<int> s;
            for(auto &di:dirs){
                int ni=i+di[0], nj=j+di[1];
                if(ni>=0&&ni<n&&nj>=0&&nj<n && g[ni][nj]==1) s.insert(d.find(ni*n+nj));
            }
            int cur=1;
            for(int id:s) cur += d.size(id);
            best = max(best, cur);
        }
        cout<<best<<"\n";
    }
};
