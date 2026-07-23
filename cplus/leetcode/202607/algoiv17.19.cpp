#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> missingTwo(vector<int>& nums) {
        // 参考题解： nums 增加 1~n
        // x = x1 ^ x2，通过lowbit 将 nums 分为两类，
        // x1 和 x2 一定在不同的分类中，其他的元素都在同一分类，出现次数为 2，异或为 0

        // 自行思考的 x = x1 ^ x2，起初两数之和，但是无法解决问题。
        int n = nums.size() + 2;
        int x = 0; // x = x1 ^ x2
        for (int i=1; i<=n; i++) x ^= i;
        for (auto & v : nums) x ^= v;

        auto lb = x & -x;
        int x1 = 0, x2 = 0;
        for (auto & v : nums)
            if (lb & v) x1 ^= v;
            else x2 ^= v;
        for (int i=1; i<=n; i++)
            if (lb & i) x1 ^= i;
            else x2 ^= i;
        
        return {x1, x2};
    }
};