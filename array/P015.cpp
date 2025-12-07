#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n); for(int i=0;i<n;++i) cin>>a[i];
        long long k; cin>>k;
        unordered_map<long long,int> mp;
        mp[0]=1;
        long long pref=0; long long cnt=0;
        for(int x:a){
            pref += x;
            if(mp.find(pref-k)!=mp.end()) cnt += mp[pref-k];
            mp[pref]++;
        }
        cout<<cnt<<"\n";
    }
};