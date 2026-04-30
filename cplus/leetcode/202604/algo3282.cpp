#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    long long findMaximumScore(vector<int>& nums) {
        long long ans = 0; int i = 0, j = 1, n = nums.size();
        while (j < n) {
            while (j<n-1 && nums[i]>=nums[j]) j++;  // j 不能等于 n
            ans += 1LL * nums[i] * (j - i);
            i = j; j = i + 1;
        }
        return ans;
    }
};