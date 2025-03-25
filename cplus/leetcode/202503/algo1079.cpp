#include <bits/stdc++.h>
using namespace std;

// 动态规划 -  多维 DP
class Solution {
public:
    int numTilePossibilities(string tiles) {
        int n = tiles.length();
        unordered_map<char, int> count;
        set<char> tset;
        for (char ch : tiles) {
            count[ch] ++;
            tset.insert(ch);
        }

        auto dfs = [&](this auto&& dfs, int i) -> int {
            if (i == 0) return 1;

            int res = 1;     // 每个长度都计数
            for (auto& ch : tset) {
                if (count[ch]) {
                    count[ch] --;
                    res += dfs(i-1);
                    count[ch] ++;
                }
            }
            return res;
        };

        return dfs(n) - 1;

    }
};