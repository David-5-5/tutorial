#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最优划分
class Solution {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        
        int n = s.size();

        vector<int> memo(n, -1);
        auto dfs = [&](this auto &&dfs, int i) -> int {
            if (i == n) return 0;

            auto& res = memo[i];
            if (res != -1) return res;
            
            res = INT_MAX;
            for (auto& word : dictionary) {
                if (word.size() > n - i) continue;
                // cout << s.substr(i, word.size()) << endl;
                if (s.substr(i, word.size()) == word)
                    res = min(res, dfs(i+word.size()));
            }
            
            res = min(res, 1 + dfs(i+1));
            return res;
        };
        
        return dfs(0);   
    }
};