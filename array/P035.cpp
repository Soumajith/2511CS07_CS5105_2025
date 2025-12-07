#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<vector<int>> a(r, vector<int>(c));
        for(int i=0;i<r;++i) for(int j=0;j<c;++j) cin>>a[i][j];
        int top=0, bottom=r-1, left=0, right=c-1;
        vector<int> res;
        while(top<=bottom && left<=right){
            for(int j=left;j<=right;++j) res.push_back(a[top][j]);
            top++;
            for(int i=top;i<=bottom;++i) res.push_back(a[i][right]);
            right--;
            if(top<=bottom){
                for(int j=right;j>=left;--j) res.push_back(a[bottom][j]);
                bottom--;
            }
            if(left<=right){
                for(int i=bottom;i>=top;--i) res.push_back(a[i][left]);
                left++;
            }
        }
        for(size_t i=0;i<res.size();++i) cout<<res[i]<<(i+1==res.size()?'\n':' ');
    }
};