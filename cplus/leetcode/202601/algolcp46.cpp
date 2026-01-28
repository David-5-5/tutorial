#include <bits/stdc++.h>
using namespace std;

// 数学算法 - 七、杂项 7.8 其他
class Solution {
public:
    vector<int> volunteerDeployment(vector<int>& finalCnt, long long totalNum, vector<vector<int>>& edges, vector<vector<int>>& plans) {
        // 参考题解 最终 场馆 0 为 x， val = k * x  + b 设置 coeffs 记录 每个场馆的 k, b
        // coeff的初始值: coeffs[0][0] = 1, coeffs[0][1] = 0
        //            i>0 情况下 coeffs[i][0] = 1, coeffs[i][1] = finalCnt[i-1]
        // 学习了如何解方程
        int n = finalCnt.size() + 1, m = plans.size();
        vector<vector<int>> g(n);
        for (auto& e:edges) {
            g[e[0]].emplace_back(e[1]); g[e[1]].emplace_back(e[0]);
        }

        vector<vector<int>> coef(n, {0, 0}); coef[0][0] = 1;
        for (int i=1; i<n; ++i) coef[i][1] = finalCnt[i-1];

        for (int i=m-1; i>=0; --i) {
            auto u = plans[i][1], idx = plans[i][0];
            if (idx == 1) {
                coef[u][0] *= 2; coef[u][1] *= 2;
            } else if (idx == 2) {
                for (auto v: g[u]) {
                    coef[v][0] -= coef[u][0]; coef[v][1] -= coef[u][1];
                }
            } else {
                for (auto v: g[u]) {
                    coef[v][0] += coef[u][0]; coef[v][1] += coef[u][1];
                }
            }
        }
        long long k = 0, b = 0;
        for (auto c: coef) {
            k += c[0], b += c[1];
        }

        int x = static_cast<int>((totalNum - b) / k);
        vector<int> ans(n);
        for (int i=0; i<n; ++i) {
            ans[i] = x * coef[i][0] + coef[i][1];
        }
        return ans;
    }
};