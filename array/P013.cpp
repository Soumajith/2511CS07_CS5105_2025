#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        vector<long long> res;
        long long mx = LLONG_MIN;
        for(int i=n-1;i>=0;--i){
            if(a[i]>mx){
                res.push_back(a[i]);
                mx=a[i];
            }
        }
        reverse(res.begin(), res.end());
        for(size_t i=0;i<res.size();++i) cout<<res[i]<<(i+1==res.size()?'\n':' ');
    }
};