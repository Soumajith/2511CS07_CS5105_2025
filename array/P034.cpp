#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<vector<int>> mat(r, vector<int>(c));
        for(int i=0;i<r;++i) for(int j=0;j<c;++j) cin>>mat[i][j];
        vector<int> rows(r,0), cols(c,0);
        for(int i=0;i<r;++i) for(int j=0;j<c;++j) if(mat[i][j]==0){ rows[i]=1; cols[j]=1; }
        for(int i=0;i<r;++i){
            for(int j=0;j<c;++j){
                if(rows[i] || cols[j]) cout<<0;
                else cout<<mat[i][j];
                if(j==c-1) cout<<"\n"; else cout<<" ";
            }
        }
    }
};