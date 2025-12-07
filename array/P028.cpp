#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        int k; cin>>k;
        unordered_map<int,int> mp;
        vector<int> res;
        for(int i=0;i<n;++i){
            mp[a[i]]++;
            if(i>=k) {
                mp[a[i-k]]--;
                if(mp[a[i-k]]==0) mp.erase(a[i-k]);
            }
            if(i>=k-1) res.push_back((int)mp.size());
        }
        for(size_t i=0;i<res.size();++i) cout<<res[i]<<(i+1==res.size()?'\n':' ');
    }
};