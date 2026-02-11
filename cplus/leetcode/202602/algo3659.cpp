#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.8 相邻不同
class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        // 自行解答 
        unordered_map<int, int> cnt;
        if (nums.size() % k) return false;
        int grps = nums.size() / k;
        for (auto & v: nums) {
            cnt[v] ++; if (cnt[v] > grps) return false;
        }
        return true;
    }
};