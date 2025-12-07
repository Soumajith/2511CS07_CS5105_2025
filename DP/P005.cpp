class Solution {
public:
    int solve1(int n, vector<int> &nums){
        if(n == 1) return nums[0];
        int prev = nums[0];
        int curr = max(nums[0], nums[1]);

        for(int i = 2; i < n; i++){
            int notTake = curr;
            int take = nums[i] + prev;
            prev = curr;
            curr = max(take, notTake);
        }

        return curr;
    }
    int solve2(int n, vector<int> &nums){
        if(n == 1) return nums[1];
        int prev = nums[1];
        int curr = max(nums[1], nums[2]);

        for(int i = 2; i < n; i++){
            int notTake = curr;
            int take = nums[i+1] + prev;
            prev = curr;
            curr = max(take, notTake);
        }

        return curr;
    }
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums[0];
       
        int maxi = solve1(n-1, nums);
        maxi =max(maxi, solve2(n-1, nums));
        return maxi;

    }
};