#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        long long maxProd=a[0], minProd=a[0], ans=a[0];
        for(int i=1;i<n;++i){
            long long x=a[i];
            long long t1 = maxProd*x;
            long long t2 = minProd*x;
            maxProd = max({x, t1, t2});
            minProd = min({x, t1, t2});
            ans = max(ans, maxProd);
        }
        cout<<ans<<"\n";
    }
};