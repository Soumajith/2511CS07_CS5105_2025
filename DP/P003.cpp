class Solution {
public:
    int solve(vector<int> &nums, vector<vector<int>> &dp, int ind, int jumps){
        if(ind >= nums.size() - 1){
            return jumps;
        }
        if(dp[ind][jumps] != -1) return dp[ind][jumps];


        int mini = INT_MAX;
        for(int i = 1; i <= nums[ind]; i++){
            mini = min(mini, solve(nums, dp, ind+i, jumps+1));
        }

        return dp[ind][jumps] = mini;
    }
    int jump(vector<int>& nums) {
        
        
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));

        int jumps = solve(nums, dp, 0, 0);

        return jumps;    

        // tabulation
        int jumps = 0;
        int l = 0, r = 0;
        int n = nums.size();
        while(r < n-1){
            int farthest = 0;
            for(int ind = l; ind <= r; ind++){
                farthest = max(ind+nums[ind], farthest);
            }

            l = r+1;
            r = farthest;
            jumps++;
        }

        return jumps;
    }
};