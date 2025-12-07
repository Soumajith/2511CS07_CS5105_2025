class Solution {
public:
    int solve(int i, int j, int n, vector<vector<int>> &grid, vector<vector<int>>&dp){
        if(dp[i][j] != -1) return dp[i][j];
        if(i == n-1){
            return grid[i][j];
        }

        int diagonal = grid[i][j] + solve(i+1, j+1, n, grid, dp);
        int down = grid[i][j] + solve(i+1, j, n, grid, dp);

        return dp[i][j] = min(diagonal, down);
    }
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<int> prev(n), curr(n);

        for(int i = 0; i < n; i++){
            prev[i] = triangle[n-1][i];
        }

        for(int i = n-2; i >= 0; i--){
            for(int j = i; j >= 0; j--){
                int up = triangle[i][j] + prev[j];
                int diagonal = INT_MAX;
                if(j <= i) diagonal = triangle[i][j] + prev[j+1];

                curr[j] = min(diagonal, up);
            }

            prev = curr;
        }

        return prev[0];

    }
};