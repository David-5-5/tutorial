#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 9.3 旅行商问题
class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();

        vector<vector<int>> eq(n, vector<int>(n, 0));
        for (int i=0; i<n; ++i) for (int j=0; j<n; ++j) {
            if (i==j) continue;
            int is = words[i].size(), js = words[j].size();
            int len = min(is, js) - 1;
            for (int l= len; l; l--) {
                if (words[i].substr(is-l) == words[j].substr(0, l)){
                    eq[i][j] = l;
                    break;
                }
            }
        }
        
        const int mx = 241;
        vector<int> next(n+1, -1);
        vector<vector<int>> memo(1<<n, vector<int>(n+1, mx));
        auto dfs = [&] (this auto&& dfs, int state, int i) ->int {
            if (state == 0) return 0;

            auto& res = memo[state][i];
            if (res != mx) return res;
            
            for (int j=0; j<n; ++j) {
                if (state >> j & 1) {
                    int value = (int)words[j].size()-(i!=n?eq[i][j]:0) + dfs(state - (1<<j), j);
                    if (value < res) {
                        next[n] = j;
                        res = value;
                    }
                }
            }
            return res;
        };
        int ans = dfs((1<<n)-1, n);


        return to_string(ans);

    }


};

