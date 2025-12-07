#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<vector<int>> a(n, vector<int>(n));
        for(int i=0;i<n;++i) for(int j=0;j<n;++j) cin>>a[i][j];
        for(int i=0;i<n;++i){
            for(int j=i+1;j<n;++j) swap(a[i][j], a[j][i]);
        }
        for(int i=0;i<n;++i) reverse(a[i].begin(), a[i].end());
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                cout<<a[i][j]<<(j==n-1?'\n':' ');
            }
        }
    }
};