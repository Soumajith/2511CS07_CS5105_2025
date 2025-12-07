#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        int k; cin>>k;
        unordered_map<int,int> mp;
        for(int i=0;i<n;++i){
            int need = k - a[i];
            if(mp.find(need)!=mp.end()){
                cout<<mp[need]<<" "<<i<<"\n";
                return;
            }
            mp[a[i]] = i;
        }
        cout<<"-1 -1\n";
    }
};