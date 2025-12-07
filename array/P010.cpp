#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        long long cand=0;
        int cnt=0;
        for(long long x:a){
            if(cnt==0){ cand=x; cnt=1; }
            else if(cand==x) cnt++;
            else cnt--;
        }
        cout<<cand<<"\n";
    }
};