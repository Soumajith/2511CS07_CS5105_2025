class Solution {
public:
    int solve(int i, int j, vector<vector<int>> &dp){

        if(i == 0 && j == 0){
            return dp[i][j] = 1;
        }
        if(i < 0 || j < 0){
            return 0;
        }

        if(dp[i][j] != -1) return dp[i][j];

        int right = solve(i, j-1, dp);
        int up = solve(i-1, j, dp);

        return dp[i][j] = up+right;
    }
    int uniquePaths(int m, int  n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        // solve(m-1, n-1, dp);

        // base case
        dp[0][0] = 1;


        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(i == 0 && j == 0) dp[0][0] = 1;                
                else{
                    int right = 0;
                    int up = 0;
                    if(j > 0) right = dp[i][j-1];
                    if(i > 0) up = dp[i-1][j];
                    dp[i][j] = right + up;
                }
            }
        }

        return dp[m-1][n-1] ;
    }
};