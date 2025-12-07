#include <bits/stdc++.h>
using namespace std;

int frogMinEnergy(const vector<int>& h) {
    int n = h.size();
    if (n <= 1) return 0;

    int prev2 = 0;                        
    int prev1 = abs(h[1] - h[0]);      

    for (int i = 2; i < n; ++i) {
        int oneStep = prev1 + abs(h[i] - h[i-1]);
        int twoStep = prev2 + abs(h[i] - h[i-2]);
        int cur = min(oneStep, twoStep);

        prev2 = prev1;
        prev1 = cur;
    }

    return prev1;
}
