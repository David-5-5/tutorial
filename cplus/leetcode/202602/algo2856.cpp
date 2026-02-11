#include <bits/stdc++.h>
using namespace std;

// 一、贪心策略 - 1.8 相邻不同
class Solution {
public:
    int minLengthAfterRemovals(vector<int>& nums) {
        // 自行解答 时间复杂度 O(N) 题单总结的问题2。 n - 2 * mx 即为所计算结果
        int n = nums.size(), mx = 0; unordered_map<int, int> cnt;
        for (auto& v : nums) {
            cnt[v] ++; 
            if (cnt[v] > mx) mx = cnt[v];
        }
        return n - 2 * min(n/2, n-mx);
    }

    int minLengthAfterRemovals(vector<int>& nums) {
        // 时间复杂度 O(logn)
    }
};