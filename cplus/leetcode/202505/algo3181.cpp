#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.9 其他优化 DP
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        // 参考题解
        int m = ranges::max(rewardValues);
        sort(rewardValues.begin(), rewardValues.end());
        // 删除重复数据
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());

        bitset<100000> f{1};
        for (auto& v: rewardValues) {  
            int shift = f.size() - v;   // c++ 的位运算不好理解
            f |= f << shift >> (shift - v);
        }
        for (int i = 2 * m-1;; i--) {
            if (f.test(i)) return i;
        }

    }
};