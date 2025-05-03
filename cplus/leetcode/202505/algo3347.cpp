#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        unordered_map<int, int> cnt;
        map<int, int> diff;
        
        for (auto& x : nums) {
            cnt[x] ++;
            diff[x-k] ++;
            diff[x];        // !!确保能遍历到 v!!
            diff[x+k+1] --;
        }

        int ans = 0, sum = 0;
        for (auto& [x, c]:diff) {
            sum += c;
            ans = max(ans, min(sum, cnt[x] + numOperations));
        }

        return ans;
    }
};