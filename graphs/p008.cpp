#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();

        priority_queue<pair<int, pair<int, int >> , vector<pair<int, pair<int, int >>>, greater<pair<int, pair<int, int>>>> pq;

        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

        dist[0][0] = 0;
        pq.push({0, {0,0}});
        int drow[] = {-1, 0, 1, 0};
        int dcol[] = {0, -1, 0, 1};

        while(!pq.empty()){
            auto [diff, g] = pq.top();
            pq.pop();
            int r = g.first;
            int c = g.second;
            if(r == n-1 && c == m-1) return diff;

            for(int i = 0; i < 4; i++){
                int nrow = r + drow[i];
                int ncol = c + dcol[i];

                if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m ){
                    int newDiff = max(diff, abs(heights[nrow][ncol] - heights[r][c]));

                    if(newDiff < dist[nrow][ncol]){
                        dist[nrow][ncol] =newDiff;
                        pq.push({newDiff, {nrow, ncol}});
                    }
                }

            }
        }

        return 0;

    }
};