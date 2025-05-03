#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        // 参考题解，技巧很强
        // 差分可以想到，但是结合 numOperations 就没有思路了
        unordered_map<int, int> cnt;
        map<int, int> diff;     // 数据域大的情况下使用 map 代替 vector
        
        for (auto& x : nums) {
            cnt[x] ++;
            diff[x-k] ++;
            diff[x];        // !!确保能遍历到 v!!，点睛之笔
            diff[x+k+1] --;
        }

        int ans = 0, sum = 0;
        for (auto& [x, c]:diff) {
            sum += c;
            // 结合 numOperations，计算 nums 中 x 的次数
            ans = max(ans, min(sum, cnt[x] + numOperations));
        }

        return ans;
    }
};