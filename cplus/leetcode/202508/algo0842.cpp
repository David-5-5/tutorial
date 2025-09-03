#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.3 划分型回溯
class Solution {
public:
    vector<int> splitIntoFibonacci(string num) {
        // 自行解答 - c++需要处理整数越界的问题。
        vector<int> ans, path;

        auto dfs = [&](this auto&& dfs, int i) -> void {
            
            if (i == num.length()) {
                if (path.size()>2) ans = path;
                return;
            }
            long long cur = 0;

            for (int j=i; j<num.length(); ++j) {
                cur = cur * 10 + (num[j] - '0');
                if (cur > INT_MAX) break;
                int n = path.size();
                
                if (n<2 || (long)path[n-1]+path[n-2] == cur) {
                    path.push_back(cur);
                    dfs(j+1);
                    path.pop_back();
                }
                if (cur == 0) break;    // 无前导零
            }
        };
        dfs(0);
        return ans;
    }
};