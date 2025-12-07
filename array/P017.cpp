#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n),b(m);
        for(int i=0;i<n;++i) cin>>a[i];
        for(int j=0;j<m;++j) cin>>b[j];
        vector<long long> res;
        int i=0,j=0;
        while(i<n && j<m){
            long long v = (a[i]<b[j])?a[i]:b[j];
            if(res.empty() || res.back()!=v) res.push_back(v);
            if(a[i]==v) i++; else j++;
        }
        while(i<n){
            if(res.empty() || res.back()!=a[i]) res.push_back(a[i]);
            i++;
        }
        while(j<m){
            if(res.empty() || res.back()!=b[j]) res.push_back(b[j]);
            j++;
        }
        for(size_t k=0;k<res.size();++k) cout<<res[k]<<(k+1==res.size()?'\n':' ');
    }
};