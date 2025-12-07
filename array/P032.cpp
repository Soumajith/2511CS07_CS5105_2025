#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        int tortoise=a[0], hare=a[0];
        do{ tortoise = a[tortoise]; hare = a[a[hare]]; } while(tortoise!=hare);
        tortoise = a[0];
        while(tortoise!=hare){ tortoise=a[tortoise]; hare=a[hare]; }
        cout<<hare<<"\n";
    }
};