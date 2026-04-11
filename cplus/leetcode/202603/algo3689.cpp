#include <bits/stdc++.h>
using namespace std;

// 五、思维题 - 5.2 脑筋急转弯
class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        return 1LL * (ranges::max(nums) - ranges::min(nums)) * k;
    }
};