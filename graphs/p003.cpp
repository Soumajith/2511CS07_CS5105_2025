//  rotten oranges
// bfs 
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<pair<int,int>, int>> q; // (r , c), t

        vector<vector<int>> vis(n, vector<int>(m));
        int frsh = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m ; j++){
                if(grid[i][j] == 2){
                    q.push({{i,j}, 0});
                    vis[i][j] = 1;
                }

                if(grid[i][j] == 1){        
                    vis[i][j] = 0;
                    frsh++;
                }
            }
        }

        
        int tRow[] = {-1, 0, 1, 0};
        int tCol[] = {0, 1, 0, -1};
        int cnt = 0;
        int tm = 0;

        while(!q.empty()){
            auto [g , t] = q.front();
            int r = g.first;
            int c = g.second;

            q.pop();
            tm = max(tm, t);

            for(int i = 0; i < 4; i++){
                int nrow = r+tRow[i];
                int ncol = c+tCol[i];

                if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && 
                    vis[nrow][ncol] == 0 && grid[nrow][ncol] == 1){
                    
                    q.push({{nrow, ncol}, tm+1});
                    vis[nrow][ncol] = 1; 
                    cnt++;
                }
            }

            
        }
        if(cnt != frsh) return -1;

        return tm;
    }
};

// T.C. = NxM
// S.c. = NxM