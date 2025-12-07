#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        vector<vector<int>> res;
        for(int i=0;i<numRows;++i){
            vector<int> row(i+1,1);
            for(int j=1;j<i;++j) row[j]=res[i-1][j-1]+res[i-1][j];
            res.push_back(row);
        }
        for(auto &r:res){
            for(size_t i=0;i<r.size();++i) cout<<r[i]<<(i+1==r.size()?'\n':' ');
        }
    }
};