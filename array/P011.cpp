#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<long long>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        long long max_ending=LLONG_MIN, max_so_far=LLONG_MIN;
        for(int i=0;i<n;++i){
            if(max_ending==LLONG_MIN) max_ending=a[i];
            else max_ending = max(a[i], max_ending + a[i]);
            max_so_far = max(max_so_far, max_ending);
        }
        cout<<max_so_far<<"\n";
    }
};