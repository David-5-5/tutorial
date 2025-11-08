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

    int catMouseGame3(vector<vector<int>>& graph) {
        int n = graph.size();
        int dp[n][n][2];
        // degree 标记当前玩家必败的数量，当degree ==0 表明必败
        int degree[n][n][2];
        memset(dp, 0, sizeof(dp));
        memset(degree, 0, sizeof(degree));
        
        // initial degree
        for (int m=0; m<n; ++m) for (int c=0; c<n; ++c) {
            degree[m][c][0] = graph[m].size();  // mouse turn
            degree[m][c][1] = graph[c].size();  // cat turn
            for (auto x : graph[c]) if (x == 0) {
                degree[m][c][1] --; break;
            }
        }
        
        vector<vector<int>> q;
        for (int cat=0; cat<n; ++cat) for (int t=0; t<2; ++t) {
            dp[0][cat][t] = 1;  q.push_back({0, cat, t});
            
            if(cat) {dp[cat][cat][t] = 2; q.push_back({cat, cat, t});} 
        }


        while (q.size()) {
            vector<vector<int>> tmp;
            for (auto status: q) {
                int mouse = status[0], cat = status[1], turn = status[2];
                int result = dp[mouse][cat][turn];

                if (turn == 0) { // cur mouse，prevoius cat
                    for (auto prev_cat: graph[cat]){
                        if (prev_cat == 0 || dp[mouse][prev_cat][1]!=0) continue;
                        if (result == 2) { // good to cat
                            dp[mouse][prev_cat][1] = 2;
                            tmp.push_back({mouse, prev_cat, 1});
                        } else {
                            degree[mouse][prev_cat][1] --;
                            if (degree[mouse][prev_cat][1] == 0) {
                                dp[mouse][prev_cat][1] = 1;
                                tmp.push_back({mouse, prev_cat, 1});
                            }
                        }
                    }
                } else {
                    for (auto prev_m: graph[mouse]) {
                        if (dp[prev_m][cat][0]!=0) continue;
                        if (result == 1) { // good to mouse
                            dp[prev_m][cat][0] = 1;
                            tmp.push_back({prev_m, cat, 0});
                        } else {
                            degree[prev_m][cat][0] --;
                            if (degree[prev_m][cat][0] == 0) {
                                dp[prev_m][cat][0] = 2;
                                tmp.push_back({prev_m, cat, 0});
                            }
                        }
                    }
                }
            }

            q = move(tmp);
        }
        return dp[1][2][0];
    }    

};
