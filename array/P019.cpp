#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<int>a(n);
        for(int i=0;i<n;++i) cin>>a[i];
        long long k; cin>>k;
        int left=0; long long sum=0; int best=0;
        for(int right=0; right<n; ++right){
            sum += a[right];
            while(left<=right && sum>k){
                sum -= a[left++];
            }
            if(sum==k) best = max(best, right-left+1);
        }
        cout<<best<<"\n";
    }
};