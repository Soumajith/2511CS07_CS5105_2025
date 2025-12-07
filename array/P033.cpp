#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int nextGap(int gap){ if(gap<=1) return 0; return (gap/2) + (gap%2); }
    void solve() {
        vector<int>a(n),b(m);
        for(int i=0;i<n;++i) cin>>a[i];
        for(int j=0;j<m;++j) cin>>b[j];
        int gap = n+m;
        while(gap>0){
            gap = nextGap(gap);
            int i=0;
            for(; i+gap<n; ++i){
                if(a[i] > a[i+gap]) swap(a[i], a[i+gap]);
            }
            int j = gap>n? gap-n:0;
            for(; i<n && j<m; ++i,++j){
                if(a[i] > b[j]) swap(a[i], b[j]);
            }
            if(j<m){
                for(j=0; j+gap<m; ++j){
                    if(b[j] > b[j+gap]) swap(b[j], b[j+gap]);
                }
            }
        }
        for(int i=0;i<n;++i) cout<<a[i]<<(i==n-1?'\n':' ');
        for(int j=0;j<m;++j) cout<<b[j]<<(j==m-1?'\n':' ');
    }
};