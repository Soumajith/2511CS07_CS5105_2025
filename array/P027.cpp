#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        unordered_map<int,int> mp;
        int sum=0, best=0;
        for(int i=0;i<n;++i){
            sum += a[i];
            if(sum==0) best = max(best, i+1);
            if(mp.find(sum)==mp.end()) mp[sum]=i;
            if(mp.find(sum)==mp.end()) continue;
            best = max(best, i - mp[sum]);
        }
        cout<<best<<"\n";
    }
};