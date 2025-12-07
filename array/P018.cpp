#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        long long x; long long xr=0;
        for(int i=0;i<n;++i){ cin>>x; xr ^= x; }
        cout<<xr<<"\n";
    }
};