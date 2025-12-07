class Solution {
public:
    int solve(int i, int j, string &p, string &s, vector<vector<int>>&dp){
        if(i == 0 && j == 0) return true;
        if(i == 0 && j > 0) return false;
        if(j == 0 && i > 0){
            for(int ii = 1; ii <= i; ii++){
                if(s[ii - 1] != '*') return false;
            }
            return true;
        }

        if(dp[i][j] != -1) return dp[i][j];

        if(s[i-1] == p[j-1] || s[i-1] == '?') return dp[i][j] = dp[i-1][j-1];
        else if(s[i-1] == '*') return dp[i][j] = dp[i-1][j] | dp[i][j-1];
        
        return dp[i][j] = false;
    }
    bool isMatch(string s, string p) {
        int n = p.size();
        int m = s.size();
        // vector<vector<int>>dp(n, vector<int>(m, -1));
        // solve(n-1, m-1, s, p, dp);
        // return dp[n-1][m-1];

        vector<vector<bool>>dp(n+1, vector<bool>(m+1, 0));
        dp[0][0] = true;
        for(int j = 1; j <= m; j++) dp[0][j] = false;

        for(int i = 1; i <= n; i++){
            int flag = true;
            for(int ii = 1; ii <= i; ii++){
                if(p[ii -1] != '*') flag = false;
            }
            dp[i][0] = flag;
        }

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(p[i-1] == s[j-1] || p[i-1] == '?') dp[i][j] = dp[i-1][j-1];
                else if(p[i-1] == '*') dp[i][j] = dp[i][j-1] | dp[i-1][j];
                else dp[i][j] = false;
            }
        }
        return dp[n][m];
        
    }
};