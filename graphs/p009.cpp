#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int sz = roads.size();
        vector<pair<int,int>> adj[n];
        for(int i = 0; i < sz; i++){
            adj[roads[i][0]].push_back({roads[i][1], roads[i][2]});
            adj[roads[i][1]].push_back({roads[i][0], roads[i][2]});
        }

        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        vector<long long> dist(n, LLONG_MAX);
        vector<int> ways(n, 0);

        int MOD = (int)(1e9+7);

        dist[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});

        while(!pq.empty()){
            auto [dis, node] = pq.top();
            pq.pop();

            if(dis > dist[node]) continue; // skip outdated states

            for(auto [adjNode, wt] : adj[node]){
                if(dis + wt < dist[adjNode]){
                    dist[adjNode] = dis + wt;
                    ways[adjNode] = ways[node]; // inherit path count
                    pq.push({dist[adjNode], adjNode});
                }
                else if(dis + wt == dist[adjNode]){
                    ways[adjNode] = (ways[adjNode] + ways[node]) % MOD;
                }
            }
        }

        return ways[n-1] % MOD;
    }
};
