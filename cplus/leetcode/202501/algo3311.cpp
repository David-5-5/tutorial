#include <bits/stdc++.h>
using namespace std;

// 贪心专题 - 构造题
class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        // 自行解答，太繁琐了，应该可以优化，但是比赛时候，在很短的时间内很难完成
        vector<vector<int>> g(n);
        for (auto e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        unordered_map<int, int> degree;
        for (int i=0; i<n; i++) 
            degree[g[i].size()] = i; // 保留不同degree的一个顶点，后续从该顶点dfs
        
        int row = 3; // 多行
        if (degree.count(1)) row = 1;
        else if (degree.count(4) == 0) row = 2;

        if (row == 1) {
            vector<vector<int>> ans(1, vector<int>(n));
            ans[0][0] = degree[1];
            for (int i=1; i<n; i++) {
                for (auto v: g[ans[0][i-1]]) {
                    if (i<2 || v != ans[0][i-2])
                        ans[0][i] = v;
                }
            }
            return ans;
        } else if (row == 2) {
            vector<bool> vis(n);
            vector<vector<int>> ans(2, vector<int>(n/2));
            ans[0][0] = degree[2], vis[ans[0][0]] = true;
            
            for (auto v : g[degree[2]])
                if (g[v].size() == 2) {
                    ans[1][0] = v, vis[v] = true;
                    break;
                }

            for (int j=1; j<n/2; j++){
                for (int i=0; i<2; i++) {
                    for (auto v:g[ans[i][j-1]])
                        if (!vis[v]) {
                            vis[v] = true; ans[i][j] = v;
                            break;
                        }
                }
            }
            return ans;
        }
        vector<bool> vis(n);
        vis[degree[2]] = true;
        vector<int> frow = {degree[2]}; // 第一行

        while (frow.size() == 1 || g[frow.back()].size() != 2) {
            for (auto v : g[frow.back()]) {
                if (g[v].size() != 4 && !vis[v]) {
                    vis[v] = true, frow.push_back(v);
                    break;
                }
            }
        }
        vector<vector<int>> ans(n/frow.size(), vector<int>(frow.size()));
        ans[0] = frow;
        for (int i = 1; i<ans.size(); i++) { // 第一列
            for (auto v:g[ans[i-1][0]]) {
                if (g[v].size() != 4 && !vis[v]) {
                    vis[v] = true, ans[i][0] = v;
                    break;
                }
            }
        }
        for (int j=1; j<ans[0].size(); j++){
            for (int i=1; i<ans.size(); i++) {
                for (auto v:g[ans[i][j-1]])
                    if (!vis[v]) {
                        vis[v] = true; ans[i][j] = v;
                        break;
                    }
            }
        }

        return ans;
    }
};