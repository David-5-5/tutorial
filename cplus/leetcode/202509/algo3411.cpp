#include <bits/stdc++.h>
using namespace std;

const int N = 1e1 + 1;
vector<int> prime_factors[N];

int init = [] {
    for (int i = 2; i < N; ++i) {
        if (prime_factors[i].empty()) { // 质数
            for (int j = i; j < N; j += i) {
                prime_factors[j].push_back(i);
            }
        }
    }
    return 0;
}();

// 数学算法 - 数论 - 1.8 互质
class Solution {
public:
    int maxLength(vector<int>& nums) {
        // 自行解答 进阶版，O(nlogU)
        // 题解使用 gcd + 滑动窗口的方案
        // 对于 nums.length 以及 nums[i] 取值 10^5 mul 整数乘法会越界
        // 本题的方案应该比较通用
        int ans = 2, l = 0, n = nums.size();
        unordered_map<int, int> prime_cnt;
        auto check = [&](int r) -> bool {
            for (auto p: prime_factors[nums[r]]) {
                if (prime_cnt[p]>1) return false;
            }

            return true;
        };

        for (int r=0; r<n; ++r) {
            for (auto p: prime_factors[nums[r]]) {
                prime_cnt[p] ++;
            }
            while (!check(r)) {
                for (auto p:prime_factors[nums[l]]) {
                    prime_cnt[p] --;
                }
                l ++;
            }
            ans = max(ans, r-l+1);
        }
        return ans;
    }
};