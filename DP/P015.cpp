#include <bits/stdc++.h>
using namespace std;


class Solution {

  public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        vector<vector<bool>> dp(n, vector<bool> (sum + 1, false));

        for(int i = 0; i < n; i++){
            dp[i][0] = true;
        }

        dp[0][nums[0]] = true;


        for(int i = 1; i < n; i++){
            for(int j = 1; j <= sum; j++){
                bool notTake = dp[i-1][j];
                bool take = false;
                if(j >= nums[i]) take = dp[i-1][j - nums[i]];

                dp[i][j] = notTake || take;
            }
        }
        
        
        int mini = INT_MAX;
        for(int i = 0; i <= sum/2; i++){
            if(dp[n-1][i] == true)
                mini = min(mini, abs((sum - i) - i));
        }

        return mini;

    }
};