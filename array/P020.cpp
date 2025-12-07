#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        long long k; cin>>k;
        unordered_map<long long,int> first;
        long long pref=0; int best=0;
        first[0] = -1;
        for(int i=0;i<n;++i){
            pref += a[i];
            if(first.find(pref)==first.end()) first[pref]=i;
            if(first.find(pref-k)!=first.end()){
                best = max(best, i - first[pref-k]);
            }
        }
        cout<<best<<"\n";
    }
};