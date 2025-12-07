#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        int cur=0, best=0;
        for(int x:a){
            if(x==1) cur++; else cur=0;
            best=max(best,cur);
        }
        cout<<best<<"\n";
    }
};