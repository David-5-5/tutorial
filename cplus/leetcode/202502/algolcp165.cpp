#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 最优划分
class Solution {
public:
    int crackNumber(int ciphertext) {
        // 自行解答，同 91
        string s = to_string(ciphertext);
        int n = s.size();

        vector<int> memo(n, -1);
        auto dfs = [&] (this auto&& dfs, int i) {
            if (i == n) return 1;

            auto& res = memo[i];
            if (res != -1) return res;
            
            res = 0;
            res += dfs(i+1);
            if (i+2 <= n && stoi(s.substr(i, 2)) >= 10 &&
                stoi(s.substr(i, 2)) <= 25) res += dfs(i+2);
            
            return res;
        };

        return dfs(0);    
    }
};