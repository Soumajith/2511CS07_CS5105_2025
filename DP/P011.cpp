class Solution {
public:
    int solve(int i, int j, int n, vector<vector<int>> &matrix, vector<vector<int>> &dp){
        if( j < 0 || j >= n) return 1e9;
       
        if(i == 0){
            return matrix[i][j];
        }

        if(dp[i][j] != -1) return dp[i][j];

        int down = solve(i-1, j, n, matrix, dp);
        int diagonalLeft = solve(i-1, j-1, n, matrix, dp);
        int diagonalRight = solve(i-1, j+1, n, matrix, dp);

        return dp[i][j] = matrix[i][j] + min({down, diagonalLeft, diagonalRight});
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        for(int j = 0; j < n; j++){
            dp[0][j] = matrix[0][j];
        }

        for(int i = 1; i < n; i++){
            for(int j = 0; j < n; j++){
                int up = matrix[i][j] +  dp[i-1][j];
                int diagonalLeft = 1e9;
                int diagonalRight = 1e9;
                if(j > 0) diagonalLeft =  matrix[i][j] + dp[i-1][j-1];
                if(j < n-1) diagonalRight =  matrix[i][j] + dp[i-1][j+1];

                dp[i][j] = min({up,diagonalLeft, diagonalRight});
            }

        }

        int mini = 1e9;

        for(int i = 0; i < n; i++){
            mini = min(mini, dp[n-1][i]);
        }

        return mini;
    }
};