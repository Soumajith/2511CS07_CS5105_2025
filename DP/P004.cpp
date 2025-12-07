class Solution {
public:
    int solve(int ind, vector<int> &nums, vector<int> &dp){
        if(ind < 0){
            return 0;
        }

        if(dp[ind] != -1) return dp[ind];

        int notTake = solve(ind-1, nums, dp);
        int take = nums[ind] + solve(ind-2, nums, dp);

        return dp[ind] = max(take, notTake);
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        
        if (n == 1) return nums[0];
        
        vector<int> dp(n,-1);

        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for(int i = 2; i < n; i++){
            int notTake = dp[i-1];
            int take = 
            nums[i] + dp[i-2];

            dp[i] = max(notTake, take);
        }
        return dp[n-1];
    }
};