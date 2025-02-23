#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 判定能否划分
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        
        int n = s.size();

        vector<int> memo(n, -1);
        auto dfs = [&](this auto &&dfs, int i) -> bool {
            if (i == n) return true;

            auto& res = memo[i];
            if (res != -1) return res;

            for (auto& word : wordDict) {
                if (word.size() > n - i) continue;
                // cout << s.substr(i, word.size()) << endl;
                if (s.substr(i, word.size()) == word && dfs(i + word.size()))
                    return res = true;
            }
            return res = false;
        };
        
        return dfs(0); 

    }
};