#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int f = 0, ssum = 0, n = nums.size();
        for (int i=0; i<n; i++) f += i * nums[i], ssum += nums[i];
        auto ans = f;

        for (int i=1; i<n; i++) {
            f += ssum - n * nums[n-i];
            ans = max(ans, f);
        }
        return ans;
    }
};