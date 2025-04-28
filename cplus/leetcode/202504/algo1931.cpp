#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.5 其他状压 DP
class Solution {
public:
    int colorTheGrid(int m, int n) {
        // 自行解答，参考 1411
        const int mod = 1e9 + 7;
        vector<int> types={0,1,2};
        for (int i=1; i<m; i++) {
            vector<int> tmp;
            for (auto &p : types) {
                if (p%3 != 0) tmp.push_back(p*3);
                if (p%3 != 1) tmp.push_back(p*3 + 1);
                if (p%3 != 2) tmp.push_back(p*3 + 2);
            }
            types = tmp;
        }
        
        int state = pow(3, m), k = types.size();

        vector<vector<int>> relate(state, vector<int>(state));
        for (int i=0; i<k; ++i) for (int j=0;j<k; ++j) {
            int u = types[i], v = types[j];
            bool validate = true;
            int div = 1;
            for (int x=0; x<m; x++) {
                if (u/div % 3 == v/div %3) {
                    validate = false;
                    break;
                }
                div *= 3;
            }
            if (validate) relate[u][v] = 1;
        }

        vector<vector<int>> memo(n, vector<int>(state+1, -1));  // 与 1411 的不同
        auto dfs = [&](this auto&& dfs, int i, int prev) -> int {
            if (i == n) return 1;

            auto& res = memo[i][prev];
            if (res != -1) return res;
            
            res = 0;
            for (auto& v: types) 
                if (prev == state || relate[prev][v]) res = ((long)res + dfs(i+1, v)) % mod;
            
            return res;
        };

        return dfs(0, state); // 初始为 0 时，当 m = 1，0是一个合法数
    }
};