#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long> seq(m,0);
        if(m>0 && n-1 < m) seq[n-1]=1;
        long long sum=0;
        for(int i=0;i<n-1 && i<m; ++i) sum += seq[i];
        if(n-1 < m) sum += seq[n-1];
        for(int i=n; i<m; ++i){
            long long s=0;
            for(int j=i-n;j<i;++j) s += seq[j];
            seq[i]=s;
        }
        for(int i=0;i<m;++i) cout<<seq[i]<<(i+1==m?'\n':' ');
    }
};