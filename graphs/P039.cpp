#include <bits/stdc++.h>
using namespace std;
struct DSU{ vector<int> p; DSU(int n):p(n,-1){} int find(int x){ return p[x]<0?x:p[x]=find(p[x]); } bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; if(p[a]>p[b]) swap(a,b); p[a]+=p[b]; p[b]=a; return true; } int size(int x){ return -p[find(x)]; } };
class Solution {
public:
    void solve() {
        int n,m,k; cin>>n>>m>>k;
        DSU d(n*m);
        vector<int> ans;
        vector<vector<int>> grid(n, vector<int>(m,0));
        vector<pair<int,int>> ops(k);
        for(int i=0;i<k;i++) cin>>ops[i].first>>ops[i].second;
        int cnt=0;
        int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        for(auto &op:ops){
            int r=op.first, c=op.second;
            if(grid[r][c]==1){ ans.push_back(cnt); continue; }
            grid[r][c]=1; cnt++;
            int id = r*m + c;
            for(auto &dxy:dirs){
                int nr=r+dxy[0], nc=c+dxy[1];
                if(nr>=0&&nr<n&&nc>=0&&nc<m && grid[nr][nc]==1){
                    int nid = nr*m + nc;
                    if(d.unite(id,nid)) cnt--;
                }
            }
            ans.push_back(cnt);
        }
        for(size_t i=0;i<ans.size();++i) cout<<ans[i]<<(i+1==ans.size()?'\n':' ');
    }
};
