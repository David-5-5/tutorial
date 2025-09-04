#include <bits/stdc++.h>
using namespace std;

// 回溯 - 4.3 划分型回溯
class Solution {
public:
    int maxUniqueSplit(string s) {
        // 自行解答
        unordered_set<string> splits; int ans = 0;

        auto dfs = [&](this auto&& dfs, int i) -> void {
            if (i == s.length()) ans = max(ans, (int)splits.size());

            for (int j=i+1; j<=s.length(); ++j) {
                string seg = s.substr(i, j-i);
                if (!splits.count(seg)) {
                    splits.insert(seg);
                    dfs(j);
                    splits.erase(seg);
                }
            }
        };
        dfs(0);
        return ans;
    }
};