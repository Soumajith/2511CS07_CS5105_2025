#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        long long t; cin>>t;
        int ans=-1;
        for(int i=0;i<n;++i) if(a[i]==t){ ans=i; break; }
        cout<<ans<<"\n";
    }
};