#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        long long expected = (long long)n*(n+1)/2;
        long long sum=0;
        for(int v:a) sum+=v;
        cout<<expected - sum<<"\n";
    }
};