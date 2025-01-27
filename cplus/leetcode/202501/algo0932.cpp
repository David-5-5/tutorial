#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<int> beautifulArray(int n) {
        unordered_map<int, vector<int>> memo;
        memo[1] = {1}; // 分治的递归边界

        function<vector<int>(int)> f = [&](int N) -> vector<int>  {
            if (memo.count(N)) return memo[N];

            vector<int> res;
            for (auto x: f((N+1)/2)) res.push_back(x*2-1);
            for (auto x: f(N/2)) res.push_back(x*2);
            
            return memo[N] = res;
        };

        return f(n);
    }
};