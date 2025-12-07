#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void solve() {
        int n; cin>>n;
        vector<int> arr(n);
        for(int i=0;i<n;i++) cin>>arr[i];
        int start,endv; cin>>start>>endv;
        const int MOD=100000;
        vector<int> dist(MOD, -1);
        queue<int>q;
        dist[start]=0; q.push(start);
        while(!q.empty()){
            int u=q.front(); q.pop();
            if(u==endv){ cout<<dist[u]<<"\n"; return; }
            for(int x:arr){
                long long v = (1LL*u * x) % MOD;
                if(dist[v]==-1){ dist[v]=dist[u]+1; q.push(v); }
            }
        }
        cout<<"-1\n";
    }
};
