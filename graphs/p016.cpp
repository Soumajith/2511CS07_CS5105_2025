#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    void dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, int i, int j, int delrow[], int delcol[]){
        visited[i][j] = true;
        int n = board.size();
        int m = board[0].size();

        for(int k = 0; k < 4; k++){
            int nrow = delrow[k] + i;
            int ncol = delcol[k] + j;

            if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m 
               && !visited[nrow][ncol] && board[nrow][ncol] == 'O'){
                dfs(board, visited, nrow, ncol, delrow, delcol);
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int drow[] = {-1, 1, 0, 0};
        int dcol[] = {0, 0, 1, -1};

        for(int i = 0; i < n; i++){
            if(board[i][0] == 'O' && !visited[i][0]){
                dfs(board, visited, i, 0, drow, dcol);
            }
            if(board[i][m-1] == 'O' && !visited[i][m-1]){
                dfs(board, visited, i, m-1, drow, dcol);
            }
        }

        for(int j = 0; j < m; j++){
            if(board[0][j] == 'O' && !visited[0][j]){
                dfs(board, visited, 0, j, drow, dcol);
            }
            if(board[n-1][j] == 'O' && !visited[n-1][j]){
                dfs(board, visited, n-1, j, drow, dcol);
            }
        }


        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(!visited[i][j] && board[i][j] == 'O'){
                    board[i][j] = 'X';
                }
            }
        }
    }
};
