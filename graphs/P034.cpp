#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int n; cin>>n;
        vector<vector<long long>> mat(n, vector<long long>(n));
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>mat[i][j];
        const long long INF = 1e12;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(mat[i][j]==-1) mat[i][j]=INF;
        for(int k=0;k<n;k++) for(int i=0;i<n;i++) for(int j=0;j<n;j++){
            if(mat[i][k]<INF && mat[k][j]<INF) mat[i][j]=min(mat[i][j], mat[i][k]+mat[k][j]);
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(mat[i][j]>=INF/2) cout<<-1; else cout<<mat[i][j];
                cout<<(j+1==n?'\n':' ');
            }
        }
    }
};
