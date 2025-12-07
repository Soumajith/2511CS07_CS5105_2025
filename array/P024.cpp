#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        int cand1=0,cand2=1,c1=0,c2=0;
        for(int x:a){
            if(x==cand1) c1++;
            else if(x==cand2) c2++;
            else if(c1==0){ cand1=x; c1=1; }
            else if(c2==0){ cand2=x; c2=1; }
            else { c1--; c2--; }
        }
        vector<int> res;
        int limit = n/3;
        c1=0; c2=0;
        for(int x:a){ if(x==cand1) c1++; if(x==cand2) c2++; }
        if(c1>limit) res.push_back(cand1);
        if(cand2!=cand1 && c2>limit) res.push_back(cand2);
        if(res.empty()) cout<<"\n"; else { for(size_t i=0;i<res.size();++i) cout<<res[i]<<(i+1==res.size()?'\n':' '); }
    }
};