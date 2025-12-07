#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int countPartitions(vector<int>& arr, int d) {
        // Code here
        
        int n = arr.size();
        int sum = accumulate(arr.begin(), arr.end(), 0);
        
        if( (sum - d)  <  0 ||  (sum - d) % 2 == 1) return 0;
        
        sum = (sum - d)/2;
 
        // vector<vector<int>> dp(n, vector<int>(sum+1, 0));
        
        vector<int> prev(sum+1, 0) , curr(sum+1, 0);
        
        if(arr[0] == 0){
            prev[0] = 2;
        }
        else{
            prev[0] = 1;
        }
        
        if(arr[0] != 0 && arr[0] <= sum){
            prev[arr[0]] = 1;
        }
        
        for(int i = 1; i < n; i++){
            for(int j = 0; j <= sum; j++){
                int notTake = prev[j];
                int take = 0;
                
                if(j >= arr[i]) take = prev[j-arr[i]];
                
                curr[j] = take + notTake;
            }
            prev = curr;
        }
        
        
        return prev[sum];
        
    }
};