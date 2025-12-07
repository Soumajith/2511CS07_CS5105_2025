#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        vector<int> pos, neg;
        for(int x:a) if(x>=0) pos.push_back(x); else neg.push_back(x);
        int i=0,j=0,idx=0;
        while(i<pos.size() && j<neg.size()){
            a[idx++]=pos[i++]; a[idx++]=neg[j++];
        }
        while(i<pos.size()) a[idx++]=pos[i++];
        while(j<neg.size()) a[idx++]=neg[j++];
        for(int k=0;k<n;++k) cout<<a[k]<<(k==n-1?'\n':' ');
    }
};