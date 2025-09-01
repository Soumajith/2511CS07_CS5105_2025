#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();

        if(grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;

        queue<pair<int, pair<int,int>>> q;
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        dist[0][0] = 1;
        q.push({1, {0, 0}});
        int drow[] = {-1, 0, 1, 0, -1, 1, -1, 1};
        int dcol[] = {0, -1, 0 , 1, -1, 1, 1, -1};


        while(!q.empty()){
            auto [dis, cell] = q.front();
            q.pop();
            int r = cell.first;
            int c = cell.second;

            for(int i = 0; i < 8; i++){
                int nrow = r+drow[i];
                int ncol = c+dcol[i];

                if(nrow < n && nrow >= 0 && ncol < n && ncol >= 0 && grid[nrow][ncol] == 0 &&
                    1+dis < dist[nrow][ncol]){
                        dist[nrow][ncol] = 1+dis;
                        if(nrow == n-1 && ncol == n-1) return dis+1;
                        q.push({dis+1, {nrow, ncol}});
                } 
            }
        }

        return -1;

    }
};