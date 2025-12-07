#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        unordered_set<int> s(a.begin(), a.end());
        int best=0;
        for(int x:s){
            if(s.find(x-1)==s.end()){
                int cur=1;
                while(s.find(x+cur)!=s.end()) cur++;
                best=max(best, cur);
            }
        }
        cout<<best<<"\n";
    }
};