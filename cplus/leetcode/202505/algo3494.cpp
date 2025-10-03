#include <bits/stdc++.h>
using namespace std;

// 动态规划 - 11.7 斜率优化 DP
class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        // 自行解答 规律是发现了, 不够代码不好写, 时间复杂度
        int n = skill.size(), m = mana.size();

        // 先不减少纬度
        vector<vector<long long>> dp(m+1, vector<long long>(n+1));
        for (int i=1; i<=m; ++i) {
            for (int j=1; j<=n; ++j) {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + skill[j-1] * mana[i-1];
            }
            for (int j=n; j; --j) {
                dp[i][j-1] = dp[i][j] - skill[j-1] * mana[i-1];
            }
        }
        return dp[m][n];

    }


    long long minTime2(vector<int>& skill, vector<int>& mana) {
        // 参考题解, 空间复杂度降低一维
        int n = skill.size(), m = mana.size();

        // 先不减少纬度
        vector<long long> dp(n+1);
        for (int i=1; i<=m; ++i) {
            for (int j=1; j<=n; ++j) {
                dp[j] = max(dp[j], dp[j-1]) + skill[j-1] * mana[i-1];
            }
            for (int j=n; j; --j) {
                dp[j-1] = dp[j] - skill[j-1] * mana[i-1];
            }
        }
        return dp[n];

    }
    
    long long minTime3(vector<int>& skill, vector<int>& mana) {
        // 凸包优化
        struct vec {
            int x, y;
            vec operator- (const vec& b) {return {x-b.x, y-b.y};}           // 向量的位移
            long det(const vec& b) {return 1L * x * b.y - 1L * y * b.x;}    // 向量的叉积
            long dot(const vec& b) {return 1L * x * b.x + 1L * y * b.y;}    // 向量的点积
        };

        auto convex_hull = [&](vector<vec> points) -> vector<vec> {
            vector<vec> q;
            for (auto p: points) {
                while (q.size()>1 && (q.back()-q[q.size()-2]).det(p-q.back()) >=0 ){
                    q.pop_back();
                }
                q.push_back(p);
            }
            return q;
        };

        int n = skill.size(), m = mana.size();
        vector<int> s(n+1); vector<vec> vs(n);
        for (int i=0; i<n; ++i) {
            s[i+1] = s[i] + skill[i];
            vs[i] = {s[i], skill[i]};
        }
        vs = convex_hull(vs);
        long start = 0;
        for (int j=1; j<m; ++j) {
            vec p = {mana[j-1] - mana[j], mana[j-1]};
            int l = -1, r = vs.size()-1;
            while (l+1 < r) {
                int mid = l + (r-l)/2;
                (p.dot(vs[mid]) > p.dot(vs[mid + 1]) ? r : l) = mid;
            }
            start += p.dot(vs[r]);
        }
        return start + 1LL * mana[m - 1] * s[n];
    }
};