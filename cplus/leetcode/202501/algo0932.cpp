#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<int> beautifulArray(int n) {
        // 参考题解 分治，思维难度较高
        unordered_map<int, vector<int>> memo;
        memo[1] = {1}; // 分治的递归边界

        function<vector<int>(int)> f = [&](int N) -> vector<int>  {
            if (memo.count(N)) return memo[N];

            vector<int> res;
            // 题目的要求，隐含在分治的策略中，分成奇数和偶数两部分
            // a[k] * 2 = a[i] + a[j] 其中 a[i] 为奇数 a[j] 为偶数
            // 确保上式不成立；
            // 同时两个满足该条件数组合并后，仍满足条件
            for (auto x: f((N+1)/2)) res.push_back(x*2-1); // 奇数
            for (auto x: f(N/2)) res.push_back(x*2);       // 偶数
            
            return memo[N] = res;
        };

        return f(n);
    }
};