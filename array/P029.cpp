#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        int k; cin>>k;
        deque<int> dq;
        vector<int> res;
        for(int i=0;i<n;++i){
            while(!dq.empty() && dq.front()<=i-k) dq.pop_front();
            while(!dq.empty() && a[dq.back()]<=a[i]) dq.pop_back();
            dq.push_back(i);
            if(i>=k-1) res.push_back(a[dq.front()]);
        }
        for(size_t i=0;i<res.size();++i) cout<<res[i]<<(i+1==res.size()?'\n':' ');
    }
};