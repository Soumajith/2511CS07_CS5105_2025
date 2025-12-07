#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int R,C;
    vector<string> grid;
    string word;
    bool dfs(int i,int j,int idx, vector<vector<int>>& vis){
        if(idx==word.size()) return true;
        if(i<0||i>=R||j<0||j>=C) return false;
        if(vis[i][j]||grid[i][j]!=word[idx]) return false;
        vis[i][j]=1;
        bool ok = dfs(i+1,j,idx+1,vis)||dfs(i-1,j,idx+1,vis)||dfs(i,j+1,idx+1,vis)||dfs(i,j-1,idx+1,vis);
        vis[i][j]=0;
        return ok;
    }
    void solve() {
        grid.resize(R);
        for(int i=0;i<R;++i) { string row; cin>>row; grid[i]=row; }
        cin>>word;
        for(int i=0;i<R;++i){
            for(int j=0;j<C;++j){
                vector<vector<int>> vis(R, vector<int>(C,0));
                if(dfs(i,j,0,vis)){ cout<<1<<"\n"; return; }
            }
        }
        cout<<0<<"\n";
    }
};