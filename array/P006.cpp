#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        int pos=0;
        for(int i=0;i<n;++i) if(a[i]!=0) a[pos++]=a[i];
        while(pos<n) a[pos++]=0;
        for(int i=0;i<n;++i) cout<<a[i]<<(i==n-1?'\n':' ');
    }
};