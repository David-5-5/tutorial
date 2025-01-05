#include <bits/stdc++.h>
using namespace std;

// 周赛 379
class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        if (k == 26) return 1;
        unordered_map<long long, int> memo;

        function<int(int, int, bool)> dfs = [&](int i, int mask, bool changed) -> int {
            if (i == s.size()) return 1;

            long long argMask = (long long) i << 32 | mask << 1 | changed;
            // 两种写法
            // if (memo.count(argMask)) return memo[argMask];
            auto it = memo.find(argMask);
            if (it != memo.end()) return it->second;
            
            int res = 0;
            // don't change i 
            if (__builtin_popcount(mask | 1 << (s[i]-'a')) > k) 
                res = dfs(i+1, 1 << (s[i]-'a'), changed) + 1;
            else res = dfs(i+1, mask | 1 << (s[i]-'a'), changed);

            // change i
            if (!changed) {
                for (int ch=0; ch<26; ch++) {
                    if (__builtin_popcount(mask | 1 << ch) > k) 
                        res = max(res, dfs(i+1, 1 << ch, true) + 1);
                    else res = max(res, dfs(i+1, mask | 1 << ch, true));
                }
            }
            
            return memo[argMask] = res;
        };

        return dfs(0,0,false);    

    }
};