#include <bits/stdc++.h>
using namespace std;

long long ninjaTraining(const vector<vector<int>>& points) {
    int n = points.size();
    if (n == 0) return 0;
    if (n == 1) {
        return max({ (long long)points[0][0], (long long)points[0][1], (long long)points[0][2] });
    }


    long long prev[3];
    prev[0] = points[0][0];
    prev[1] = points[0][1];
    prev[2] = points[0][2];

    for (int day = 1; day < n; ++day) {
        long long cur[3];

        cur[0] = points[day][0] + max(prev[1], prev[2]);

        cur[1] = points[day][1] + max(prev[0], prev[2]);

        cur[2] = points[day][2] + max(prev[0], prev[1]);


        prev[0] = cur[0];
        prev[1] = cur[1];
        prev[2] = cur[2];
    }

    return max({ prev[0], prev[1], prev[2] });
}
