// 01 matrix
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

class Solution {
  public:
    // Function to find distance of nearest 1 in the grid for each cell.
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        
        queue<pair<pair<int,int> , int>> q;
        vector<vector<int>> vis(n, vector<int>(m));
        vector<vector<int>> dis(n, vector<int>(m));
        
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == 1){
                    q.push({{i,j} , 0});
                    vis[i][j] = 1;
                }
                else{
                    vis[i][j] = 0;
                }
            }
        }
        
        
        int dRow[] = {-1, 0, 1, 0};
        int dCol[] = {0, -1, 0, 1};
        
        while(!q.empty()){
            auto [g, d] = q.front();
            q.pop();
            int r = g.first;
            int c = g.second;
            
            
            for(int i = 0; i < 4; i++){
                int nrow = r+dRow[i];
                int ncol = c+dCol[i];
                
                if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && vis[nrow][ncol] == 0){
                    q.push({{nrow, ncol}, d+1});
                    vis[nrow][ncol] = 1;
                    dis[nrow][ncol] = d+1;
                }
            }
        }
        
        
        return dis;
    }
};