#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        if(n>0){
            long long first=a[0];
            for(int i=0;i<n-1;++i) a[i]=a[i+1];
            a[n-1]=first;
        }
        for(int i=0;i<n;++i) cout<<a[i]<<(i==n-1?'\n':' ');
    }
};