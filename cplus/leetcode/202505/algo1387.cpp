#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 其他
class Solution {
public:
    int getKth(int lo, int hi, int k) {
        // 自行解答

        unordered_map<int, int> memo;
        auto dfs = [&](this auto&& dfs, int x) -> int {
            if (x == 1) return 0;

            if (memo.count(x)) return memo[x];

            int res;
            if (x % 2) res = 1 + dfs(3 * x + 1);
            else res = 1 + dfs(x / 2);
            return memo[x] = res;
        };

        // 下面的写法很高级
        vector<int> nums(hi - lo + 1);
        iota(nums.begin(), nums.end(), lo);
        ranges::stable_sort(nums, {}, dfs);
        return nums[k - 1];  
    }
};
