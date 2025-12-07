#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        vector<int> res;
        for(int i=0;i<n;++i){
            int idx = abs(a[i]) - 1;
            if(idx>=0 && idx<n){
                if(a[idx] < 0) res.push_back(abs(a[i]));
                else a[idx] = -a[idx];
            }
        }
        for(size_t i=0;i<res.size();++i) cout<<res[i]<<(i+1==res.size()?'\n':' ');
    }
};