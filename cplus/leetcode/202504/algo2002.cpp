#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int maxProduct(string s) {
        int n = s.length();
        
        vector<int> memo(1<<n, -1);
        auto is_pal = [&](int mask) -> bool {
            if (memo[mask]!=-1) return memo[mask];

            vector<int> ids;
            for (int i=0; i<n; ++i) 
                if (mask >> i & 1) ids.push_back(i);
            
            int m = ids.size();
            for (int i=0; i<m/2; i++){
                if (s[ids[i]] != s[ids[m-1-i]]) return memo[mask]=0;
            }
            return memo[mask]=1;
        };

        int tot = (1 << n) - 1, ans = 1;
        for (int first = 1; first <= tot/2; ++first) {
            int second = tot - first;

            int f_l = 1, s_l = 1;
            int mask = first;
            while (mask) {
                if (is_pal(mask)) f_l = max(f_l, __builtin_popcount(mask));
                mask = (mask-1) & first;
            }

            mask = second;
            while (mask) {
                if (is_pal(mask)) s_l = max(s_l, __builtin_popcount(mask));
                mask = (mask-1) & second;
            }
            ans = max(ans, f_l*s_l);
            
        }

        return ans;

    }
};