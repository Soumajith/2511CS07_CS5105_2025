#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int n;
        cin >> n;
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        bool ok=true;
        for(int i=1;i<n;++i) if(a[i]<a[i-1]){ ok=false; break; }
        cout<<(ok?1:0)<<"\n";
    }
};