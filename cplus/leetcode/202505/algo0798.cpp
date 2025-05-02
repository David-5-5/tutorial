#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 2.1 一维差分（扫描线）
class Solution {
public:
    int bestRotation(vector<int>& nums) {
        unordered_map<int, int> cnt;
        int score = 0, k = 0, n = nums.size();
        
        for (int i=0; i<n; ++i) {
            if (i>=nums[i]) score += 1;
            cnt.count(i-nums[i])?cnt[i-nums[i]] ++:cnt[i-nums[i]] = 1;
        }

        int res = score;
        for (int i=0; i<n; ++i) {
            if (i-nums[i] < 0 && n - 1 -nums[i] > 0) res += 1;
            cnt[i-nums[i]] --;
            res -= cnt[i];
            cnt.count((n - 1 -nums[i]))?cnt[n - 1 -nums[i]] ++:cnt[n - 1 -nums[i]] = 1;

            if (res > score) {
                score = res;
                k = i;
            }
        }

        return k;
    }
};