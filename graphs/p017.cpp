#include <bits/stdc++.h>
using namespace std;

class Solution {

public:
    void bfs(vector<vector<int>> &grid, vector<vector<bool>> &vis, int i, int j){
        int delR[] = {-1, 1, 0, 0};
        int delC[] = {0, 0, -1, 1};
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int,int>> q;
        q.push({i, j});

        vis[i][j] = true;
    
        while(!q.empty()){
            auto [x, y] = q.front();
            q.pop();

            for(int i = 0; i < 4; i++){
                int nrow = x+delR[i];
                int ncol = y+delC[i];

                if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && !vis[nrow][ncol] && grid[nrow][ncol] == 1){
                    vis[nrow][ncol] = 1;
                    q.push({nrow, ncol});
                }
            }
        }
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<bool>> vis(n, vector<bool>(m, false));

        for(int i = 0; i < n; i++){
            if(!vis[i][0] && grid[i][0] == 1)
                bfs(grid, vis, i, 0);
            if(!vis[i][m-1]  && grid[i][m-1] == 1){
                bfs(grid, vis, i, m-1);
            }
        }

        for(int i = 0; i < m; i++){
            if(!vis[0][i] && grid[0][i] == 1)
                bfs(grid, vis, 0, i);

            if(!vis[n-1][i] && grid[n-1][i] == 1)
                bfs(grid, vis, n-1, i);
        }

        int cnt = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(!vis[i][j] && grid[i][j] == 1){
                    cnt++;
                }
            }
        }

        return cnt;
    }
};