#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.2 子集型回溯
class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        // 自行解答，遍历
        int m = requests.size(), ans = 0;

        vector<int> cnt(n);
        auto check = [&](int mask) -> int {
            // 参考题解 - 两个优化
            int cur = __builtin_popcount(mask);
            if (cur <= ans) {       
                return 0;   // 优化1 剪枝
            }
        
            fill(cnt.begin(), cnt.end(), 0);    // 优化2 复用同一vector
            for (int i=0; i<m; ++i) if((mask >> i) & 1) {
                --cnt[requests[i][0]];
                ++cnt[requests[i][1]];
            }

            for (auto v:cnt) if (v != 0) return 0;
            return cur;
        };

        for (int mask = 0; mask<(1<<m); ++mask) {
            ans = max(ans, check(mask));
        }
        return ans;  
  
        
    }
};