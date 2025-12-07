#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        if(n==0){ cout<<0<<"\n"; return; }
        int idx=0;
        for(int i=1;i<n;++i){
            if(a[i]!=a[idx]){
                ++idx;
                a[idx]=a[i];
            }
        }
        cout<<idx+1<<"\n";
        for(int i=0;i<=idx;++i) cout<<a[i]<<(i==idx?'\n':' ');
    }
};