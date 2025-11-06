#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 博弈论
class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        // 易理解 - OVERTIME - 需降维优化
        int n = graph.size();
        int memo[50][50][2*50*49]; 
        memset(memo, -1, sizeof(memo));
        
        auto dfs = [&](this auto&& dfs, int mouse, int cat, int step) -> int {

            if (mouse == 0) return 1;
            if (mouse == cat) return 2;
            if (step >= 2 * n * (n-1)) return 0;
            int& res = memo[mouse][cat][step%2];
            if (res != -1) return res;

            
            bool has_draw = false;
            if (step % 2 == 0) { // mouse
                
                for (auto v: graph[mouse]) {
                    int cur = dfs(v, cat, step+1);
                    if (cur == 1) return res = 1;
                    else if (cur == 0) has_draw = true;
                }
                return res = (has_draw)?0:2;
            } else {
                for (auto v: graph[cat]) {
                    if (v == 0) continue;
                    int cur = dfs(mouse, v, step+1);
                    if (cur == 2) return res = 2;
                    else if (cur == 0) has_draw = true;
                }
                return res = (has_draw)?0:1;
            }

        };

        return dfs(1, 2, 0);
    }

    int catMouseGame2(vector<vector<int>>& graph) {
        // 探测最大步数 - 机会主义
        int n = graph.size();
        int memo[50][50][5 * 50]; 
        memset(memo, -1, sizeof(memo));
        
        auto dfs = [&](this auto&& dfs, int mouse, int cat, int step) -> int {

            if (mouse == 0) return 1;
            if (mouse == cat) return 2;
            if (step >= 5 * n ) return 0;
            int& res = memo[mouse][cat][step];
            if (res != -1) return res;

            
            bool has_draw = false;
            if (step % 2 == 0) { // mouse
                
                for (auto v: graph[mouse]) {
                    int cur = dfs(v, cat, step+1);
                    if (cur == 1) return res = 1;
                    else if (cur == 0) has_draw = true;
                }
                return res = (has_draw)?0:2;
            } else {
                for (auto v: graph[cat]) {
                    if (v == 0) continue;
                    int cur = dfs(mouse, v, step+1);
                    if (cur == 2) return res = 2;
                    else if (cur == 0) has_draw = true;
                }
                return res = (has_draw)?0:1;
            }

        };

        return dfs(1, 2, 0);
    }    
};