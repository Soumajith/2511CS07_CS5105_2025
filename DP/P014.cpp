class Solution {
public:
    bool canPartition(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        
        if(sum & 1 || n == 1) return false;
        sum = sum/2;
        
        vector<vector<bool>> dp(n, vector<bool> (sum+1, false));
        
        for(int i = 0; i < n; i++){
            dp[i][0] = true;
        }
        dp[0][nums[0]] = true;

        for(int i = 1; i < n; i++){
            for(int j = 1; j <= sum; j++){
                bool notTake = dp[i-1][j];
                bool take = false;
                if(j >= nums[i]) take = dp[i-1][j-nums[i]];

                dp[i][j] = notTake || take;
            }
        }

        return dp[n-1][sum];
    }
};