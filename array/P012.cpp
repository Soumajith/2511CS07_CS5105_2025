#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>p(n);
        for(int i=0;i<n;++i) cin>>p[i];
        long long minP=LLONG_MAX, profit=0;
        for(long long x:p){
            if(x<minP) minP=x;
            profit = max(profit, x - minP);
        }
        cout<<profit<<"\n";
    }
};