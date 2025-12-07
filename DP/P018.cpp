class Solution {
public:

    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);

        if((sum - target) < 0 || (sum-target) % 2 == 1 ) return 0;
        
        sum = (sum-target)/2;

        vector<vector<int>> dp(n, vector<int>(sum+1, 0));

        if(nums[0] == 0){
            dp[0][0] = 2;
        }
        else{
            dp[0][0] = 1;
        }

        if(nums[0] != 0 && nums[0] <= sum) dp[0][nums[0]] = 1;

        for(int i = 1; i < n; i++){
            for(int j = 0; j <= sum; j++){
                int notPick = dp[i-1][j];
                int pick = 0;
                if( j >= nums[i]) pick = dp[i-1][j-nums[i]];

                dp[i][j] = pick+notPick;
            }
        }

        return dp[n-1][sum];
    }
};